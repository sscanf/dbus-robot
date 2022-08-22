#ifndef l298n_MANAGER_H
#define l298n_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <roengines_plugin.h>
#include <QtDBus>
#include <Adafruit_PWMServoDriver.h>
#include <QtGui/QKeyEvent>
#include <QElapsedTimer>

#define PLUGIN_TYPE      " Please, define plugin type !!! "
#define TIMER_RESOLUTION 1

#define LIMIT         100
#define TOTAL_SAMPLES 1
#define TOTAL_ERRORS  5

#define ENCODER_RIGHT_CHANA "MXM3_5"  // GPIO 3
#define ENCODER_RIGHT_CHANB "MXM3_7"  // GPIO 4
#define ENCODER_LEFT_CHANA  "MXM3_11" // GPIO 5
#define ENCODER_LEFT_CHANB  "MXM3_13" // GPIO 6

class l298nWorker : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.roengines")

    const char *encoder_files[2] = {"robot_encoder_left", "robot_encoder_right"};

    enum direction {
        DIR_FORWARDING,
        DIR_TURNING_LEFT,
        DIR_TURNING_RIGHT,
        DIR_BACKWARDING,
        DIR_STOPPED
    };

    enum errors {
        ERR_MOTOR_LEFT,
        ERR_MOTOR_RIGHT
    };

    enum PWM {
        MotorLeft_Forward,
        MotorLeft_Backward,
        MotorRight_Forward,
        MotorRight_Backward
    };

    enum encoders {
        encoder_left,
        encoder_right
    };

    struct st_motor {
        encoders   m_encoder;
        int        m_pwm    = 0;
        qint32     m_speed  = 0;
        int        m_dir    = DIR_FORWARDING;
        int        m_errSum = 0;
        QList<int> m_errors;
    };

public:
    explicit l298nWorker(QString strName, QString strDescription = 0, bool bEnabled = 0, QObject *parent = 0);

public Q_SLOTS:
    int     init();
    QString getName();
    QString getAddress();
    QString getPluginType();
    QString getDescription();
    int     getMaxSpeed() const;
    void    setMaxSpeed(int newMaxSpeed);
    bool    isEnabled();
    void    setEnabled(bool bEnabled);
    int     getSpeed(int encoder);
    void    setSpeed(int speed);
    void    setDualSpeed(int left, int right);
    void    setTurn(int turn);
    int     getDirection();
    void    setPWMValue(int motorNum, int value);
    //    int     getSpeed();

    // quint8  getEncoderDir(Motors motor);
    // void    motorChangeDir(MotorDirection dir, MotorDirection motor);
    // void    motorSpeed(int speed, Motors motor);
    // quint8  motorDir(Motors motor);

private:
    void   PIDControl(st_motor &motor);
    void   setMotorSpeed(const st_motor &motor, int speed);
    int    loadModule();
    double convertSpeed(double speed);
    double map(double x, double in_min, double in_max, double out_min, double out_max);

private: // Variables
    QDBusConnection         m_connection;
    Adafruit_PWMServoDriver m_pwm;

    int           m_address;
    QString       m_strName;
    QString       m_strAddress;
    QString       m_strDescription;
    bool          m_bEnabled;
    st_motor      m_motorLeft;
    st_motor      m_motorRight;
    int           m_lastSpeedLeft    = 0;
    int           m_lastSpeedRight   = 0;
    int           m_maxSpeed         = 0;
    QTimer       *m_pTimer           = nullptr;
    QTimer       *m_pMotorController = nullptr;
    QElapsedTimer m_ellapsedTimer;

    //   void (l298nWorker::*current_state)(QVariantList *) = NULL;

signals:
    void error(int error);
    void encoderRightChange(int val);
    void encoderLeftChange(int val);

private slots:
    // States
    void onTimeout();
    void onMotorController();
};

#endif // l298n_MANAGER_H
