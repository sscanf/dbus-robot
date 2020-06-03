#include <QDebug>

#include "servoscontroller_worker.h"
#include "servoscontroller_worker_interface.h"

servoscontrollerWorker::servoscontrollerWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);
    m_angle          = 0;
    m_inc            = +1;

    new servoscontroller_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
//    m_connection.registerService(strAddress.replace("/","."));

    m_pTimer = new QTimer(this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT(on_timeout()));
    m_pwm.begin();
//    m_pTimer->start (10);
    setAngle(0,90);
    setAngle(1,45);
}

double servoscontrollerWorker::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void servoscontrollerWorker::on_timeout()
{
    setAngle (1,m_angle);
    setAngle (0,m_angle);

    m_angle += m_inc;
    if (m_angle>180)
        m_inc=-1;

    if (m_angle==0)
        m_inc=+1;
}

void servoscontrollerWorker::setAngle(quint8 n, quint16 angle)
{
    // 240 = 1ms
    // 480 = 2ms
//    qDebug() << angle;
    m_pwm.setPWM(n, 0, map (angle, 0, 180, 120, 480));
//    m_pwm.setPWM(2, 0, map (angle, 0, 180, 120, 480));
}

void servoscontrollerWorker::setServoPulse(quint8 n, double pulse)
{
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 50;   // 60 Hz
  pulselength /= 4096;  // 12 bits of resolution
  pulse *= 1000;
  pulse /= pulselength;
  m_pwm.setPWM(n, 0, pulse);
}
