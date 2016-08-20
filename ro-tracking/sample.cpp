// Local file/media source.
std::string IMEM_SOURCE_FOLDER = "settings/rvideo/samples/bigdog";

class MyImemData
{
public:
    MyImemData() : mFrame(0), mDts(0), mPts(0) {}
    ~MyImemData() {}
    std::vector<cv::Mat> mImages;
    std::size_t mFrame;
    int64_t mDts;
    int64_t mPts;
};


/**
    \brief Callback method triggered by VLC to get image data from
    a custom memory source. This is used to tell VLC where the 
    data is and to allocate buffers as needed.

    To set this callback, use the "--imem-get=<memory_address>" 
    option, with memory_address the address of this function in memory.

    When using IMEM, be sure to indicate the format for your data
    using "--imem-cat=2" where 2 is video. Other options for categories are
    0 = Unknown,
    1 = Audio,
    2 = Video,
    3 = Subtitle,
    4 = Data

    When creating your media instance, use libvlc_media_new_location and
    set the location to "imem:/" and then play.

    \param[in] data Pointer to user-defined data, this is your data that
    you set by passing the "--imem-data=<memory_address>" option when
    initializing VLC instance.
    \param[in] cookie A user defined string. This works the same way as
    data, but for string. You set it by adding the "--imem-cookie=<your_string>"
    option when you initialize VLC. Use this when multiple VLC instances are
    running.
    \param[out] dts The decode timestamp, value is in microseconds. This value
    is the time when the frame was decoded/generated. For example, 30 fps 
    video would be every 33 ms, so values would be 0, 33333, 66666, 99999, etc.
    \param[out] pts The presentation timestamp, value is in microseconds. This
    value tells the receiver when to present the frame. For example, 30 fps 
    video would be every 33 ms, so values would be 0, 33333, 66666, 99999, etc.
    \param[out] flags Unused,ignore.
    \param[out] bufferSize Use this to set the size of the buffer in bytes.
    \param[out] buffer Change to point to your encoded frame/audio/video data. 
        The codec format of the frame is user defined and set using the
        "--imem-codec=<four_letter>," where 4 letter is the code for your
        codec of your source data.
*/
int MyImemGetCallback (void *data, 
                       const char *cookie, 
                       int64_t *dts, 
                       int64_t *pts, 
                       unsigned *flags, 
                       size_t * bufferSize,
                       void ** buffer)
{
    MyImemData* imem = (MyImemData*)data;

    if(imem == NULL)
        return 1;
    // Loop...
    if(imem->mFrame >= imem->mImages.size())
    {
        imem->mFrame = 0;
    }
    // Changing this value will impact the playback
    // rate on the receiving end (if they use the dts and pts values).
    int64_t uS = 33333; // 30 fps

    cv::Mat img = imem->mImages[imem->mFrame++];
    *bufferSize = img.rows*img.cols*img.channels();
    *buffer = img.data;
    *dts = *pts = imem->mDts = imem->mPts = imem->mPts + uS;

    return 0;
}


/**
    \brief Callback method triggered by VLC to release memory allocated
    during the GET callback.

    To set this callback, use the "--imem-release=<memory_address>" 
    option, with memory_address the address of this function in memory.

    \param[in] data Pointer to user-defined data, this is your data that
    you set by passing the "--imem-data=<memory_address>" option when
    initializing VLC instance.
    \param[in] cookie A user defined string. This works the same way as
    data, but for string. You set it by adding the "--imem-cookie=<your_string>"
    option when you initialize VLC. Use this when multiple VLC instances are
    running.
    \param[int] bufferSize The size of the buffer in bytes.
    \param[out] buffer Pointer to data you allocated or set during the GET
    callback to handle  or delete as needed.
*/
int MyImemReleaseCallback (void *data, 
                           const char *cookie, 
                           size_t bufferSize, 
                           void * buffer)
{
    // Since I did not allocate any new memory, I don't need
    // to delete it here. However, if you did in your get method, you
    // should delete/free it here.
    return 0;
}


/**
    \brief Method to load a series of images to use as raw image data
    for the network stream.

    \param[in] sourceFolder Path to folder containing jpeg or png images.
*/
std::vector<cv::Mat> GetRawImageData(const std::string& sourceFolder)
{
    namespace fs = boost::filesystem;
    std::vector<cv::Mat> result;
    std::vector<std::string> filenames;
    if( fs::exists(sourceFolder) && fs::is_directory(sourceFolder) )
    {
        for(fs::directory_iterator dir(sourceFolder);
            dir != fs::directory_iterator();
            dir++)
        {
            std::string ext = dir->path().extension().string();
            if( fs::is_regular_file( dir->status() ) &&
                (dir->path().extension() == ".jpeg" ||
                 dir->path().extension() == ".png") )
            {
                filenames.push_back(dir->path().string());
            }
        }
    }

    if(filenames.size() > 0)
    {
        // Sort from 0 to N
        std::sort(filenames.begin(), filenames.end());
        std::vector<std::string>::iterator filename;
        for(filename = filenames.begin();
            filename != filenames.end();
            filename++)
        {
            cv::Mat img = cv::imread(*filename);
            result.push_back(img);
        }
    }
    return result;
}


