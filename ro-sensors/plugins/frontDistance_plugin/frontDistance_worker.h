#ifndef frontDistance_MANAGER_H
#define frontDistance_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QtDBus/QtDBus>
#include <rosensors_plugin.h>
#include "zoi2c.h"

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class frontDistanceWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rosensors")

public:
    explicit frontDistanceWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName           ()              { return m_strName; }
    QString getAddress        ()              { return m_strAddress; }
    QString getPluginType     ()              { return PLUGIN_TYPE; }
    QString getDescription    ()              { return m_strDescription; }
    bool    isEnabled         ()              { return m_bEnabled; }
    void    setEnabled        (bool bEnabled) { m_bEnabled = bEnabled; }
    int     getDistance       ();
    int     setMinimumDistance(int value);

private:    //Functions


private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QTimer         *m_pTimer;
    zoi2c           m_i2c;
    QByteArray      m_samples;
    int             m_distance;
    int             m_minDistance=10;
    
private slots:
    void onTimeout();

signals:
    void  error (bool bError);
    void  collision();
};

#endif // frontDistance_MANAGER_H
