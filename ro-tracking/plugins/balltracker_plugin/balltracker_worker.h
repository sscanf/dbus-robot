#ifndef balltracker_MANAGER_H
#define balltracker_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <rotracking_plugin.h>
#include <QtDBus>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/ocl.hpp>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QImage>
#include <QImageWriter>
#include <QVector3D>
#include "streamServer.h"
//#include <raspicam/raspicam_cv.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

using namespace std;
using namespace cv;

#define ILOW_H  35
#define ILOW_S  50
#define ILOW_V  10

#define IHIGH_H 80
#define IHIGH_S 255
#define IHIGH_V 255

//COLOR_RANGES_HSV = {
//    "red": [(0, 50, 10), (10, 255, 255)],
//    "orange": [(10, 50, 10), (25, 255, 255)],
//    "yellow": [(25, 50, 10), (35, 255, 255)],
//    "green": [(35, 50, 10), (80, 255, 255)],
//    "cyan": [(80, 50, 10), (100, 255, 255)],
//    "blue": [(100, 50, 10), (130, 255, 255)],
//    "purple": [(130, 50, 10), (170, 255, 255)],
//    "red ": [(170, 50, 10), (180, 255, 255)]
//}

class MyImemData
{
public:
    MyImemData() : m_dts(0), m_pts(0) {}
    ~MyImemData() {}

    Mat    m_image;
    int64_t m_dts;
    int64_t m_pts;
};

class balltrackerWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rotracking")

public:
    explicit balltrackerWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName       ()              { return m_strName; }
    QString getAddress    ()              { return m_strAddress; }
    QString getPluginType ()              { return PLUGIN_TYPE; }
    QString getDescription()              { return m_strDescription; }
    bool    isEnabled     ()              { return m_bEnabled; }
    void    setEnabled    (bool bEnabled) { m_bEnabled = bEnabled; }
    void    startTracking ();
    void    stopTracking  ();
    void    startStream   ();
    void    stopStream    ();
    QPoint  xyPossition   ();
    int     zPossition    ();
    QPoint  centerDistance();
    bool    isBallDetected();
    void    morphOps      (Mat const &thresh);
    void    detectCircles ();

private:    //Functions
    void    drawCVPannel   ();

private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
//    QTimer         *m_pTimer;
    VideoCapture    m_capture;
    MyImemData      m_data;
    QTcpServer     *m_pSocket;
    QTcpSocket     *m_pClient;
    streamServer   *m_pThresholdSender;
    streamServer   *m_pResultSender;
    QMutex          m_mutex;
    QVector3D       m_centerBall;
    QPoint          m_centerDistance;
    bool            m_bBallDetected;
    int             m_iLowH;
    int             m_iHighH;
    int             m_iLowS;
    int             m_iHighS;
    int             m_iLowV;
    int             m_iHighV;
    int             m_camBrightness=100;
    int             m_ballLostCount=0;

//    raspicam::RaspiCam_Cv  m_camera;

signals:
    void error (bool bError);
    void possitionChanged (QPoint possition);
    void ballLost();
    void nextTrack();

private slots:
//    void on_timeout ();
    void on_newConnection();
    void on_disconnected();
    void on_readyRead();
    void on_track();
};

#endif // balltracker_MANAGER_H
