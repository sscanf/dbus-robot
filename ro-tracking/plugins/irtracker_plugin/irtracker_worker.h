#ifndef balltracker_MANAGER_H
#define balltracker_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <rotracking_plugin.h>
#include <QtDBus/QtDBus>
#include <QTcpServer>
#include <QTcpSocket>
#include "zoposircam.h"
//#include <raspicam/raspicam_cv.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

using namespace std;

class irtrackerWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rotracking")

public:
    explicit irtrackerWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

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

private:    //Functions

private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QPoint          m_centerDistance;
    bool            m_bBallDetected;
    QPoint          m_pos1;
    QPoint          m_pos2;
    QPoint          m_pos3;
    QPoint          m_pos4;

//    raspicam::RaspiCam_Cv  m_camera;

signals:
    void error (bool bError);
    void positionChanged (QPoint, QPoint, QPoint, QPoint );
    void ballLost();
    void nextTrack();

private slots:
//    void on_timeout ();
    void on_track();
    void onDetection(QPoint, QPoint, QPoint, QPoint);
};

#endif // balltracker_MANAGER_H
