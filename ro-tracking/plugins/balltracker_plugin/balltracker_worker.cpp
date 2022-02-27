#include <QDebug>
#include "balltracker_worker.h"
#include "balltracker_worker_interface.h"
#include "../../../common/robot.h"

balltrackerWorker::balltrackerWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent)
    : QObject(parent)
    , m_strName(strName)
    , m_connection(QDBusConnection::systemBus())
    , m_capture(0)
    , m_iLowH(ILOW_H)
    , m_iHighH(IHIGH_H)
    , m_iLowS(ILOW_S)
    , m_iHighS(IHIGH_S)
    , m_iLowV(ILOW_V)
    , m_iHighV(IHIGH_V) {

    //    ocl::setUseOpenCL(false);
    //    if (!ocl::haveOpenCL()) {
    //        qDebug() << "OpenCL is not available...";
    //    }

    if (!m_capture.isOpened()) { // if not success, exit program
        qDebug() << "Cannot open the camera";
        return;
    }

    m_capture.set(CAP_PROP_FRAME_WIDTH, 320);
    m_capture.set(CAP_PROP_FRAME_HEIGHT, 240);
    //    m_capture.set (CV_CAP_PROP_FRAME_WIDTH,640);
    //    m_capture.set (CV_CAP_PROP_FRAME_HEIGHT,480);
    m_capture.set(CAP_PROP_BRIGHTNESS, 40);
    m_capture.set(CAP_PROP_CONTRAST, 1);
    //    m_capture.set (CV_CAP_PROP_XI_LED_MODE,1);

    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);
    //    m_pTimer        = new QTimer();
    m_bBallDetected = false;

    new balltracker_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject  = "/" + strName;
    m_connection.registerObject(strObject, this);

    //    connect (m_pTimer, SIGNAL (timeout()),  this, SLOT (on_timeout()));
    connect(this, SIGNAL(nextTrack()), this, SLOT(on_track()));

    m_pThresholdSender = new streamServer(ROBOT_STREAM_THRESHOLD_VIDEO);
    m_pResultSender    = new streamServer(1236);
    m_pSocket          = new QTcpServer(this);
    connect(m_pSocket, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
    m_pSocket->listen(QHostAddress("0.0.0.0"), 1234);

    QThread *pThreadThreshold = new QThread();
    QThread *pThreadResult    = new QThread();
    m_pThresholdSender->moveToThread(pThreadThreshold);
    m_pResultSender->moveToThread(pThreadResult);
    pThreadResult->start();
    pThreadThreshold->start();

    //    m_camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    //    m_camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);

    //    if ( !m_camera. open()) {
    //        qDebug() << "Error opening camera"<<endl;
    //        return;
    //    }
    startTracking();
    startStream();
}

void balltrackerWorker::morphOps(Mat const &thresh) {
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat dilatEelment = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    dilate(thresh, thresh, dilatEelment);
    dilate(thresh, thresh, dilatEelment);
}

void balltrackerWorker::startTracking() {
    emit nextTrack();
    //    m_pTimer->start (10);
}

void balltrackerWorker::stopTracking() {
    //    m_pTimer->stop();
}

void balltrackerWorker::startStream() {
    m_pThresholdSender->startListening();
    m_pResultSender->startListening();
}

void balltrackerWorker::stopStream() {
    m_pThresholdSender->stopListening();
    m_pResultSender->stopListening();
}

QPoint balltrackerWorker::centerDistance() {
    return m_centerDistance;
}

bool balltrackerWorker::isBallDetected() {
    return m_bBallDetected;
}

QPoint balltrackerWorker::xyPossition() {
    QPoint pos;
    pos.setX(m_centerBall.x());
    pos.setY(m_centerBall.y());
    return pos;
}

int balltrackerWorker::zPossition() {
    return m_centerBall.z();
}

