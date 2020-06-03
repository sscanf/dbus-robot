#include <QDebug>
#include "distance_worker.h"
#include "distance_worker_interface.h"

distanceWorker::distanceWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new distance_workerInterface(this);
    m_connection.registerObject(m_strAddress,this);

    m_pTimer = new QTimer (this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));
    m_pTimer->start(100);
    m_i2c.setAddress(0x30);

    memset (m_minDistances,16,sizeof (m_minDistances));
}

int distanceWorker::getDistance(int distance)
{
    return m_distances[distance];
}

QList<QVariant> distanceWorker::getCollisions()
{
    QList<QVariant> sensors;
    for (int n=0;n<MAX_SENSORS;n++) {
        if (m_distances[n]>0) {
            if (m_distances[n] <= m_minDistances[n]) {
                sensors.append (n);
            }
        }
    }
    return sensors;
}


void distanceWorker::setMinFront(int center, int right, int left)
{
    m_minDistances[frontCenter] = center;
    m_minDistances[frontRight] = right;
    m_minDistances[frontLeft] = left;
}

void distanceWorker::setMinRear(int center, int right, int left)
{
    m_minDistances[rearCenter] = center;
    m_minDistances[rearRight] = right;
    m_minDistances[rearLeft] = left;
}

void distanceWorker::onTimeout()
{
    m_i2c.receive(m_distances, MAX_SENSORS);

    for (int n=0;n<MAX_SENSORS;n++) {
        if (m_distances[n]>0) {
            if (m_distances[n] <= m_minDistances[n]) {
                emit collision (n);
            }
        }
    }
}
