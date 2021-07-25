#include "powerwidget.h"

powerWidget::powerWidget(QWidget *parent) :
    QWidget(parent),
    m_connection ("")
{

    m_pWidget = new QQuickWidget(this);
    connect (m_pWidget, SIGNAL (statusChanged(QQuickWidget::Status)), this, SLOT (onStatusChanged(QQuickWidget::Status)));
    m_pWidget->setSource (QUrl ("qrc:/PowerPanel.qml"));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(730);
    setFixedHeight(400);
    setWindowTitle("Power Control");

    m_pSocket = new QTcpSocket (this);
    connect (m_pSocket, SIGNAL (connected()), this, SLOT (onConnected()));
    connect (m_pSocket, SIGNAL (disconnected()), this, SLOT (onDisconnected()));

    m_pTimer = new QTimer(this);
    connect (m_pTimer, SIGNAL(timeout()), this, SLOT (onTimeout()));
    m_pTimer->start(1000);
}

void powerWidget::connectToRobot()
{
    QString connString = QString("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection = QDBusConnection::connectToBus(connString,"robot");

    m_connection.connect( "com.robot.rosensors",
                          "/rosensors/ina219",
                          "com.robot.rosensors",
                          "voltageChanged",
                          this,
                          SLOT (onVoltageChanged(int)));

    m_connection.connect( "com.robot.rosensors",
                          "/rosensors/ina219",
                          "com.robot.rosensors",
                          "currentChanged",
                          this,
                          SLOT (onCurrentChanged(int)));

    m_connection.connect( "com.robot.rosensors",
                          "/rosensors/ina219",
                          "com.robot.rosensors",
                          "powerChanged",
                          this,
                          SLOT (onPowerChanged(int)));

    m_connection.connect( "com.robot.rogamepad",
                          "/rogamepad/dualshock4",
                          "com.robot.rogamepad",
                          "capacityChanged",
                          this,
                          SLOT (onCapacityChanged(int)));

    m_connection.connect( "com.robot.rogamepad",
                          "/rogamepad/dualshock4",
                          "com.robot.rogamepad",
                          "statusChanged",
                          this,
                          SLOT (onStatusChanged(int)));

    onCapacityChanged(getCapacity());
    onStatusChanged(getStatus());
}

int powerWidget::getCapacity()
{
    int ret=0;
    QDBusInterface robotIface ("com.robot.rogamepad",
                               "/rogamepad/dualshock4",
                               "com.robot.rogamepad.dualshock4",
                               m_connection, this);
    QDBusPendingReply<int> r = robotIface.call(QLatin1String("getCapacity"));
    if(r.isValid()) {
         ret= r.value();
    }
    return ret;
}

QString powerWidget::getStatus()
{
    QString ret;
    QDBusInterface robotIface ("com.robot.rogamepad",
                               "/rogamepad/dualshock4",
                               "com.robot.rogamepad.dualshock4",
                               m_connection, this);
    QDBusPendingReply<QString> r = robotIface.call(QLatin1String("getStatus"));
    if(r.isValid()) {
         ret= r.value();
    }
    return ret;
}

void powerWidget::onTimeout()
{
    m_pSocket->connectToHost(ROBOT_IP,ROBOT_DBUS_PORT);
}

void powerWidget::onConnected()
{
    m_pTimer->stop();
    connectToRobot();
}

void powerWidget::onDisconnected()
{
    m_connection.disconnectFromBus("robot");
    m_pTimer->start();
}


void powerWidget::onStatusChanged(QQuickWidget::Status status)
{
    if (status == QQuickWidget::Ready) {
        QQuickItem *pItem = m_pWidget->rootObject();
        m_pVoltage = pItem->findChild<QQuickItem *>("voltage");
        m_pCurrent = pItem->findChild<QQuickItem *>("current");
        m_pPower   = pItem->findChild<QQuickItem *>("power");
        m_pCapacity= pItem->findChild<QQuickItem *>("capacity");
        m_pStatus  = pItem->findChild<QQuickItem *>("status");
        m_pRobotCapacity= pItem->findChild<QQuickItem *>("robotCapacity");
    }
}

double powerWidget::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void powerWidget::onVoltageChanged(int val)
{
    if (m_pVoltage!=nullptr) {
        double voltage = val/1000.0;
        int cap = map (voltage,14.0,16.7,0,100);
        m_pVoltage->setProperty("currentValue",(double)voltage);
        m_pRobotCapacity->setProperty("currentValue",(double)cap);
    }
}

void powerWidget::onCurrentChanged(int val)
{
    if (m_pCurrent!=nullptr)
        m_pCurrent->setProperty("currentValue",(int)val);
}

void powerWidget::onPowerChanged(int val)
{
    if (m_pPower!=nullptr)
        m_pPower->setProperty("currentValue",(double)val/1000000.0);
}

void powerWidget::onCapacityChanged(int val)
{
    if (m_pCapacity!=nullptr)
        m_pCapacity->setProperty("currentValue",(int)val);
}

void powerWidget::onStatusChanged(QString str)
{
    if (m_pStatus!=nullptr)
        m_pStatus->setProperty("text",(QString)str);

}