int main(int argc, char* argv[])
{

    // Load images first since we need to know
    // the size of the image data for IMEM
    MyImemData data;
    data.mImages = 
        GetRawImageData(IMEM_SOURCE_FOLDER);

    if(data.mImages.size() == 0)
    {
        std::cout << "No images found to render/stream.";
        return 0;
    }

    int w, h, channels;
    w = data.mImages.front().cols;
    h = data.mImages.front().rows;
    channels = data.mImages.front().channels();

    // You must create an instance of the VLC Library
    libvlc_instance_t * vlc;
    // You need a player to play media
    libvlc_media_player_t *mediaPlayer;
    // Media object to play.
    libvlc_media_t *media;

    // Configure options for this instance of VLC (global settings).
    // See VLC command line documentation for options.
    std::vector<const char*> options;
    std::vector<const char*>::iterator option;
    options.push_back("--no-video-title-show");

    char imemDataArg[256];
    sprintf(imemDataArg, "--imem-data=%#p", &data);
    options.push_back(imemDataArg);

    char imemGetArg[256];
    sprintf(imemGetArg, "--imem-get=%#p", MyImemGetCallback);
    options.push_back(imemGetArg);

    char imemReleaseArg[256];
    sprintf(imemReleaseArg, "--imem-release=%#p", MyImemReleaseCallback);
    options.push_back(imemReleaseArg);

    options.push_back("--imem-cookie=\"IMEM\"");
    // Codec of data in memory for IMEM, raw 3 channel RGB images is RV24
    options.push_back("--imem-codec=RV24");
    // Video data.
    options.push_back("--imem-cat=2");

    // If using RAW image data, like RGB24, then you
    // must specify the width, height, and number of channels
    // to IMEM. Other codes may have that information within
    // the data buffer, but RAW will not.
    char imemWidthArg[256];
    sprintf(imemWidthArg, "--imem-width=%d", w);
    options.push_back(imemWidthArg);

    char imemHeightArg[256];
    sprintf(imemHeightArg, "--imem-height=%d", h);
    options.push_back(imemHeightArg);

    char imemChannelsArg[256];
    sprintf(imemChannelsArg, "--imem-channels=%d", channels);
    options.push_back(imemChannelsArg);

    //options.push_back("--verbose=2");

    // Load the VLC engine
    vlc = libvlc_new (int(options.size()), options.data());

    // Create a media item from file
    media = libvlc_media_new_location (vlc, "imem://");

    // Configure any transcoding or streaming
    // options for the media source.
    options.clear();

    // Stream as MPEG2 via RTSP
    //options.push_back(":sout=#transcode{venc=ffmpeg{keyint=1,min-keyint=1,tune=zerolatency,bframes=0,vbv-bufsize=1200}, vcodec=mp2v,vb=800}:rtp{sdp=rtsp://:1234/BigDog}");

    // Stream as MJPEG (Motion JPEG) to http destination. MJPEG encoder
    // does not currently support RTSP
    //options.push_back(":sout=#transcode{vcodec=MJPG,vb=800,scale=1,acodec=none}:duplicate{dst=std{access=http,mux=mpjpeg,noaudio,dst=:1234/BigDog.mjpg}");

    // Convert to H264 and stream via RTSP
    options.push_back(":sout=#transcode{vcodec=h264,venc=x264,vb=0,vbv-bufsize=1200,bframes=0,scale=0,acodec=none}:rtp{sdp=rtsp://:1234/BigDog}");

    // Set media options
    for(option = options.begin(); option != options.end(); option++)
    {
        libvlc_media_add_option(media, *option);
    }

    // Create a media player playing environment 
    mediaPlayer = libvlc_media_player_new_from_media (media);

    // No need to keep the media now
    libvlc_media_release (media);

    // play the media_player
    libvlc_media_player_play (mediaPlayer);

    boost::this_thread::sleep(boost::posix_time::milliseconds(60000));

    // Stop playing 
    libvlc_media_player_stop (mediaPlayer);

    // Free the media_player 
    libvlc_media_player_release (mediaPlayer);
    // Free vlc
    libvlc_release (vlc);

    return 0;
}
