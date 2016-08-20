#include <QDebug>
#include "balltracker_worker.h"
#include "balltracker_worker_interface.h"

balltrackerWorker::balltrackerWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus()),
    m_capture   (0)
{
    if ( !m_capture.isOpened() ){  // if not success, exit program
         qDebug() << "Cannot open the web cam";
         return;
    }
    m_bStreaming    = false;
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);
    m_pTimer        = new QTimer();
    m_iLowH         = 0;
    m_iHighH        = 188;
    m_iLowS         = 92;
    m_iHighS        = 255;
    m_iLowV         = 105;
    m_iHighV        = 255;

    new balltracker_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
    m_connection.registerService(strAddress.replace("/","."));

    connect (m_pTimer, SIGNAL (timeout()),  this, SLOT (on_timeout()));
    m_pTimer->start (50);

    m_pSocket = new QTcpServer(this);
    m_pSocket->listen(QHostAddress("0.0.0.0"),1234);
    connect(m_pSocket, SIGNAL (newConnection()), this, SLOT(on_newConnection()));
}

void balltrackerWorker::startStreaming()
{
    if (m_data.m_image.data == 0)
        return;

    std::vector<const char*> options;
    std::vector<const char*>::iterator option;

    int w, h, channels;
    w = m_data.m_image.cols;
    h = m_data.m_image.rows;
    channels = m_data.m_image.channels();
    qDebug() << w << h << channels;

    char imemDataArg[256];
    memset (imemDataArg,0,sizeof(imemDataArg));
    sprintf(imemDataArg, "--imem-data=%p", &m_data);
    options.push_back(imemDataArg);

    char imemGetArg[256];
    memset (imemGetArg,0,sizeof(imemDataArg));
    sprintf(imemGetArg, "--imem-get=%p", balltrackerWorker::MyImemGetCallback);
    options.push_back(imemGetArg);

    char imemReleaseArg[256];
    memset (imemReleaseArg,0,sizeof(imemDataArg));
    sprintf(imemReleaseArg, "--imem-release=%p", balltrackerWorker::MyImemReleaseCallback);
    options.push_back(imemReleaseArg);
    options.push_back("--imem-cookie=\"IMEM\"");
    options.push_back("--imem-codec=RV24");
    options.push_back("--imem-cat=2");
    options.push_back("--imem-fps=10");
    char imemWidthArg[256];
    sprintf(imemWidthArg, "--imem-width=%d",w);
    options.push_back(imemWidthArg);


    char imemHeightArg[256];
    memset (imemHeightArg,0,sizeof(imemDataArg));
    sprintf(imemHeightArg, "--imem-height=%d",h);
    options.push_back(imemHeightArg);

    char imemChannelsArg[256];
    memset (imemChannelsArg,0,sizeof(imemDataArg));
    sprintf(imemChannelsArg, "--imem-channels=%d",channels);
    options.push_back(imemChannelsArg);
    options.push_back("-vvv");
    //options.push_back("--verbose=2");

    m_pVlcInstance = libvlc_new ((int)options.size(), options.data());
    m_pVlcMedia = libvlc_media_new_location (m_pVlcInstance, "imem://");

//    options.clear();
    options.push_back(":sout=#transcode{vcodec=ffmpeg{keyint=1,min-keyint=1,tune=zerolatency,bframes=0,vbv-bufsize=1200}, vcodec=png,vb=800}:rtp{sdp=rtsp://:8554/live.ts}");
    for(option = options.begin(); option != options.end(); option++) {
        libvlc_media_add_option(m_pVlcMedia, *option);
    }

    m_pVlcMediaPlayer = libvlc_media_player_new_from_media (m_pVlcMedia);
    // No need to keep the media now
    libvlc_media_release (m_pVlcMedia);
    // play the media_player
    libvlc_media_player_play (m_pVlcMediaPlayer);
    m_bStreaming = true;
}

