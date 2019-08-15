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
#include <rocamera_plugin.h>
#include <QtDBus/QtDBus>
#include <Adafruit_PWMServoDriver.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class servoscontrollerWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.servoscontroller")

public:
    explicit servoscontrollerWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName       ()              { return m_strName; }
    QString getAddress    ()              { return m_strAddress; }
    QString getPluginType ()              { return PLUGIN_TYPE; }
    QString getDescription()              { return m_strDescription; }
    bool    isEnabled     ()              { return m_bEnabled; }
    void    setEnabled    (bool bEnabled) { m_bEnabled = bEnabled; }
    void    setServoPulse (quint8 n, double pulse);
    void    setAngle      (quint8 n, quint16 angle);

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
    Adafruit_PWMServoDriver  m_pwm;
    QTimer                  *m_pTimer;
    int                      m_angle;
    int                      m_inc;
signals:
    void  error (bool bError);

private slots:
    void  on_timeout();

};

#endif // servoscontroller_MANAGER_H
