#include <QDebug>
#include "dualshock4_worker.h"
#include "dualshock4_worker_interface.h"

dualshock4Worker::dualshock4Worker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new dualshock4_workerInterface(this);
    m_connection.registerObject(m_strAddress,this);

    m_pTimer = new QTimer(this);
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));
    m_pTimer->start(1000);
    onTimeout();
}

bool dualshock4Worker::isConnected()
{
    return (m_pPad==nullptr);
}

void dualshock4Worker::initDevFiles()
{
    QDir dir("/sys/class/leds");
    QStringList list = dir.entryList(QDir::AllEntries);
    m_blueFile = "/sys/class/leds/"+searchSubstring(list, "blue")+"/brightness";
    m_redFile  = "/sys/class/leds/"+searchSubstring(list, "red")+"/brightness";
    m_greenFile= "/sys/class/leds/"+searchSubstring(list, "green")+"/brightness";

    dir.setPath ("/sys/class/power_supply");
    list = dir.entryList(QDir::AllEntries);
    m_capacityFile = "/sys/class/power_supply/"+searchSubstring(list,"sony_controller_battery")+"/capacity";
    m_statusFile   = "/sys/class/power_supply/"+searchSubstring(list,"sony_controller_battery")+"/status";
}

void dualshock4Worker::updateValues()
{
    QFile file(m_capacityFile);
    if (file.open (QIODevice::ReadOnly)) {
        int ret = QString (file.readAll()).toInt();
        if (ret != m_capacity) {
            m_capacity=ret;
            emit capacityChanged(ret);
        }
        file.close();
    }

   file.setFileName(m_statusFile);
    if (file.open (QIODevice::ReadOnly)) {
        QString ret = file.readAll();
        if (m_strStatus != ret) {
            m_strStatus=ret;
            emit statusChanged(ret.simplified());
        }
        file.close();
    }
}

int dualshock4Worker::getCapacity()
{
    return m_capacity;
}

QString dualshock4Worker::getStatus()
{
    return m_strStatus;
}


QString dualshock4Worker::searchSubstring(const QStringList &list, const QString &match)
{
    QString ret;
    foreach (QString str, list) {
        if (str.contains (match)) {
            ret=str;
        }
    }
    return ret;
}

void dualshock4Worker::redLedValue(int value)
{
    QFile file(m_redFile);
    if (file.open (QIODevice::WriteOnly)) {
        QString val = QString::number(value);
        file.write (val.toLocal8Bit().constData(),val.length());
    }
}

void dualshock4Worker::blueLedValue(int value)
{
    QFile file(m_blueFile);
    if (file.open (QIODevice::WriteOnly)) {
        QString val = QString::number(value);
        file.write (val.toLocal8Bit().constData(),val.length());
    }
}

void dualshock4Worker::greenLedValue(int value)
{
    qDebug() << m_greenFile;
    QFile file(m_greenFile);
    if (file.open (QIODevice::WriteOnly)) {
        QString val = QString::number(value);
        file.write (val.toLocal8Bit().constData(),val.length());
    }
}

