#include <QDebug>
#include "l298n_worker.h"
#include "l298n_worker_interface.h"

l298nWorker::l298nWorker(QString strName, const QString &strDescription, bool bEnabled, QObject *parent)
    : QObject(parent)
    , m_connection(QDBusConnection::systemBus())
    , m_pwm(0x41)
    , m_strName(strName)
    , m_motorLeft(encoder_left, 1000.0, &m_pwm, MotorLeft_Forward, MotorLeft_Backward, this)
    , m_motorRight(encoder_right, 1000.0, &m_pwm, MotorRight_Backward, MotorRight_Forward, this)
    , m_PIDController(0.1, 0.01, 0.01) {

    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QString("%1/%2").arg(DBUS_BASE_ADDRESS, strName);

    new l298n_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject  = "/roengines/" + strName;
    m_connection.registerObject(strObject, this);
    m_connection.registerService(strAddress.replace("/", "."));

    m_pwm.begin();
    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &l298nWorker::onTimeout);
    m_pTimer->start(10);
}

QString l298nWorker::getName() {
    return m_strName;
}

QString l298nWorker::getAddress() {
    return m_strAddress;
}

QString l298nWorker::getPluginType() {
    return PLUGIN_TYPE;
}

QString l298nWorker::getDescription() {
    return m_strDescription;
}

bool l298nWorker::isEnabled() {
    return m_bEnabled;
}
void l298nWorker::setEnabled(bool bEnabled) {
    m_bEnabled = bEnabled;
}

int l298nWorker::getSpeed() {
    return m_speed;
}

int l298nWorker::getSpeed(int encoder) {
    int     ret     = 0;
    QString strFile = QString("/proc/driver/%1").arg(encoder_files[encoder]);
    QFile   file(strFile);
    if (file.open(QIODevice::ReadOnly)) {
        ret = file.readAll().toInt();
    }
    return ret;
}

void l298nWorker::setSpeed(int speed) {
    m_speed = speed;
}

void l298nWorker::onTimeout() {
    int encoder_reading_motorLeft  = m_motorLeft.getSpeed();
    int encoder_reading_motorRight = m_motorRight.getSpeed();

    if (m_speedRight != encoder_reading_motorRight) {
        m_speedRight = encoder_reading_motorRight;
        emit motorSpeedChanged (encoder_right, m_speedRight);
    }

    if (m_speedLeft != encoder_reading_motorLeft) {
        m_speedLeft= encoder_reading_motorLeft;
        emit motorSpeedChanged (encoder_left, m_speedLeft);
    }

    for (int time = 0; time < 100; time++) {
        int control_effort_motor1 = m_PIDController.Compute(m_speed, encoder_reading_motorLeft);
        int control_effort_motor2 = m_PIDController.Compute(m_speed, encoder_reading_motorRight);

        m_motorLeft.setSpeed(control_effort_motor1);
        m_motorRight.setSpeed(control_effort_motor2);
    }
}
