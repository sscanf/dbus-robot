#ifndef servoscontroller_MANAGER_H
#define servoscontroller_MANAGER_H
#include <limits.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <pwm_plugin.h>
#include <QtDBus>
#include <Adafruit_PWMServoDriver.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "
#define T_TIMEOUT     400

class servoscontrollerWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.servoscontroller")

public:
    enum Positions{
        position_azimuth,
        position_elevation
    };
    explicit servoscontrollerWorker(Adafruit_PWMServoDriver  *pPwm, QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName       ();
    QString getAddress    ();
    QString getPluginType ();
    QString getDescription();
    bool    isEnabled     ();
    void    setEnabled    (bool bEnabled);
    void    setServoPulse (quint8 n, double pulse);
    void    setAngle      (servoscontrollerWorker::Positions pos, quint16 angle);
    void    stop          (servoscontrollerWorker::Positions pos);

private:    //Functions
    double map(double x, double in_min, double in_max, double out_min, double out_max);

public:     //Variabes

private:    //Variables
    int                      m_address;
    QString                  m_strName;
    QString                  m_strAddress;
    QString                  m_strDescription;
    bool                     m_bEnabled;
    QDBusConnection          m_connection;
    Adafruit_PWMServoDriver  *m_pPwm;
    QTimer                   *m_pTimer;
    int                      m_inc;
signals:
    void  error (bool bError);
    void  positionChanged (int idx, int angle);

private slots:
    void  on_timeout();

};

#endif // servoscontroller_MANAGER_H
