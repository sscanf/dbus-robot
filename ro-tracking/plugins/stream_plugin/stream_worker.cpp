#include <QDebug>
#include "stream_worker.h"
#include "stream_worker_interface.h"

//vlc v4l2:// :v4l2-dev=/dev/video0 :v4l2-width=640 :v4l2-height=480 --sout="#transcode{vcodec=h264,vb=800,scale=1,acodec=mp4a,ab=128,channels=2,samplerate=44100}:rtp{sdp=rtsp://:8554/live.ts}" -I dummy


streamWorker::streamWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_pImage    (0),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{

    m_bEnabled          = bEnabled;
    m_strDescription    = strDescription;
    m_strAddress        = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new stream_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
    m_connection.registerService(strAddress.replace("/","."));
}

void streamWorker::setImage(const char *pImage)
{
   m_pImage = pImage;
}

void streamWorker::start()
{
    if (m_pImage == 0)
        return;

    std::vector<const char*> options;
    std::vector<const char*>::iterator option;

    char imemDataArg[256];
    sprintf(imemDataArg, "--imem-data=%p", &m_pImage);
    options.push_back(imemDataArg);

    char imemGetArg[256];
    sprintf(imemGetArg, "--imem-get=%p", streamWorker::MyImemGetCallback);
    options.push_back(imemGetArg);

    char imemReleaseArg[256];
    sprintf(imemReleaseArg, "--imem-release=%p", streamWorker::MyImemReleaseCallback);
    options.push_back(imemReleaseArg);
    options.push_back(":sout=#transcode{vcodec=h264,venc=x264,vb=0,vbv-bufsize=1200,bframes=0,scale=0,acodec=none}:rtp{sdp=rtsp://:1234/BigDog}");
    options.push_back("--imem-cookie=\"IMEM\"");
    options.push_back("--imem-codec=RV24");
    options.push_back("--imem-cat=2");
    char imemWidthArg[256];
    sprintf(imemWidthArg, "--imem-width=800");
    options.push_back(imemWidthArg);

    char imemHeightArg[256];
    sprintf(imemHeightArg, "--imem-height=600");
    options.push_back(imemHeightArg);

    char imemChannelsArg[256];
    sprintf(imemChannelsArg, "--imem-channels=2");
    options.push_back(imemChannelsArg);
    //options.push_back("--verbose=2");

    m_pVlcInstance = libvlc_new (int(options.size()), options.data());
    m_pVlcMedia = libvlc_media_new_location (m_pVlcInstance, "imem://");

    for(option = options.begin(); option != options.end(); option++) {
        libvlc_media_add_option(m_pVlcMedia, *option);
    }


    m_pVlcMediaPlayer = libvlc_media_player_new_from_media (m_pVlcMedia);
    // No need to keep the media now
    libvlc_media_release (m_pVlcMedia);
    // play the media_player
    libvlc_media_player_play (m_pVlcMediaPlayer);
}

int streamWorker::MyImemGetCallback(void *data, const char *cookie, int64_t *dts, int64_t *pts, unsigned *flags, size_t *bufferSize, void **buffer)
{
    return 0;
}

int streamWorker::MyImemReleaseCallback(void *data, const char *cookie, size_t bufferSize, void *buffer)
{
    return 0;
}
