#include "statuswidget.h"
#include <QDBusPendingReply>
#include <QQuickItem>
#include <QTcpSocket>

statusWidget::statusWidget(QWidget *parent)
    : QWidget(parent)
    , m_connection(QLatin1String("")) {
    m_pWidget = new QQuickWidget(this);
    connect(m_pWidget, &QQuickWidget::statusChanged, this, &statusWidget::onStatusChanged);
    m_pWidget->setSource(QUrl(QStringLiteral("qrc:/SpeedPanel.qml")));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(600);
    setFixedHeight(400);
    setWindowTitle(QStringLiteral("Motors Gauges"));

    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, &QAbstractSocket::connected, this, &statusWidget::onConnected);
    connect(m_pSocket, &QAbstractSocket::disconnected, this, &statusWidget::onDisconnected);
    //    connect(m_pSocket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &statusWidget::onError);
    connect(m_pSocket, &QAbstractSocket::errorOccurred, this, &statusWidget::onError);

    m_pSocket->connectToHost(ROBOT_IP, 6667);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_pTimer->start(1000);
}

void statusWidget::connectToRobot() {
    QString connString = QStringLiteral("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection       = QDBusConnection::connectToBus(connString, QStringLiteral("connRobot"));

    m_connection.connect(QStringLiteral("com.robot.roengines"),
                         QStringLiteral("/engines"),
                         QStringLiteral("com.robot.roengines"),
                         QStringLiteral("encoderLeftChange"),
                         this,
                         SLOT(onEncoderLeftChanged(int)));

    m_connection.connect(QStringLiteral("com.robot.roengines"),
                         QStringLiteral("/engines"),
                         QStringLiteral("com.robot.roengines"),
                         QStringLiteral("encoderRightChange"),
                         this,
                         SLOT(onEncoderRightChanged(int)));
}

int statusWidget::getRightSpeed() {
    int                    ret = 0;
    QDBusInterface         robotIface(QStringLiteral("com.robot.roengines"),
                              QStringLiteral("/engines"),
                              QStringLiteral("com.robot.roengines"),
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
    int                    ret = 0;
    QDBusInterface         robotIface(QStringLiteral("com.robot.roengines"),
                              QStringLiteral("/engines"),
                              QStringLiteral("com.robot.roengines"),
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
    m_pSocket->abort();
    m_pSocket->connectToHost(ROBOT_IP, 6667);
}

void statusWidget::onStatusChanged(QQuickWidget::Status status) {
    if (status == QQuickWidget::Ready) {
        QQuickItem *pItem = m_pWidget->rootObject();
        connect(pItem, SIGNAL(setPressed()), this, SLOT(onSetPressed()));
        m_pRightMotor   = pItem->findChild<QQuickItem *>(QStringLiteral("rightMotor"));
        m_pLeftMotor    = pItem->findChild<QQuickItem *>(QStringLiteral("leftMotor"));
        m_pMaximumSpeed = pItem->findChild<QQuickItem *>(QStringLiteral("maximumSpeed"));
    }
}

void statusWidget::onEncoderLeftChanged(int value) {
    float val = map(value, 0, 30, 0, 170);
    m_pLeftMotor->setProperty("value", (int)val);
}

void statusWidget::onEncoderRightChanged(int value) {
    float val = map(value, 0, 30, 0, 170);
    m_pRightMotor->setProperty("value", (int)val);
}

void statusWidget::onSetPressed() {
    QVariant variant = m_pMaximumSpeed->property("text");
    int      speed   = variant.toInt();

    QDBusInterface roengines(QStringLiteral("com.robot.roengines"),
                             QStringLiteral("/engines"),
                             QStringLiteral("com.robot.roengines"),
                             m_connection,
                             this);

    int          vel = map(speed, 0, 150, 0, 15);
    QDBusMessage msg = roengines.call(QStringLiteral("setMaximumSpeed"), QVariant::fromValue(qint32(vel)));
}

void statusWidget::onConnected() {
    // m_pTimer->stop();
    connectToRobot();
}

void statusWidget::onDisconnected() {
    m_pTimer->start();
}

void statusWidget::onError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
    m_pSocket->abort();
    m_pSocket->connectToHost(ROBOT_IP, 6667);
}
