#ifndef ENCODERSTHRD_H
#define ENCODERSTHRD_H

#include <QThread>
#include <qsoc.h>
#include <Adafruit_PWMServoDriver.h>

#define TOTAL_SAMPLES 1
#define TOTAL_ERRORS  5
#define LIMIT         40

enum MotorDirection {
    Forward,
    Backward
};

class encodersThrd : public QThread {
    Q_OBJECT
public:
    enum States {
        stSampling,
        stAveraged,
        stWaitingForStopped
    };

    explicit encodersThrd(Adafruit_PWMServoDriver *pPWM, quint8 motorId, QString strChanA, QString strChanB, QThread *parent = nullptr);
    quint8 getEncoderDir();
    int    getEncoderWidth();
    void   motorChangeDir(MotorDirection dir);
    void   motorSpeed(int speed);
    quint8 motorDir();
    void   onWaitForStopped();
    void   run();

private:
    void onSampling();
    void onAveraged();
    void onWaitForMotorStop();
    void stop();

private:
    States                   m_currentState = stSampling;
    quint8                   m_motorId;
    quint8                   m_pulseDir;
    qint16                   m_inSpeed;
    qint16                   m_outSpeed;
    qint16                   m_pwm;
    quint8                   m_time_collision;
    int                      m_width = 0;
    QList<int>               m_errors;
    QSoc                     m_soc;
    QString                  m_strChanA;
    QString                  m_strChanB;
    int                      m_ticks     = 0;
    MotorDirection           m_direction = MotorDirection::Forward;
    Adafruit_PWMServoDriver *m_pPWM;
signals:
};

#endif // ENCODERSTHRD_H
