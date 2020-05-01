#ifndef piccontroller_MANAGER_H
#define piccontroller_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <roengines_plugin.h>
#include <QtDBus/QtDBus>
#include "qlibusb.h"

#define PLUGIN_TYPE     " Please, define plugin type !!! "
#define USB_BUFFER_LEN 	32
#define VELOCIDAD_H		0
#define VELOCIDAD_L		1
#define MOTOR_LEFT_H	2
#define MOTOR_LEFT_L	3
#define MOTOR_RIGHT_H	4
#define MOTOR_RIGHT_L	5
#define BPID_H			6
#define BPID_L			7

class piccontrollerWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.roengines")

public:
    explicit piccontrollerWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName       ()              { return m_strName; }
    QString getAddress    ()              { return m_strAddress; }
    QString getPluginType ()              { return PLUGIN_TYPE; }
    QString getDescription()              { return m_strDescription; }
    bool    isEnabled     ()              { return m_bEnabled; }
    void    setEnabled    (bool bEnabled) { m_bEnabled = bEnabled; }
    int     getSpeed      ();
    int     getEncoder1   ();
    int     getEncoder2   ();
    void    setSpeed      (int speed);
    void    setTurn       (int turn);
    void    setDualSpeed  (int left, int right);

private:    //Functions
    void    getEngineData ();

private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QlibUsb         m_libUsb;
    quint8         *m_pUsbBufferTx;
    quint8         *m_pUsbBufferRx;
    int             m_speed=0;
    int             m_realSpeed;
    int             m_encoder1;
    int             m_encoder2;
    QTimer         *m_pTimer;

signals:
    void  error (bool bError);

private slots:
    void  on_timeout();

};
#endif // piccontroller_MANAGER_H
