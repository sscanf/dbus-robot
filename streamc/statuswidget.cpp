#include <QDBusPendingReply>
#include "statuswidget.h"
#include <QQuickItem>
#include <QTcpSocket>

statusWidget::statusWidget(QWidget *parent) :
    QWidget (parent),
    m_connection ("")
{
    m_pWidget = new QQuickWidget (this);
    connect (m_pWidget, SIGNAL (statusChanged(QQuickWidget::Status)), this, SLOT (onStatusChanged(QQuickWidget::Status)));
    m_pWidget->setSource (QUrl ("qrc:/SpeedPanel.qml"));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(600);
    setFixedHeight(400);
    setWindowTitle("Motors Gauges");

    m_pSocket = new QTcpSocket (this);
    connect (m_pSocket, SIGNAL (connected()), this, SLOT (onConnected()));


    m_pSocket = new QTcpSocket (this);
    connect (m_pSocket, SIGNAL (connected()), this, SLOT (onConnected()));
    connect (m_pSocket, SIGNAL (disconnected()), this, SLOT (onDisconnected()));

    m_pTimer = new QTimer(this);
    connect (m_pTimer, SIGNAL(timeout()), this, SLOT (onTimeout()));
    m_pTimer->start(1000);
}

void statusWidget::connectToRobot()
{
    QString connString = QString("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_PORT);
    m_connection = QDBusConnection::connectToBus(connString,"connRobot");


    m_connection.connect( "com.robot.roengines",
                           "/engines",
                           "com.robot.roengines",
                           "encoderLeftChange",
                           this,
                           SLOT (onEncoderLeftChanged(int)));

    m_connection.connect( "com.robot.roengines",
                           "/engines",
                           "com.robot.roengines",
                           "encoderRightChange",
                           this,
                           SLOT (onEncoderRightChanged(int)));
}

int statusWidget::getRightSpeed()
{
    int ret=0;
    QDBusInterface robotIface ("com.robot.roengines",
                               "/engines",
                               "com.robot.roengines",
                               m_connection, this);
    QDBusPendingReply<int> r = robotIface.call(QLatin1String("getEncoderRight"));
    if(r.isValid()) {
         ret= r.value();
    }
    return ret;
}

double statusWidget::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int statusWidget::getLeftSpeed()
{
    int ret=0;
    QDBusInterface robotIface ("com.robot.roengines",
                               "/engines",
                               "com.robot.roengines",
                               m_connection, this);
    QDBusPendingReply<int> r = robotIface.call(QLatin1String("getEncoderLeft"));
    if(r.isValid()) {
         ret= r.value();
    }
    return ret;
}

QStringList statusWidget::getProperties(QQuickItem *pItem)
{
    QStringList list;
    QMetaObject *meta = (QMetaObject *)pItem->metaObject();
    int n = meta->propertyCount();
    for(int i = 0; i < n; ++i) {
        list << meta->property(i).name();
    }
    return list;
}

void statusWidget::onTimeout()
{
    m_pSocket->connectToHost("192.168.0.1",6667);
}

void statusWidget::onStatusChanged(QQuickWidget::Status status)
{
    if (status == QQuickWidget::Ready) {
        QQuickItem *pItem = m_pWidget->rootObject();
        connect (pItem,SIGNAL (setPressed()), this, SLOT (onSetPressed()));
        m_pRightMotor = pItem->findChild<QQuickItem *> ("rightMotor");
        m_pLeftMotor  = pItem->findChild<QQuickItem *> ("leftMotor");
        m_pMaximumSpeed=pItem->findChild<QQuickItem *> ("maximumSpeed");
    }
}

void statusWidget::onEncoderLeftChanged(int value)
{
    float val = map (value, 0,30,0,170);
    m_pLeftMotor->setProperty("value",(int)val);
}

void statusWidget::onEncoderRightChanged(int value)
{
    float val = map (value, 0,30,0,170);
    m_pRightMotor->setProperty("value",(int)val);
}

void statusWidget::onSetPressed()
{
    QVariant variant = m_pMaximumSpeed->property("text");
    int speed = variant.toInt();

    QDBusInterface roengines ("com.robot.roengines", "/engines",
                                  "com.robot.roengines", m_connection, this);

    int vel = map (speed, 0,150,0,15);
    QDBusMessage msg = roengines.call ("setMaximumSpeed", QVariant::fromValue(qint32(vel)));
}

void statusWidget::onConnected()
{
    m_pTimer->stop();
    connectToRobot();
}

void statusWidget::onDisconnected()
{
    m_pTimer->start();
}