void dualshock4Worker::onTimeout()
{
    //buttonSelect = Shared
    //buttonX = Cuadrado
    //buttonY = Triangulo
    //buttonA = X
    //buttonB = Circulo
    //buttonStart = options
    //buttonGuide = PS

    QList<int> gamePadIds = QGamepadManager::instance()->connectedGamepads();
    if (!gamePadIds.isEmpty()) {
        if (m_pPad == nullptr) {
            m_pPad = new QGamepad (gamePadIds[0], this);
            connect (m_pPad, SIGNAL (axisLeftXChanged(double)), this, SLOT (onAxisLeftXChanged(double)));
            connect (m_pPad, SIGNAL (axisLeftYChanged(double)), this, SLOT (onAxisLeftYChanged(double)));
            connect (m_pPad, SIGNAL (axisRightXChanged(double)),this, SLOT (onAxisRightXChanged(double)));
            connect (m_pPad, SIGNAL (axisRightYChanged(double)),this, SLOT (onAxisRightYChanged(double)));
            connect (m_pPad, SIGNAL (buttonR2Changed(double)),  this, SLOT (onButtonR2Changed(double)));
            connect (m_pPad, SIGNAL (buttonL1Changed(bool)),    this, SLOT (onButtonL1Changed(bool)));
            connect (m_pPad, SIGNAL (buttonR1Changed(bool)),    this, SLOT (onButtonR1Changed(bool)));
            connect (m_pPad, SIGNAL (buttonL2Changed(double)),  this, SLOT (onButtonL2Changed(double)));
            connect (m_pPad, SIGNAL (buttonGuideChanged(bool)), this, SLOT (onButtonPSChanged(bool)));
            connect (m_pPad, SIGNAL (buttonStartChanged(bool)), this, SLOT (onButtonOptionsChanged(bool)));
            connect (m_pPad, SIGNAL (buttonSelectChanged(bool)),this, SLOT (onButtonShareChanged(bool)));
            connect (m_pPad, SIGNAL (buttonAChanged(bool)),     this, SLOT (onButtonAChanged(bool)));
            connect (m_pPad, SIGNAL (buttonBChanged(bool)),     this, SLOT (onButtonBChanged(bool)));
            connect (m_pPad, SIGNAL (buttonXChanged(bool)),     this, SLOT (onButtonXChanged(bool)));
            connect (m_pPad, SIGNAL (buttonYChanged(bool)),     this, SLOT (onButtonYChanged(bool)));
            initDevFiles();
            emit connected();
        }
        updateValues();
    } else {
        if (m_pPad) {
            delete m_pPad;
            m_pPad=nullptr;
            emit disconnected();
        }
    }
}

void dualshock4Worker::onAxisLeftXChanged(double value)
{
    m_lx=value;
    emit axisLeftX(value);
    printall();
}

void dualshock4Worker::onAxisLeftYChanged(double value)
{
    m_ly=value;
    emit axisLeftY(value);
    printall();
}

void dualshock4Worker::onAxisRightXChanged(double value)
{
    m_rx=value;
    emit axisRightX(value);
    printall();
}

void dualshock4Worker::onAxisRightYChanged(double value)
{
    m_ry=value;
    emit axisRightY (value);
    printall();
}

void dualshock4Worker::onButtonR2Changed(double value)
{
    m_btr2=value;
    emit buttonR2(value);
    printall();
}

void dualshock4Worker::onButtonL1Changed(bool value)
{
    m_btl1 = value;
    emit buttonL1(value);
    printall();
}

void dualshock4Worker::onButtonR1Changed(bool value)
{
    m_btr1 = value;
    emit buttonR1(value);
    printall();
}

void dualshock4Worker::onButtonPSChanged(bool value)
{
    m_bBPS = value;
    emit buttonPS(value);
    printall();
}

void dualshock4Worker::onButtonOptionsChanged(bool value)
{
    m_btopt = value;
    emit buttonOpt(value);
    printall();
}

void dualshock4Worker::onButtonShareChanged(bool value)
{
    m_btshared = value;
    emit buttonShare(value);
    printall();
}

void dualshock4Worker::onButtonAChanged(bool value)
{
    m_btA = value;
    emit buttonA(value);
    printall();
}

void dualshock4Worker::onButtonBChanged(bool value)
{
    m_btB = value;
    emit buttonB(value);
    printall();
}

void dualshock4Worker::onButtonXChanged(bool value)
{
    m_btX = value;
    emit buttonX(value);
    printall();
}

void dualshock4Worker::onButtonYChanged(bool value)
{
    m_btY = value;
    emit buttonY(value);
    printall();
}

void dualshock4Worker::onButtonL2Changed(double value)
{
    m_btl2=value;
    emit buttonL2(value);
    printall();
}

void dualshock4Worker::printall()
{
    printf ("%04.3f %04.3f %04.3f %04.3f %04.3f %04.3f %d %d %d %d %d %d %d %d %d\n",
            m_lx, m_ly, m_rx, m_ry, m_btl2, m_btr2, m_bBPS, m_btl1, m_btr1, m_btshared, m_btopt, m_btA, m_btB, m_btX, m_btY);
    fflush(stdout);
}