int balltrackerWorker::MyImemGetCallback(void *data, const char *cookie, int64_t *dts, int64_t *pts, unsigned *flags, size_t *bufferSize, void **buffer)
{
    Q_UNUSED (cookie)
    Q_UNUSED (flags)

    MyImemData *pImem = (MyImemData*)data;
    if(pImem == NULL)
         return 1;

     // Changing this value will impact the playback
     // rate on the receiving end (if they use the dts and pts values).
     //int64_t uS = 33333; // 30 fps
     int64_t uS = 100000;
     *bufferSize = pImem->m_image.rows*pImem->m_image.cols*pImem->m_image.channels();
     *buffer = pImem->m_image.data;
     *dts = *pts = pImem->m_dts = pImem->m_pts = (pImem->m_pts + uS);
     return 0;
}

int balltrackerWorker::MyImemReleaseCallback(void *data, const char *cookie, size_t bufferSize, void *buffer)
{
    return 0;
}

void balltrackerWorker::on_timeout()
{
    //Mat imgOriginal;
    Mat imgThresholded;

    bool bSuccess = m_capture.read(m_data.m_image); // read a new frame from video

    if (!bSuccess) { //if not success, break loop
        qDebug() << "Cannot read a frame from video stream";
        return;
    }
    //qDebug() << m_data.m_image.cols << m_data.m_image.rows;
    int centerX = m_data.m_image.cols/2;
    int centerY = m_data.m_image.rows/2;

    Mat imgHSV;
    cvtColor(m_data.m_image, imgHSV, COLOR_BGR2HSV);   //Convert the captured frame from BGR to HSV
    GaussianBlur(imgHSV, imgHSV, Size(7,7), 2, 2);

    inRange(imgHSV, Scalar(m_iLowH, m_iLowS, m_iLowV), Scalar(m_iHighH, m_iHighS, m_iHighV), imgThresholded); //Threshold the image

    GaussianBlur( imgThresholded, imgThresholded, cv::Size(7, 7), 0, 0 );
    vector<Vec3f> circles;
    HoughCircles( imgThresholded, circles, CV_HOUGH_GRADIENT, 6, imgThresholded.rows/8, 100, 200, 50, 100 );
    Point center;

    if (circles.size()) {
        center = Point (cvRound(circles[0][0]), cvRound(circles[0][1]));
        int radius = cvRound(circles[0][2]);
        // circle center
        circle( m_data.m_image, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( m_data.m_image, center, radius, Scalar(0,0,255), 3, 8, 0 );

        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 2;
        int thickness = 3;
        Point textOrg (10,130);
        putText (m_data.m_image,"HOLA",textOrg, fontFace, fontScale, Scalar::all(255),thickness,8);

        Mat img = m_data.m_image;
        QImage imgIn= QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        QByteArray arr;
        QBuffer buffer(&arr);
        buffer.open (QIODevice::WriteOnly);
        imgIn.save (&buffer,"JPEG");

        QByteArray sendArr;
        QDataStream stream (&sendArr,QIODevice::WriteOnly);
//        stream << (quint64) arr.size();
        stream << arr;

        m_mutex.lock();

        foreach (QTcpSocket *pSocket, m_listClients) {
            pSocket->write (sendArr);
        }
        m_mutex.unlock();

//        imwrite("/tmp/edges.png",imgThresholded);
//        imwrite("/tmp/circles.png",img);
    }
//    else
//        qDebug() << "No ball !";


//    if (!m_bStreaming)
//        startStreaming();

//    int distX = center.x - centerX;
//    int distY = center.y - centerY;
    //    qDebug() << distX << distY << center.x << center.y << circles.size() << m_iLowH << m_iHighH << m_iLowS << m_iHighS << m_iLowV << m_iHighV;
}

void balltrackerWorker::on_newConnection()
{
    QTcpSocket *clientConnection = m_pSocket->nextPendingConnection();
    connect(clientConnection, SIGNAL (disconnected()), this, SLOT (on_disconnected()));
    m_listClients.append (clientConnection);
}

void balltrackerWorker::on_disconnected()
{
    QTcpSocket *pClient = (QTcpSocket *)sender();

    m_mutex.lock();
    int idx=0;
    foreach (QTcpSocket *pSocket, m_listClients) {
        if (pSocket == pClient) {
            m_listClients.removeAt (idx);
            pSocket->deleteLater();
            break;
        }
        idx++;
    }
    m_mutex.unlock();
}
