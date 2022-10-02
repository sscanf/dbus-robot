#include <QQuickItem>
#include "sensorswidget.h"

SensorsWidget::SensorsWidget(QWidget *parent)
    : itemBase(parent) {
    setSource(QUrl(QStringLiteral("qrc:/Sensors.qml")));
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(1024);
    setFixedHeight(768);
    setWindowTitle(QStringLiteral("Sensors status"));
    connect(this, &QQuickWidget::statusChanged, this, &SensorsWidget::onStatusChanged);
}

void SensorsWidget::connectToDBusRobot() {
    QString connString = QStringLiteral("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection       = QDBusConnection::connectToBus(connString, QStringLiteral("robot"));

    if (m_connection.isConnected()) {
    m_connection.connect(QStringLiteral("com.robot.rosensors"),
                         QStringLiteral("/rosensors/distance"),
                         QStringLiteral("com.robot.rosensors"),
                         QStringLiteral("distanceChanged"),
                         this,
                         SLOT(onDistanceChange(int,int)));
    }
}

void SensorsWidget::onStatusChanged(QQuickWidget::Status status) {
    if (status == QQuickWidget::Ready) {
        QQuickItem *pItem = rootObject();
        m_pFrontLeft      = pItem->findChild<QQuickItem *>(QStringLiteral("front_left"));
        m_pFrontCenter    = pItem->findChild<QQuickItem *>(QStringLiteral("front_center"));
        m_pFronRight      = pItem->findChild<QQuickItem *>(QStringLiteral("front_right"));
        m_pRearLeft       = pItem->findChild<QQuickItem *>(QStringLiteral("rear_left"));
        m_pRearCenter     = pItem->findChild<QQuickItem *>(QStringLiteral("rear_center"));
        m_pRearRight      = pItem->findChild<QQuickItem *>(QStringLiteral("rear_right"));
    }
}

void SensorsWidget::onDistanceChanged(int sensor, int distance) {
    qDebug() << sensor << distance;
}
