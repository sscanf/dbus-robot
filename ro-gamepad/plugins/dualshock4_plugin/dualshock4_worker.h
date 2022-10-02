#ifndef dualshock4_MANAGER_H
#define dualshock4_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QtGamepad>
#include <gamepad_plugin.h>
#include <QtDBus>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class dualshock4Worker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rogamepad.dualshock4")

public:
    explicit dualshock4Worker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName       ()              { return m_strName; }
    QString getAddress    ()              { return m_strAddress; }
    QString getPluginType ()              { return PLUGIN_TYPE; }
    QString getDescription()              { return m_strDescription; }
    bool    isEnabled     ()              { return m_bEnabled; }
    bool    isConnected   ();
    void    setEnabled    (bool bEnabled) { m_bEnabled = bEnabled; }
    void    redLedValue   (int value);
    void    greenLedValue (int value);
    void    blueLedValue  (int value);
    int     getCapacity   ();
    QString getStatus     ();

private:    //Functions
    void    printall();
    void    initDevFiles();
    void    updateValues();
    QString searchSubstring(const QStringList &list, const QString &match);

private:    //Variables
    int              m_address;
    QString          m_strName;
    QString          m_strAddress;
    QString          m_strDescription;
    bool             m_bEnabled;
    QDBusConnection  m_connection;
    QGamepad        *m_pPad=nullptr;
    double           m_lx=0;
    double           m_ly=0;
    double           m_rx=0;
    double           m_ry=0;
    bool             m_bBPS=false;
    double           m_btr2=0;
    double           m_btl2=0;
    bool             m_btl1=false;
    bool             m_btr1=false;
    bool             m_btopt=false;
    bool             m_btshared=false;
    bool             m_btA=false;
    bool             m_btB=false;
    bool             m_btY=false;
    bool             m_btX=false;
    int              m_capacity;
    QString          m_strStatus;
    QTimer          *m_pTimer;
    QString          m_redFile;
    QString          m_blueFile;
    QString          m_greenFile;
    QString          m_capacityFile;
    QString          m_statusFile;

signals:
    void error           (bool bError);
    void connected       ();
    void disconnected    ();
    void buttonPS        (bool);
    void axisLeftX       (double);
    void axisLeftY       (double);
    void axisRightX      (double);
    void axisRightY      (double);
    void buttonL1        (bool);
    void buttonR1        (bool);
    void buttonL2        (bool);
    void buttonR2        (bool);
    void buttonOpt       (bool);
    void buttonShare     (bool);
    void buttonA         (bool);
    void buttonB         (bool);
    void buttonY         (bool);
    void buttonX         (bool);
    void capacityChanged (int);
    void statusChanged   (QString );

private slots:
    void onAxisLeftXChanged    (double);
    void onAxisLeftYChanged    (double);
    void onAxisRightXChanged   (double);
    void onAxisRightYChanged   (double);
    void onButtonL2Changed     (double);
    void onButtonR2Changed     (double);
    void onButtonL1Changed     (bool);
    void onButtonR1Changed     (bool);
    void onButtonPSChanged     (bool);
    void onButtonOptionsChanged(bool);
    void onButtonShareChanged  (bool);
    void onButtonAChanged      (bool);
    void onButtonBChanged      (bool);
    void onButtonXChanged      (bool);
    void onButtonYChanged      (bool);
    void onTimeout();
};

#endif // dualshock4_MANAGER_H
