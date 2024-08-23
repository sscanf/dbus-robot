#include <QDebug>
#include <QFile>
#include "ina219_worker.h"
#include "ina219_worker_interface.h"

#ifdef QT_DEBUG
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif

ina219Worker::ina219Worker(QString strName, const QString &strDescription, bool bEnabled, QObject *parent)
    : QObject(parent)
    , m_strName(strName)
    , m_connection(QDBusConnection::systemBus()) {
    m_bEnabled       = bEnabled;
    m_strDescription = strDescription;
    m_strAddress     = QString("%1/%2").arg(DBUS_BASE_ADDRESS, strName);

    new ina219_workerInterface(this);
    m_connection.registerObject(m_strAddress, this);

    if (init() == EXIT_FAILURE) {
        throw std::runtime_error ("Can't init the INA219 driver");
    }
    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &ina219Worker::onTimeout);
    m_pTimer->start(1000);
}

QString ina219Worker::getName() {
    return m_strName;
}

QString ina219Worker::getAddress() {
    return m_strAddress;
}

QString ina219Worker::getPluginType() {
    return PLUGIN_TYPE;
}

QString ina219Worker::getDescription() {
    return m_strDescription;
}

bool ina219Worker::init() {
    bool ret = EXIT_FAILURE;

    //    echo "ina219 0x45" > /sys/bus/i2c/devices/i2c-4/new_device

    QFile file("/sys/bus/i2c/devices/i2c-4/new_device");
    if (file.open(QIODevice::WriteOnly)) {
        file.write("ina219 0x45");
        file.close();

        QDir        dir("/sys/class/hwmon");
        QStringList list = dir.entryList();

        foreach (QString str, list) {
            QString path = QString("/sys/class/hwmon/%1/name").arg(str);
            QFile   file(path);
            if (file.open(QIODevice::ReadOnly)) {
                QString name = file.readAll();
                if (name.contains("ina219")) {
                    m_strSysPath = path;
                    ret          = EXIT_SUCCESS;
                    break;
                }
            }
            file.close();
        }
    }
    return ret;
}

bool ina219Worker::isEnabled() {
    return m_bEnabled;
}

void ina219Worker::setEnabled(bool bEnabled) {
    m_bEnabled = bEnabled;
}

void ina219Worker::updateValues() {
    QString in1    = m_strSysPath + "/in1_input";
    QString curr1  = m_strSysPath + "/curr1_input";
    QString power1 = m_strSysPath + "/power1_input";

    int val = readFile(in1);
    if (val != m_voltage) {
        m_voltage = val;
        emit voltageChanged(val);
    }

    val = readFile(curr1);
    if (val != m_current) {
        m_current = val;
        emit currentChanged(val);
    }

    val = readFile(power1);
    if (val != m_power) {
        m_power = val;
        emit powerChanged(val);
    }
}

void ina219Worker::onTimeout() {
    updateValues();
}

int ina219Worker::getVoltage() {
    return m_voltage;
}

int ina219Worker::getCurrent() {
    return m_current;
}

int ina219Worker::getPower() {
    return m_power;
}

int ina219Worker::readFile(const QString &fileName) {
    int   value = -1;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {

        QString strVal = file.readAll();
        value          = strVal.toInt(nullptr, 10);
    }
    return value;
}
#ifdef QT_DEBUG
#pragma GCC pop_options
#endif
