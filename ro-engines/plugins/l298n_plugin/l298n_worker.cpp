#include <QDebug>
#include <QProcess>
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

    m_motorLeft.m_encoder  = encoder_left;
    m_motorRight.m_encoder = encoder_right;

    new l298n_workerInterface(this);
    QString strObject = "/" + strName;
    m_connection.registerObject(strObject, this);
}

int l298nWorker::init() {
    int ret = loadModule();
    if (ret == EXIT_SUCCESS) {
        m_pwm.begin();
        m_pPIDTimer = new QTimer(this);
        connect(m_pPIDTimer, SIGNAL(timeout()), this, SLOT(onPIDTimeout()));

        m_pMotorController = new QTimer(this);
        connect(m_pMotorController, SIGNAL(timeout()), this, SLOT(onMotorController()));

        m_pTskDispatcherTimer = new QTimer(this);
        connect(m_pTskDispatcherTimer, SIGNAL(timeout()), this, SLOT(onTaskDispatcher()));

        m_pPIDTimer->start(30);
    }
    return ret;
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

// int l298nWorker::getSpeed() {
//     return m_speed.m_speed;
// }

double l298nWorker::map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int l298nWorker::getMaxSpeed() const {
    return m_maxSpeed;
}

void l298nWorker::setMaxSpeed(int newMaxSpeed) {
    m_maxSpeed = newMaxSpeed;
}

int l298nWorker::getSpeed(int encoder) {
    int     ret     = 0;
    QString strFile = QString("/proc/driver/%1").arg(encoder_files[encoder]);
    QFile   file(strFile);
    if (file.open(QIODevice::ReadOnly)) {
        ret = file.readAll().toInt() / 2;
    }
    return ret;
}

void l298nWorker::setSpeed(int speed) {
    speed *= -1;
    setDualSpeed(speed, speed);
}

void l298nWorker::setDualSpeed(int left, int right) {
    left *= -1;
    right *= -1;

    if (m_maxSpeed > 0) {
        if (left > m_maxSpeed)
            left = m_maxSpeed;

        if (right > m_maxSpeed)
            right = m_maxSpeed;

        if (left < -m_maxSpeed)
            left = -m_maxSpeed;

        if (right < -m_maxSpeed)
            right = -m_maxSpeed;
    }

    m_motorLeft.m_dir  = (left < 0) ? DIR_FORWARDING : DIR_BACKWARDING;
    m_motorRight.m_dir = (right < 0) ? DIR_FORWARDING : DIR_BACKWARDING;

    //    m_motorLeft.m_pwm   = convertSpeed(left);
    m_motorLeft.m_speed = left;

    //    m_motorRight.m_pwm   = convertSpeed(right);
    m_motorRight.m_speed = right;
    m_pMotorController->start(3000);
}

void l298nWorker::setTurn(int turn) {
    qint32 *speedLeft  = &m_motorLeft.m_speed;
    qint32 *speedRight = &m_motorRight.m_speed;

    if (*speedLeft == 0 && *speedRight == 0) {
        if (turn > 0) {
            setDualSpeed(turn * -1, turn);
        } else {
            setDualSpeed(turn, turn * -1);
        }
    } else {
        if (turn > 0) {
            setDualSpeed(*speedLeft, (*speedRight) + turn);
        } else {
            setDualSpeed((*speedLeft) + turn, *speedRight);
        }
    }
}

int l298nWorker::getDirection() {
    int direction;
    int left  = getSpeed(encoder_left);
    int right = getSpeed(encoder_right);

    if (left == right) {
        if (left > 0)
            direction = DIR_FORWARDING;
        else if (left < 0)
            direction = DIR_BACKWARDING;
        else
            direction = DIR_STOPPED;
    }

    if (left > right)
        direction = DIR_TURNING_RIGHT;

    if (left < right)
        direction = DIR_TURNING_RIGHT;
    return direction;
}

void l298nWorker::setPWMValue(int motorNum, int value) {
    m_pPIDTimer->stop();
    if (motorNum == 0) {
        setMotorSpeed(m_motorLeft, value);
    }

    if (motorNum == 1) {
        setMotorSpeed(m_motorRight, value);
    }
}

void l298nWorker::pushTask(const QByteArray &arr) {
    stTask task;
    memcpy(&task, arr.constData(), sizeof(stTask));
    m_tasks.push(task);
}

void l298nWorker::PIDControl(st_motor &motor) {
    int desiredSpeed = abs(motor.m_speed);
    int encoderSpeed = abs(getSpeed(motor.m_encoder));

    if (desiredSpeed > 150)
        desiredSpeed = 150;

    if (desiredSpeed == 0) {
        setMotorSpeed(motor, 0);
        encoders enc    = motor.m_encoder;
        motor           = {};
        motor.m_encoder = enc;
    }

    int err = desiredSpeed - encoderSpeed;

    motor.m_errors.append(err);

    if (motor.m_errors.count() == TOTAL_ERRORS) {
        for (int n = 0; n < TOTAL_ERRORS; n++) {
            err += motor.m_errors[n];
        }

        err /= TOTAL_ERRORS;

        if (err < -LIMIT)
            err = -LIMIT;
        if (err > LIMIT)
            err = LIMIT;

        motor.m_errSum += err;
        setMotorSpeed(motor, encoderSpeed + motor.m_errSum);
        motor.m_errors.clear();
    }
}

void l298nWorker::setMotorSpeed(const st_motor &motor, int speed) {

    if (motor.m_encoder == encoder_left) {
        if (motor.m_speed >= 0) {
            m_pwm.setPWM(MotorLeft_Forward, 0, speed);
            m_pwm.setPWM(MotorLeft_Backward, 0, 0);
        } else {
            m_pwm.setPWM(MotorLeft_Forward, 0, 0);
            m_pwm.setPWM(MotorLeft_Backward, 0, speed);
        }
    }

    if (motor.m_encoder == encoder_right) {
        if (motor.m_speed >= 0) {
            m_pwm.setPWM(MotorRight_Forward, 0, speed);
            m_pwm.setPWM(MotorRight_Backward, 0, 0);
        } else {
            m_pwm.setPWM(MotorRight_Forward, 0, 0);
            m_pwm.setPWM(MotorRight_Backward, 0, speed);
        }
    }
}

int l298nWorker::loadModule() {
    int ret = EXIT_FAILURE;

    QProcess    process;
    QStringList arguments = {"/home/root/rtencoder.ko"};
    process.start("/sbin/insmod", arguments);

    if (process.waitForStarted()) {
        if (process.waitForFinished() == true) {
            ret = EXIT_SUCCESS;
        }

        if (process.exitCode()) {
            qDebug() << process.readAll();
        }
    }
    return ret;
}

double l298nWorker::convertSpeed(double speed) {
    return map(speed, 0, 120, 0, 3300);
}

void l298nWorker::onPIDTimeout() {
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
    PIDControl(m_motorLeft);
    PIDControl(m_motorRight);
}

void l298nWorker::onMotorController() {
    int encoderLeft  = getSpeed(encoder_left);
    int encoderRight = getSpeed(encoder_right);
    int speedLeft    = m_motorLeft.m_speed;
    int speedRight   = m_motorLeft.m_speed;

    if (encoderLeft == 0 && speedLeft) {
        emit error(ERR_MOTOR_LEFT);
    }

    if (encoderRight == 0 && speedRight) {
        emit error(ERR_MOTOR_RIGHT);
    }
}

void l298nWorker::onTaskDispatcher() {
    if (m_tasks.count()) {
        stTask task = m_tasks.pop();

        switch (task.m_task) {
            case TSK_STEP_FORWARD:
                setSpeed(0);
                setSpeed(task.m_speed);
                break;

            case TSK_STEP_BACKWARD:
                setSpeed(0);
                setSpeed(-task.m_speed);
                break;

            case TSK_TURN_LEFT:
                setSpeed(0);
                setTurn(task.m_speed);
                break;

            case TSK_TURN_RIGHT:
                setSpeed(0);
                setTurn(-task.m_speed);
                break;

            case TSK_STOP:
                setSpeed(0);
                break;

            default:
                break;
        }
        m_pTskDispatcherTimer->start(task.m_tSecs);
    }
}
