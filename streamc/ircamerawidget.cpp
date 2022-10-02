#include "ircamerawidget.h"
#include "../common/robot.h"

IRCameraWidget::IRCameraWidget(QWidget *parent)
    : QWidget(parent)
    , m_connection(QLatin1String("")) {
    m_pWidget = new QQuickWidget(this);
    m_pWidget->setSource(QUrl(QStringLiteral("qrc:/ircamera.qml")));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(1024);
    setFixedHeight(768);
    setWindowTitle(QStringLiteral("Power Control"));

    QQuickItem *pItem = m_pWidget->rootObject();
    m_pTarget         = pItem->findChild<QQuickItem *>(QStringLiteral("target"));
    m_pLabelX         = pItem->findChild<QQuickItem *>(QStringLiteral("posXLabel"));
    m_pLabelY         = pItem->findChild<QQuickItem *>(QStringLiteral("posYLabel"));
    m_pAzimut         = pItem->findChild<QQuickItem *>(QStringLiteral("posAzimut"));
    m_pElevation      = pItem->findChild<QQuickItem *>(QStringLiteral("posElevation"));

    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, &QAbstractSocket::connected, this, &IRCameraWidget::onConnected);
    connect(m_pSocket, &QAbstractSocket::disconnected, this, &IRCameraWidget::onDisconnected);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &IRCameraWidget::onTimeout);
    m_pTimer->start(1000);
}

void IRCameraWidget::connectToRobot() {
    QString connString = QStringLiteral("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection       = QDBusConnection::connectToBus(connString, QStringLiteral("robot"));
    if (!m_connection.connect(QStringLiteral("com.robot.rotracking"),
                              QStringLiteral("/irtracker"),
                              QStringLiteral("com.robot.rotracking"),
                              QStringLiteral("positionChanged"),
                              this,
                              SLOT(onPositionChanged(QPoint,QPoint,QPoint,QPoint)))) {
        qDebug() << "Can't connect to rotracking service";
        qDebug() << m_connection.lastError();
    }

    m_connection.connect(QStringLiteral("com.robot.pwm"),
                         QStringLiteral("/servos"),
                         QStringLiteral("com.robot.servoscontroller"),
                         QStringLiteral("positionChanged"),
                         this,
                         SLOT(onPositionChanged(int,int)));
}

void IRCameraWidget::onPositionChanged(QPoint pos1, QPoint pos2, QPoint pos3, QPoint pos4) {
    Q_UNUSED(pos2);
    Q_UNUSED(pos3);
    Q_UNUSED(pos4);

    qDebug() << pos1.x() << pos1.y();
    if (pos1.x() != 1023 && pos1.y() != 1023) {
        m_pTarget->setProperty("xPos", pos1.x() - 15);
        m_pTarget->setProperty("yPos", pos1.y() - 15);
        m_pLabelY->setProperty("label", pos1.y());
        m_pLabelX->setProperty("label", pos1.x());
    }
}

void IRCameraWidget::onConnected() {
    m_pTimer->stop();
    connectToRobot();
}

void IRCameraWidget::onDisconnected() {
    m_connection.disconnectFromBus(QStringLiteral("robot"));
    m_pTimer->start();
}

void IRCameraWidget::onTimeout() {
    m_pSocket->abort();
    m_pSocket->connectToHost(QStringLiteral(ROBOT_IP), ROBOT_DBUS_PORT);
}
