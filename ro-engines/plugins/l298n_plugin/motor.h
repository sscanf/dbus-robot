#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <Adafruit_PWMServoDriver.h>

enum encoders {
    encoder_left,
    encoder_right
};

enum PWMChannel {
    MotorLeft_Forward,
    MotorLeft_Backward,
    MotorRight_Backward,
    MotorRight_Forward
};

class Motor : public QObject {
    Q_OBJECT
public:
    Motor(encoders                 encoder,
          double                   encoder_ticks_per_revolution,
          Adafruit_PWMServoDriver *pPwm,
          PWMChannel               forward,
          PWMChannel               backward,
          QObject                 *parent = nullptr);
    void   setSpeed(double speed);
    double getSpeed();

private:
    const char *m_encoder_files[2] = {"robot_encoder_right", "robot_encoder_left"};

    double                   m_encoder_ticks_per_revolution;
    double                   m_position;
    encoders                 m_encoder;
    PWMChannel               m_pwmChannelFordward;
    PWMChannel               m_pwmChannelBackward;
    Adafruit_PWMServoDriver *m_pPwm = nullptr;
};

#endif // MOTOR_H
