#include "encodersthrd.h"
#include <QDebug>

encodersThrd::encodersThrd(Adafruit_PWMServoDriver *pPWM, quint8 motorId, QString strChanA, QString strChanB, QThread *parent)
    : QThread(parent)
    , m_motorId(motorId)
    , m_strChanA(strChanA)
    , m_strChanB(strChanB)
    , m_pPWM(pPWM) {

    m_soc.addNewGPIO(strChanA, gpio_direction::INPUT);
    m_soc.addNewGPIO(strChanB, gpio_direction::INPUT);
}

quint8 encodersThrd::getEncoderDir() {
    return m_pulseDir;
}

int encodersThrd::getEncoderWidth() {
    return m_inSpeed;
}

void encodersThrd::motorSpeed(int speed) {
    m_outSpeed = speed;
}

quint8 encodersThrd::motorDir() {
    return m_pulseDir;
}

void encodersThrd::onWaitForStopped() {
    if (m_inSpeed == 0)
        m_currentState = stSampling;
}

void encodersThrd::run() {

    //    motorSpeed(20);
    m_pPWM->setPWM(m_motorId, 0, 500);

    forever {
        switch (m_currentState) {
            case stSampling:
                onSampling();
                break;
            case stAveraged:
                onAveraged();
                break;
            case stWaitingForStopped:
                onWaitForStopped();
                break;
        }
        msleep(1);
    }
}

void encodersThrd::onSampling() {
    qint8 enc_states[16] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
    quint8 position;

    position = m_soc.level(m_strChanA);
    position |= (m_soc.level(m_strChanB) >> 1);
    m_width += enc_states[(position)];

    //        qDebug("%02x",pEncoderR->position);
    //        qDebug("%02x",pEncoderL->position);
    //        QTimer::singleShot(1, this, &l298nWorker::stSampling);

    // 120 milisegundos = 480
    if (++m_ticks >= 120) {
        m_inSpeed = abs(m_width);
        qDebug() << m_inSpeed;
        m_width        = 0;
        m_ticks        = 0;
//        m_currentState = stAveraged;
        m_currentState = stSampling;
    } else
        m_currentState = stSampling;
    //            QTimer::singleShot(1, this, &l298nWorker::stSampling);
}

void encodersThrd::stop() {
    m_pPWM->setPWM(m_motorId, 0, 0);
}

void encodersThrd::onAveraged() {
    int err      = 0;
    int outSpeed = m_outSpeed;
    int width    = m_inSpeed;

    if (outSpeed < 0) {
        outSpeed *= -1;
        if (m_direction == MotorDirection::Forward) {
            m_direction = MotorDirection::Backward;
            stop();
            m_currentState = stWaitingForStopped;
            return;
        }
    } else if (outSpeed > 0 && m_direction == MotorDirection::Backward) {
        m_direction = MotorDirection::Forward;
        stop();
        m_currentState = stWaitingForStopped;
        return;
    }
    err = outSpeed - width;
    m_errors.append(err);

    if (m_errors.size() == TOTAL_ERRORS) {
        for (int n = 0; n < TOTAL_ERRORS; n++) {
            err += m_errors[n];
        }
        err /= TOTAL_ERRORS;

        if (err < 0 && err < -LIMIT)
            err = -LIMIT;

        if (err > LIMIT)
            err = LIMIT;

        qint16 newPWM = (m_outSpeed == 0) ? 0 : m_pwm + err;
        m_pwm += newPWM;
        m_pPWM->setPWM(m_motorId, 0, m_pwm);
        m_errors.clear();
    }
    m_currentState = stSampling;
}
