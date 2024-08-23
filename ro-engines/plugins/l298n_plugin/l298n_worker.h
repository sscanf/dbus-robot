#ifndef l298n_MANAGER_H
#define l298n_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <roengines_plugin.h>
#include <QtDBus>
#include <Adafruit_PWMServoDriver.h>
#include "encodersthrd.h"
#include "motor.h"
#include "pidcontroller.h"

#define PLUGIN_TYPE      " Please, define plugin type !!! "
#define TIMER_RESOLUTION 1

#define ENCODER_RIGHT_CHANA "MXM3_5"  // GPIO 3
#define ENCODER_RIGHT_CHANB "MXM3_7"  // GPIO 4
#define ENCODER_LEFT_CHANA  "MXM3_11" // GPIO 5
#define ENCODER_LEFT_CHANB  "MXM3_13" // GPIO 6

class l298nWorker : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.roengines")

    const char *encoder_files[2] = {"robot_encoder_right", "robot_encodre_left"};

public:
    explicit l298nWorker(QString strName, const QString &strDescription = 0, bool bEnabled = 0, QObject *parent = 0);

public Q_SLOTS:
    QString getName();
    QString getAddress();
    QString getPluginType();
    QString getDescription();
    bool    isEnabled();
    void    setEnabled(bool bEnabled);
    int     getSpeed();
    int     getSpeed(int encoder);
    void    setSpeed(int speed);

private:
    void PIDControl(void);

private: // Variables
    QDBusConnection         m_connection;
    Adafruit_PWMServoDriver m_pwm;

    int           m_address;
    QString       m_strName;
    QString       m_strAddress;
    QString       m_strDescription;
    bool          m_bEnabled;
    int           m_speed      = 0;
    int           m_speedLeft  = 0;
    int           m_speedRight = 0;
    int           m_errorsRight[TOTAL_ERRORS];
    int           m_errorsLeft[TOTAL_ERRORS];
    int           m_nErrors = 0;
    QTimer       *m_pTimer;
    Motor         m_motorLeft;
    Motor         m_motorRight;
    PIDController m_PIDController;

    //   void (l298nWorker::*current_state)(QVariantList *) = NULL;

signals:
    void error(bool bError);
    void motorSpeedChanged(int, int);

private slots:
    // States
    void onTimeout();
};

#endif // l298n_MANAGER_H
