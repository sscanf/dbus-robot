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
    m_bBallDetected = false;

    new balltracker_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
    m_connection.registerService(strAddress.replace("/","."));

    connect (m_pTimer, SIGNAL (timeout()),  this, SLOT (on_timeout()));

    m_pSocket = new QTcpServer(this);
    connect(m_pSocket, SIGNAL (newConnection()), this, SLOT(on_newConnection()));
}

void balltrackerWorker::startTracking()
{
    m_pTimer->start (50);
}

void balltrackerWorker::stopTracking()
{
    m_pTimer->stop();
}

void balltrackerWorker::startStream()
{
    m_pSocket->listen(QHostAddress("0.0.0.0"),1234);
}

void balltrackerWorker::stopStream()
{
    m_pSocket->close();
}

QPoint balltrackerWorker::centerDistance()
{
    return m_centerDistance;
}

bool balltrackerWorker::isBallDetected()
{
    return m_bBallDetected;
}

QPoint balltrackerWorker::possition()
{
    QPoint pos;
    pos.setX(m_centerBall.x);
    pos.setY(m_centerBall.y);
    return pos;
}

void balltrackerWorker::drawCVPannel()
{
    Mat image = m_data.m_image;

    cv::Mat roi = image(cv::Rect(0, 0, 150, 100));
    cv::Mat color(roi.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    double alpha = 0.7;
    addWeighted(color, alpha, roi, 1.0 - alpha , 0.0, roi);


    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.5;
    int thickness = 1;
    Point textOrg (10,20);

    char buff[80];
    sprintf (buff,"X = %d ",m_centerBall.x);
    putText (m_data.m_image,buff,textOrg, fontFace, fontScale, Scalar(255,255,255),thickness,8);
    textOrg.y+=15;
    sprintf (buff,"Y = %d ",m_centerBall.y);
    putText (m_data.m_image,buff,textOrg, fontFace, fontScale, Scalar(255,255,255),thickness,8);
    textOrg.y+=15;
    sprintf (buff,"Z = %d ",m_radius);
    putText (m_data.m_image,buff,textOrg, fontFace, fontScale, Scalar(255,255,255),thickness,8);
    textOrg.y+=15;
    sprintf (buff,"Dist. X = %d ",m_centerDistance.x());
    putText (m_data.m_image,buff,textOrg, fontFace, fontScale, Scalar(255,255,255),thickness,8);
    textOrg.y+=15;
    sprintf (buff,"Dist. Y = %d ",m_centerDistance.y());
    putText (m_data.m_image,buff,textOrg, fontFace, fontScale, Scalar(255,255,255),thickness,8);
}

void balltrackerWorker::sendTcpFrame()
{
    if (m_pSocket->isListening()) {
        Mat img = m_data.m_image;
        QImage imgIn= QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        QByteArray arr;
        QBuffer buffer(&arr);
        buffer.open (QIODevice::WriteOnly);
        imgIn.save (&buffer,"JPEG");

        QByteArray sendArr;
        QDataStream stream (&sendArr,QIODevice::WriteOnly);
        stream << arr;

        m_mutex.lock();
        foreach (QTcpSocket *pSocket, m_listClients) {
            pSocket->write (sendArr);
        }
        m_mutex.unlock();
    }
}

void balltrackerWorker::on_timeout()
{
    //Mat imgOriginal;
    Mat imgThresholded_lRed;
    Mat imgThresholded_hRed;
    Mat imgThresholded;
    m_bBallDetected = false;

    bool bSuccess = m_capture.read(m_data.m_image); // read a new frame from video

    if (!bSuccess) { //if not success, break loop
        qDebug() << "Cannot read a frame from video stream";
        return;
    }
    //qDebug() << m_data.m_image.cols << m_data.m_image.rows;
    int centerBallX = m_data.m_image.cols/2;
    int centerBallY = m_data.m_image.rows/2;

    Mat imgHSV;
    cvtColor(m_data.m_image, imgHSV, COLOR_BGR2HSV);   //Convert the captured frame from BGR to HSV
//    GaussianBlur(imgHSV, imgHSV, Size(7,7), 2, 2);

    inRange(imgHSV, Scalar(0, 100, 100), Scalar(10, 255,255), imgThresholded_lRed); //Threshold the image
    inRange(imgHSV, Scalar(160, 100, 100), Scalar(179, 255,255), imgThresholded_hRed); //Threshold the image

    cv::addWeighted(imgThresholded_lRed, 1.0, imgThresholded_hRed, 1.0, 0.0, imgThresholded);
    GaussianBlur( imgThresholded, imgThresholded, cv::Size(9, 9), 2, 2 );
    vector<Vec3f> circles;

    HoughCircles( imgThresholded, circles, CV_HOUGH_GRADIENT, 1, imgThresholded.rows/8, 100, 20, 50, 100 );

    if (circles.size()) {
        m_centerBall = Point (cvRound(circles[0][0]), cvRound(circles[0][1]));
        m_radius = cvRound(circles[0][2]);
        // circle m_centerBall
        circle( m_data.m_image, m_centerBall, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( m_data.m_image, m_centerBall, m_radius, Scalar(0,0,255), 3, 8, 0 );
        m_bBallDetected = true;
//        imwrite("/tmp/edges.png",imgThresholded);
//        imwrite("/tmp/circles.png",img);
    }
    drawCVPannel();
    sendTcpFrame();

    int distX = m_centerBall.x - centerBallX;
    int distY = m_centerBall.y - centerBallY;
    m_centerDistance = QPoint (distX, distY);
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
