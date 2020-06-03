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

#define MAX_SENSORS 6

class distanceWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rosensors")

public:
enum distances {
    frontCenter,
    frontLeft,
    frontRight,
    rearRight,
    rearLeft,
    rearCenter
};

    explicit distanceWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString    getName       ()              { return m_strName; }
    QString    getAddress    ()              { return m_strAddress; }
    QString    getPluginType ()              { return PLUGIN_TYPE; }
    QString    getDescription()              { return m_strDescription; }
    bool       isEnabled     ()              { return m_bEnabled; }
    void       setEnabled    (bool bEnabled) { m_bEnabled = bEnabled; }
    int        getDistance   (int distance);
    void       setMinFront   (int center, int right, int left);
    void       setMinRear    (int center, int right, int left);
    QList<QVariant> getCollisions();


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
    quint8          m_minDistances[6];
    quint8          m_distances[6]{0};
private slots:
    void onTimeout();

public:
signals:
    void  error (bool bError);
    void  collision(int sensor);
};


#endif // frontDistance_MANAGER_H