void balltrackerWorker::drawCVPannel() {
    Mat image = m_data.m_image;

    cv::Mat roi = image(cv::Rect(0, 0, 100, 90));
    cv::Mat color(roi.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    double  alpha = 0.7;
    addWeighted(color, alpha, roi, 1.0 - alpha, 0.0, roi);

    int    fontFace  = FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.3;
    double thickness = 0.2;
    Point  textOrg(10, 20);

    char buff[80];
    sprintf(buff, "X = %f ", m_centerBall.x());
    putText(m_data.m_image, buff, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 3);
    textOrg.y += 15;
    sprintf(buff, "Y = %f ", m_centerBall.y());
    putText(m_data.m_image, buff, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 3);
    textOrg.y += 15;
    sprintf(buff, "Z = %f ", m_centerBall.z());
    putText(m_data.m_image, buff, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 3);
    textOrg.y += 15;
    sprintf(buff, "Dist. X = %d ", m_centerDistance.x());
    putText(m_data.m_image, buff, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 3);
    textOrg.y += 15;
    sprintf(buff, "Dist. Y = %d ", m_centerDistance.y());
    putText(m_data.m_image, buff, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 3);
}

// void balltrackerWorker::on_timeout()
//{
//    detectCircles();
//}

void balltrackerWorker::detectCircles() {
    Mat imgThresholded;
    m_bBallDetected = false;

    bool bSuccess = m_capture.read(m_data.m_image); // read a new frame from video
    if (!bSuccess) {                                // if not success, break loop
        qDebug() << "Cannot read a frame from video stream";
        return;
    }

    //    //Rotamos la imágen 90 grados porque la cámara está en posición vertical.
    double  angle = -90;
    Point2f center((m_data.m_image.cols - 1) / 2.0, (m_data.m_image.rows - 1) / 2.0);
    Mat     rot = getRotationMatrix2D(center, angle, 1);
    warpAffine(m_data.m_image, m_data.m_image, rot, m_data.m_image.size());

    int centerBallX = m_data.m_image.cols / 2;
    int centerBallY = m_data.m_image.rows / 2;

    Mat           imgHSV;
    vector<Vec3f> circles;
    cvtColor(m_data.m_image, imgHSV, COLOR_BGR2HSV); // Convert the captured frame from BGR to HSV
    inRange(imgHSV, Scalar(m_iLowH, m_iLowS, m_iLowV), Scalar(m_iHighH, m_iHighS, m_iHighV), imgThresholded); // Threshold the image
    //    morphOps (imgThresholded);
    GaussianBlur(imgThresholded, imgThresholded, cv::Size(9, 9), 3, 3);
    HoughCircles(imgThresholded, circles, HOUGH_GRADIENT, 2, imgThresholded.rows / 32, 200, 80, 0, 0);

    //    cvtColor(m_data.m_image, imgHSV, COLOR_BGR2GRAY);   //Convert the captured frame from BGR to GRAY
    //    medianBlur (imgHSV, imgHSV,5);
    //    vector<Vec3f> circles;
    //    HoughCircles( imgHSV, circles, CV_HOUGH_GRADIENT, 2, imgHSV.rows/32, 200, 80, 0, 0 );

    if (circles.size()) {
        m_centerBall     = QVector3D(cvRound(circles[0][0]), cvRound(circles[0][1]), cvRound(circles[0][2]));
//        IplImage  copy   = m_data.m_image;
//        IplImage *nImage = &copy;
//        if (m_centerBall.x() <= m_data.m_image.rows && m_centerBall.y() <= m_data.m_image.cols) {
//            CvScalar c = cvGet2D(nImage, m_centerBall.x(), m_centerBall.y()); // color of the center
//        }

        // circle m_centerBall
        circle(m_data.m_image, Point(m_centerBall.x(), m_centerBall.y()), 3, Scalar(0, 255, 0), -1, 8, 0);
        // circle outline
        circle(m_data.m_image, Point(m_centerBall.x(), m_centerBall.y()), m_centerBall.z(), Scalar(0, 0, 255), 3, 8, 0);

        m_bBallDetected = true;
        emit possitionChanged(xyPossition());
        m_ballLostCount = 0;
        // imwrite("/tmp/circles.png",img);
    } else {
        m_ballLostCount++;
        if (m_ballLostCount > 4) {
            emit ballLost();
            m_ballLostCount = 0;
        }
    }

    //    drawCVPannel();
    m_pThresholdSender->pushFrame(imgThresholded);
    m_pResultSender->pushFrame(m_data.m_image);

    int distX        = m_centerBall.x() - centerBallX;
    int distY        = m_centerBall.y() - centerBallY;
    m_centerDistance = QPoint(distX, distY);
    QTimer::singleShot(10, this, SLOT(on_track()));
}

void balltrackerWorker::on_newConnection() {
    m_pClient = m_pSocket->nextPendingConnection();
    connect(m_pClient, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(m_pClient, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void balltrackerWorker::on_disconnected() {
    m_pClient->deleteLater();
}

void balltrackerWorker::on_readyRead() {
    QTcpSocket *pSocket = (QTcpSocket *)this->sender();
    QByteArray  arr     = pSocket->readAll();
    QDataStream in(&arr, QIODevice::ReadOnly);
    in >> m_iLowH;
    in >> m_iHighH;
    in >> m_iLowS;
    in >> m_iHighS;
    in >> m_iLowV;
    in >> m_iHighV;
    in >> m_camBrightness;
    qDebug() << m_iLowH << m_iLowS << m_iLowV << " : " << m_iHighH << m_iHighS << m_iHighV << m_camBrightness;
    //    m_capture.set (CV_CAP_PROP_BRIGHTNESS,m_camBrightness);
}

void balltrackerWorker::on_track() {
    detectCircles();
}
