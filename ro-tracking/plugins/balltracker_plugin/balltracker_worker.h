#ifndef balltracker_MANAGER_H
#define balltracker_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <rotracking_plugin.h>
#include <QtDBus/QtDBus>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QImage>
#include <QImageWriter>
#include <QVector3D>
#include <raspicam/raspicam_cv.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

using namespace std;
using namespace cv;

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
    Q_CLASSINFO("D-Bus Interface", "com.robot.tracker")

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
    QPoint  possition     ();
    QPoint  centerDistance();
    bool    isBallDetected();

private:    //Functions
    void    drawCVPannel   ();
    void    sendTcpFrame   ();

private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QTimer         *m_pTimer;
    VideoCapture    m_capture;
    int             m_iLowH;
    int             m_iHighH;
    int             m_iLowS;
    int             m_iHighS;
    int             m_iLowV;
    int             m_iHighV;
    MyImemData      m_data;

    QTcpServer         *m_pSocket;
    QList<QTcpSocket *> m_listClients;
    QMutex              m_mutex;
    Point               m_centerBall;
    QPoint              m_centerDistance;
    int                 m_radius;
    bool                m_bBallDetected;
    raspicam::RaspiCam_Cv  m_camera;

signals:
    void  error (bool bError);

private slots:
    void on_timeout ();
    void on_newConnection();
    void on_disconnected();
    void on_readyRead();
};

#endif // balltracker_MANAGER_H
