#include <QDebug>
#include <QFile>
#include "ina219_worker.h"
#include "ina219_worker_interface.h"

ina219Worker::ina219Worker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new ina219_workerInterface(this);
    m_connection.registerObject(m_strAddress,this);

    m_pTimer = new QTimer(this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));
    m_pTimer->start (1000);
}

void ina219Worker::updateValues()
{
    int val = readFile ("/sys/class/hwmon/hwmon1/in1_input");
    if (val!=m_voltage) {
        m_voltage=val;
        emit voltageChanged(val);
    }

    val = readFile ("/sys/class/hwmon/hwmon1/curr1_input");
    if (val!=m_current) {
        m_current=val;
        emit currentChanged(val);
    }

    val = readFile ("/sys/class/hwmon/hwmon1/power1_input");
    if (val!=m_power) {
        m_power=val;
        emit powerChanged(val);
    }
}

void ina219Worker::onTimeout()
{
    updateValues();
}

int ina219Worker::getVoltage()
{
    return m_voltage;
}

int ina219Worker::getCurrent()
{
    return m_current;
}

int ina219Worker::getPower()
{
    return m_power;
}

int ina219Worker::readFile(const QString &fileName)
{
    int value=-1;
    QFile file(fileName);
    if (file.open (QIODevice::ReadOnly)) {

        QString strVal = file.readAll();
        value = strVal.toInt(nullptr, 10);
    }
    return value;
}
