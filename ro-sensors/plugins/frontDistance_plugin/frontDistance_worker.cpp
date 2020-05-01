#include <QDebug>
#include "frontDistance_worker.h"
#include "frontDistance_worker_interface.h"

frontDistanceWorker::frontDistanceWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new frontDistance_workerInterface(this);
    m_connection.registerObject(m_strAddress,this);

    m_pTimer = new QTimer (this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));
    m_pTimer->start(100);
    m_i2c.setAddress(0x30);
}

int frontDistanceWorker::getDistance()
{
    return m_distance;
}

int frontDistanceWorker::setMinimumDistance(int value)
{
    m_minDistance = value;
}

void frontDistanceWorker::onTimeout()
{
    unsigned char buff;
    m_i2c.receive(&buff,2);
    m_samples.append(buff);

    if (m_samples.count() == 4) {
        int avr=0;
        for (int n=0;n<m_samples.count();n++) {
            avr += m_samples[n];
        }
        avr = avr / m_samples.count();
        m_distance = avr;
        if (avr<=m_minDistance)
            emit collision();

        m_samples.clear();
    }
    qDebug() << m_distance;
}
