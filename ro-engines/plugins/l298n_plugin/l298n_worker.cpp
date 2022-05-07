#include <QDebug>
#include "l298n_worker.h"
#include "l298n_worker_interface.h"

l298nWorker::l298nWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent)
    : QObject(parent)
    , m_connection(QDBusConnection::systemBus())
    , m_pwm(0x41)
    , m_strName(strName) {

    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QString("%1/%2").arg(DBUS_BASE_ADDRESS, strName);

    new l298n_workerInterface(this);
    QString strObject = "/" + strName;
    m_connection.registerObject(strObject, this);

    m_pwm.begin();
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_pTimer->start (100);
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

int l298nWorker::getSpeed(encoders encoder) {
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

void l298nWorker::PIDControl() {
    int n;
    int err1               = 0;
    int err2               = 0;
    int realSpeed          = getSpeed();
    int encoderSpeed_left  = getSpeed(encoder_left);
    int encoderSpeed_right = getSpeed(encoder_right);

    m_errorsLeft[m_nErrors]  = realSpeed - encoderSpeed_left;
    m_errorsRight[m_nErrors] = realSpeed - encoderSpeed_right;

    if (++m_nErrors == TOTAL_ERRORS) {
        m_nErrors = 0;
        for (n = 0; n < TOTAL_ERRORS; n++) {
            err1 += m_errorsLeft[n];
            err2 += m_errorsRight[n];
        }

        err1 /= TOTAL_ERRORS;
        err2 /= TOTAL_ERRORS;

        if (err1 < 0 && err1 < -LIMIT)
            err1 = -LIMIT;
        if (err2 < 0 && err2 < -LIMIT)
            err2 = -LIMIT;

        if (err1 > LIMIT)
            err1 = LIMIT;
        if (err2 > LIMIT)
            err2 = LIMIT;

        setEncoderSpeed(encoder_left, m_speed + err1);
        setEncoderSpeed(encoder_right, m_speed + err2);
    }
}

void l298nWorker::setEncoderSpeed(encoders encoder, int speed) {

    if (speed > 0) {
        if (encoder == encoder_left) {
            m_pwm.setPWM(MotorLeft_Forward, 0, speed);
            m_pwm.setPWM(MotorLeft_Backward, 0, 0);
        }
        if (encoder == encoder_right) {
            m_pwm.setPWM(MotorRight_Forward, 0, speed);
            m_pwm.setPWM(MotorRight_Backward, 0, 0);
        }
    }

    if (speed < 0) {
        if (encoder == encoder_left) {
            m_pwm.setPWM(MotorLeft_Forward, 0, 0);
            m_pwm.setPWM(MotorLeft_Backward, 0, speed);
        }
        if (encoder == encoder_right) {
            m_pwm.setPWM(MotorRight_Forward, 0, 0);
            m_pwm.setPWM(MotorRight_Backward, 0, speed);
        }
    }
}

void l298nWorker::onTimeout() {
    int speedLeft  = getSpeed(encoder_left);
    int speedRight = getSpeed(encoder_right);

    if (m_lastSpeedLeft != speedLeft) {
        m_lastSpeedLeft = speedLeft;
        emit encoderLeftChange(speedLeft);
    }

    if (m_lastSpeedRight != speedRight) {
        m_lastSpeedRight = speedRight;
        emit encoderLeftChange(speedRight);
    }
    PIDControl();
}

// quint8 l298nWorker::getEncoderDir(Motors motor) {
//     quint8 ret = 0;
//     if (m_threads.size() <= motor) {
//         ret = m_threads[motor]->getEncoderDir();
//     }
//     return ret;
// }

// void l298nWorker::motorChangeDir(MotorDirection dir, MotorDirection motor) {
//     if (m_threads.size() <= motor) {
//         m_threads[motor]->motorChangeDir (dir);
//     }
// }

// void l298nWorker::motorSpeed(int speed, Motors motor) {
//     if (m_threads.size() <= motor) {
//         m_threads[motor]->motorSpeed (speed);
//     }
// }

// quint8 l298nWorker::motorDir(Motors motor) {
//     quint8 ret = 0;
//     switch (motor) {
//         case MotorLeft:
//             ret = !m_soc.level("MOTOR_LEFT");
//             break;
//         case MotorRight:
//             ret = m_soc.level("MOTOR_RIGHT");
//             break;
//     }
//     return ret;
// }

// void l298nWorker::setDirection(int motor, int direction) {
//    Q_UNUSED (motor)
//    Q_UNUSED (direction)
//    //    if (direction == MotorDirection::Forward) {
//    //        m_gpio1.setValue(imx6io::High);
//    //        m_gpio2.setValue(imx6io::Low);
//    //    }
//    //    if (direction == MotorDirection::Forward) {
//    //        m_gpio1.setValue(imx6io::Low);
//    //        m_gpio2.setValue(imx6io::High);
//    //    }
//}
