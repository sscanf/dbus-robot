#include "statuswidget.h"
#include <QDBusPendingReply>
#include <QQuickItem>
#include <QTcpSocket>

#ifdef QT_DEBUG
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif

statusWidget::statusWidget(QWidget *parent)
    : QWidget(parent)
    , m_connection("") {
    m_pWidget = new QQuickWidget(this);
    connect(m_pWidget, &QQuickWidget::statusChanged, this, &statusWidget::onStatusChanged);
    m_pWidget->setSource(QUrl("qrc:/SpeedPanel.qml"));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(600);
    setFixedHeight(400);
    setWindowTitle("Motors Gauges");

    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, &QAbstractSocket::connected, this, &statusWidget::onConnected);

    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, &QAbstractSocket::connected, this, &statusWidget::onConnected);
    connect(m_pSocket, &QAbstractSocket::disconnected, this, &statusWidget::onDisconnected);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &statusWidget::onTimeout);
    m_pTimer->start(1000);
}

void statusWidget::connectToRobot() {
    QString connString = QString("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection       = QDBusConnection::connectToBus(connString, "connRobot");

    m_connection.connect("com.robot.roengines", //
                         "/roengines/l298n",
                         "com.robot.roengines",
                         "motorSpeedChanged",
                         this,
                         SLOT(onMotorSpeedChanged(int, int)));
}

int statusWidget::getRightSpeed() {
    int ret = 0;

    QDBusInterface robotIface("com.robot.roengines", //
                              "/engines",
                              "com.robot.roengines",
                              m_connection,
                              this);

    QDBusPendingReply<int> r = robotIface.call(QLatin1String("getEncoderRight"));
    if (r.isValid()) {
        ret = r.value();
    }
    return ret;
}

double statusWidget::map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int statusWidget::getLeftSpeed() {
    int ret = 0;

    QDBusInterface robotIface("com.robot.roengines", //
                              "/engines",
                              "com.robot.roengines",
                              m_connection,
                              this);

    QDBusPendingReply<int> r = robotIface.call(QLatin1String("getEncoderLeft"));
    if (r.isValid()) {
        ret = r.value();
    }
    return ret;
}

QStringList statusWidget::getProperties(QQuickItem *pItem) {
    QStringList  list;
    QMetaObject *meta = (QMetaObject *)pItem->metaObject();
    int          n    = meta->propertyCount();
    for (int i = 0; i < n; ++i) {
        list << meta->property(i).name();
    }
    return list;
}

void statusWidget::onTimeout() {
    m_pSocket->connectToHost(ROBOT_IP, 6667);
}

void statusWidget::onStatusChanged(QQuickWidget::Status status) {
    if (status == QQuickWidget::Ready) {
        QQuickItem *pItem = m_pWidget->rootObject();
        connect(pItem, SIGNAL(setPressed()), this, SLOT(onSetPressed()));

        m_pRightMotor   = pItem->findChild<QQuickItem *>("rightMotor");
        m_pLeftMotor    = pItem->findChild<QQuickItem *>("leftMotor");
        m_pMaximumSpeed = pItem->findChild<QQuickItem *>("maximumSpeed");
    }
}

void statusWidget::onMotorSpeedChanged(int motor, int speed) {
    if (motor == 0) { // Left
        m_pLeftMotor->setProperty("value", (int)speed);
    }

    if (motor == 1) { // Right
        m_pRightMotor->setProperty("value", (int)speed);
    }
}

void statusWidget::onSetPressed() {
    QVariant variant = m_pMaximumSpeed->property("text");
    int      speed   = variant.toInt();

    QDBusInterface roengines("com.robot.roengines", //
                             "/engines",
                             "com.robot.roengines",
                             m_connection,
                             this);

    int          vel = map(speed, 0, 150, 0, 15);
    QDBusMessage msg = roengines.call("setMaximumSpeed", QVariant::fromValue(qint32(vel)));
}

void statusWidget::onConnected() {
    m_pTimer->stop();
    connectToRobot();
}

void statusWidget::onDisconnected() {
    m_pTimer->start();
}

#ifdef QT_DEBUG
#pragma GCC pop_options
#endif
