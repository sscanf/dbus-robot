#include <QDebug>

#include "servoscontroller_worker.h"
#include "servoscontroller_worker_interface.h"

servoscontrollerWorker::servoscontrollerWorker(Adafruit_PWMServoDriver *pPwm,
                                               const QString           &strName,
                                               const QString           &strDescription,
                                               bool                     bEnabled,
                                               QObject                 *parent)
    : QObject(parent)
    , m_strName(strName)
    , m_connection(QDBusConnection::systemBus()) {
    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QStringLiteral("%1/%2").arg(DBUS_BASE_ADDRESS, strName);
    m_pPwm           = pPwm;
    m_inc            = 1;

    new servoscontroller_workerInterface(this);
    QString strObject = "/" + strName;
    m_connection.registerObject(strObject, this);
    //    m_connection.registerService(strAddress.replace("/","."));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &servoscontrollerWorker::on_timeout);
    m_pTimer->start(T_TIMEOUT);
    setAngle(0, 45);
    setAngle(1, 45);
}

QString servoscontrollerWorker::getName() {
    return m_strName;
}

QString servoscontrollerWorker::getAddress() {
    return m_strAddress;
}

QString servoscontrollerWorker::getPluginType() {
    return QStringLiteral (PLUGIN_TYPE);
}

QString servoscontrollerWorker::getDescription() {
    return m_strDescription;
}

bool servoscontrollerWorker::isEnabled() {
    return m_bEnabled;
}

void servoscontrollerWorker::setEnabled(bool bEnabled) {
    m_bEnabled = bEnabled;
}

double servoscontrollerWorker::map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void servoscontrollerWorker::on_timeout() {
    stop(0);
    stop(1);
    m_pTimer->stop();
}

void servoscontrollerWorker::stop(int pos) {
    m_pPwm->setPWM((int)pos, 0, 0);
}
void servoscontrollerWorker::setAngle(quint8 pos, quint16 angle) {
    // 240 = 1ms
    // 480 = 2ms
    //    qDebug() << angle;
    m_pPwm->setPWM((int)pos, 0, map(angle, 0, 180, 120, 480));
    //    m_pwm.setPWM(2, 0, map (angle, 0, 180, 120, 480));
    m_pTimer->start(T_TIMEOUT);
    emit positionChanged((int)pos, angle);
}

void servoscontrollerWorker::setServoPulse(quint8 n, double pulse) {
    double pulselength;

    pulselength = 1000000; // 1,000,000 us per second
    pulselength /= 50;     // 60 Hz
    pulselength /= 4096;   // 12 bits of resolution
    pulse *= 1000;
    pulse /= pulselength;
    m_pPwm->setPWM(n, 0, pulse);
}
