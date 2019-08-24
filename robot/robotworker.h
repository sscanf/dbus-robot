#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H
#include <QCoreApplication>
#include <QtDBus/QtDBus>
#include <QtDBus/qdbusconnection.h>
#include <positionthrd.h>


class robotWorker : public QCoreApplication
{
    Q_OBJECT

public:
    robotWorker(int & argc, char ** argv);

private: //Functions
    void initTracker();
    void initCamera();
    void setAngle (quint16 azim, quint16 elev);
    bool isBallDetected();
    double map(double x, double in_min, double in_max, double out_min, double out_max);


private: //Variables
    QTimer         *m_pTimer;
    QDBusConnection m_connection;
    QDBusInterface *m_pTrackingIface;
    QDBusInterface *m_pCameraIface;
    int             m_azimut;
    int             m_elev;
    int             m_lastDirElev;
    int             m_lastDirAzim;
    bool            m_ballLost=false;
    positionThrd   *m_pThrd;

private slots:
    void on_timeout();
    void on_possitionChanged (const QPoint &);
    void on_ballLost();
};

#endif // ROBOTWORKER_H
