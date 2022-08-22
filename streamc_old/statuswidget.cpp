#include <QDBusPendingReply>
#include <QQuickItem>
#include <QTcpSocket>
#include "statuswidget.h"
#include "../common/robot.h"

void statusWidget::connectToRobot() {
    QString connString = QStringLiteral("tcp:host=%1,port=%2").arg(QStringLiteral(ROBOT_IP)).arg(ROBOT_DBUS_PORT);
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
    QDBusPendingReply<int> r = robotIface.call(QStringLiteral("getEncoderRight"));
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

    int vel = map(speed, 0, 150, 0, 15);
    roengines.call(QStringLiteral("setMaximumSpeed"), QVariant::fromValue(qint32(vel)));
}

void statusWidget::onConnected() {
    m_pTimer->stop();
    connectToRobot();
}

void statusWidget::onDisconnected() {
    m_pTimer->start();
}
