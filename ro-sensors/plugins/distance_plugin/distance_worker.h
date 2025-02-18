#ifndef frontDistance_MANAGER_H
#define frontDistance_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <QtDBus>
#include <rosensors_plugin.h>
#include "zoi2c.h"

#define PLUGIN_TYPE " Please, define plugin type !!! "

//#define MAX_SENSORS 6
#define MAX_SENSORS 6

class distanceWorker : public QObject {
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

    explicit distanceWorker(const QString &strName, const QString &strDescription = 0, bool bEnabled = 0, QObject *parent = 0);

public Q_SLOTS:
    QString    getName();
    QString    getAddress();
    QString    getPluginType();
    QString    getDescription();
    bool       isEnabled();
    void       setEnabled(bool bEnabled);
    int        getDistance(int sensor);
    QList<int> getAllDistances();
    void       setMinFront(int center, int right, int left);
    void       setMinRear(int center, int right, int left);
    int        getSensorsCount();

private: // Functions
private: // Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    QTimer         *m_pTimer;
    zoi2c           m_i2c;
    quint8          m_minDistances[MAX_SENSORS];
    quint8          m_lastSensors[MAX_SENSORS]{0};
    quint8          m_sensors[MAX_SENSORS]{0};
    bool            m_bFlagCollisions[MAX_SENSORS]{false};
private slots:
    void onTimeout();

public:
signals:
    void error(bool bError);
    void collision(int sensor);
    void distanceChanged(int sensor, int distance);
};

#endif // frontDistance_MANAGER_H
