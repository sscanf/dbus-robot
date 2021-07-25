#ifndef piccontroller_MANAGER_H
#define piccontroller_MANAGER_H

#include "qlibusb.h"
#include <QFile>
#include <QMap>
#include <QObject>
#include <QTimer>
#include <QtDBus/QtDBus>
#include <roengines_plugin.h>

#define PLUGIN_TYPE " Please, define plugin type !!! "
#define USB_BUFFER_LEN 32
#define VELOCIDAD_H 0
#define VELOCIDAD_L 1
#define MOTOR_LEFT_H 2
#define MOTOR_LEFT_L 3
#define MOTOR_RIGHT_H 4
#define MOTOR_RIGHT_L 5
#define BPID_H 6
#define BPID_L 7
#define MAX_SPEED 15

class piccontrollerWorker : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.roengines")

public:
    enum direction{
        DIR_FORWARDING,
        DIR_TURNING_LEFT,
        DIR_TURNING_RIGHT,
        DIR_BACKWARDING,
        DIR_STOPPED
    };
    enum errors
    {
        ERR_MOTOR_LEFT,
        ERR_MOTOR_RIGHT
    };
    explicit piccontrollerWorker(QString strName, QString strDescription = 0, bool bEnabled = 0, QObject *parent = 0);

public Q_SLOTS:
    QString getName();
    QString getAddress();
    QString getPluginType();
    QString getDescription();
    bool    isEnabled();
    void    setEnabled(bool bEnabled);
    int     getSpeed();
    int     getEncoderLeft();
    int     getEncoderRight();
    void    setSpeed(int speed);
    void    setTurn(int turn);
    void    setDualSpeed(int left, int right);
    void    setMaximumSpeed(int speed);
    int     getDirection();

private: // Functions
    void getEngineData();

private: // Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QlibUsb         m_libUsb;
    quint8 *        m_pUsbBufferTx;
    quint8 *        m_pUsbBufferRx;
    int             m_speed = 0;
    int             m_realSpeed;
    int             m_encoderLeft;
    int             m_encoderRight;
    int             m_lastEncoderRight = 0;
    int             m_lastEncoderLeft  = 0;
    QTimer *        m_pTimer;
    QTimer *        m_pCheckMotorsTimer;
    int             m_maxSpeed  = MAX_SPEED;
    direction       m_direction = DIR_STOPPED;

signals:
    void error(bool bError);
    void encoderRightChange(int val);
    void encoderLeftChange(int val);

private slots:
    void on_timeout();
    void on_CheckMotors();
};
#endif // piccontroller_MANAGER_H
