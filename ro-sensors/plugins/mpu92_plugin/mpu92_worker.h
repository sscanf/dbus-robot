#ifndef mpu950_MANAGER_H
#define mpu950_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QtDBus>
#include <mpu9250.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class mpu92Worker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.mpu950")

public:
    explicit mpu92Worker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName        ()              { return m_strName; }
    QString getAddress     ()              { return m_strAddress; }
    QString getPluginType  ()              { return PLUGIN_TYPE; }
    QString getDescription ()              { return m_strDescription; }
    bool    isEnabled      ()              { return m_bEnabled; }
    void    setEnabled     (bool bEnabled) { m_bEnabled = bEnabled; }
    void    setlTest       ();


private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    mpu9250         m_c9250;
    int16_t         m_accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
    QTimer         *m_pTimer;
    QVector3D       m_accelPos;
    QVector3D       m_gyroPos;
    QVector3D       m_magPos;
    int             m_countAvg=0;
    QList<float>    m_listPos;
    QList<float>    m_listYaw;

signals:
    void  error (bool bError);

private slots:
    void onTimeout();

};

#endif // mpu950_MANAGER_H
