#include <QDebug>
#include "distance_worker.h"
#include "distance_worker_interface.h"

distanceWorker::distanceWorker(const QString &strName, const QString &strDescription, bool bEnabled, QObject *parent)
    : QObject(parent)
    , m_strName(strName)
    , m_connection(QDBusConnection::systemBus()) {
    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QStringLiteral("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new distance_workerInterface(this);
    m_connection.registerObject(m_strAddress, this);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &distanceWorker::onTimeout);
    m_pTimer->start(100);
    m_i2c.setAddress(0x30);

    memset(m_minDistances, 20, sizeof(m_minDistances));
}

QString distanceWorker::getName() {
    return m_strName;
}

QString distanceWorker::getAddress() {
    return m_strAddress;
}

QString distanceWorker::getPluginType() {
    return QStringLiteral(PLUGIN_TYPE);
}

QString distanceWorker::getDescription() {
    return m_strDescription;
}

bool distanceWorker::isEnabled() {
    return m_bEnabled;
}

void distanceWorker::setEnabled(bool bEnabled) {
    m_bEnabled = bEnabled;
}

int distanceWorker::getDistance(int sensor) {
    return m_sensors[sensor];
}

QList<int> distanceWorker::getAllDistances() {
    QList<int> sensors;
    for (int n = 0; n < MAX_SENSORS; n++) {
        sensors.append(m_sensors[n]);
    }
    return sensors;
}

void distanceWorker::setMinFront(int center, int right, int left) {
    m_minDistances[frontCenter] = center;
    m_minDistances[frontRight]  = right;
    m_minDistances[frontLeft]   = left;
}

void distanceWorker::setMinRear(int center, int right, int left) {
    m_minDistances[rearCenter] = center;
    m_minDistances[rearRight]  = right;
    m_minDistances[rearLeft]   = left;
}

int distanceWorker::getSensorsCount() {
    // Test
    return MAX_SENSORS;
}

void distanceWorker::onTimeout() {
    m_i2c.receive(m_sensors, MAX_SENSORS);
    for (int n = 0; n < MAX_SENSORS; n++) {
        if (m_sensors[n] != m_lastSensors[n]) {
            emit distanceChanged(n, m_sensors[n]);
            m_lastSensors[n] = m_sensors[n];
        }
        if (m_sensors[n] > 0) {
            if (m_sensors[n] <= m_minDistances[n]) {
                if (m_bFlagCollisions[n] == false) {
                    m_bFlagCollisions[n] = true;
                    emit collision(n);
                }
            } else {
                m_bFlagCollisions[n] = false;
            }
        }
    }
}
