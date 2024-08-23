#include "motor.h"
#include <QFile>
#include <QDebug>

#ifdef QT_DEBUG
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif
Motor::Motor(encoders                 encoder,
             double                   encoder_ticks_per_revolution,
             Adafruit_PWMServoDriver *pPwm,
             PWMChannel               forward,
             PWMChannel               backward,
             QObject                 *parent)
    : QObject(parent)
    , m_encoder_ticks_per_revolution(encoder_ticks_per_revolution)
    , m_position(0)
    , m_encoder(encoder)
    , m_pwmChannelFordward(forward)
    , m_pwmChannelBackward(backward)
    , m_pPwm(pPwm) {}

void Motor::setSpeed(double speed) {
    if (speed > 0) {
        m_pPwm->setPWM(m_pwmChannelFordward, 0, speed);
        m_pPwm->setPWM(m_pwmChannelBackward, 0, 0);
    }

    if (speed < 0) {
        m_pPwm->setPWM(m_pwmChannelFordward, 0, 0);
        m_pPwm->setPWM(m_pwmChannelBackward, 0, speed);
    }
}

double Motor::getSpeed() {
    int ret = -1;
    bool    ok;
    QString strFile = QString("/proc/driver/%1").arg(m_encoder_files[m_encoder]);
    QFile   file(strFile);
    if (file.open(QIODevice::ReadOnly)) {
        ret = file.readAll().toInt(&ok);
    }
    return (double)ret;
}

#ifdef QT_DEBUG
#pragma GCC pop_options
#endif
