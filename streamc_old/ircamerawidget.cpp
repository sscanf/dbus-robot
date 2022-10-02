#include "ircamerawidget.h"
#include "../common/robot.h"

IRCameraWidget::IRCameraWidget(QWidget* parent)
    : QWidget(parent)
    , m_connection("")
{
    m_pWidget = new QQuickWidget(this);
    m_pWidget->setSource(QUrl("qrc:/ircamera.qml"));
    m_pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    setFixedWidth(1024);
    setFixedHeight(768);
    setWindowTitle("Power Control");

    QQuickItem* pItem = m_pWidget->rootObject();
    m_pTarget         = pItem->findChild<QQuickItem*>("target");
    m_pLabelX         = pItem->findChild<QQuickItem*>("posXLabel");
    m_pLabelY         = pItem->findChild<QQuickItem*>("posYLabel");
    m_pAzimut         = pItem->findChild<QQuickItem*>("posAzimut");
    m_pElevation      = pItem->findChild<QQuickItem*>("posElevation");
    connectToRobot();
}

void IRCameraWidget::connectToRobot()
{
    QString connString = QString("tcp:host=%1,port=%2").arg(ROBOT_IP).arg(ROBOT_DBUS_PORT);
    m_connection       = QDBusConnection::connectToBus(connString, "robot");
    if (!m_connection.connect("com.robot.rotracking",
                              "/irtracker",
                              "com.robot.rotracking",
                              "positionChanged",
                              this,
                              SLOT(onPositionChanged(QPoint, QPoint, QPoint, QPoint)))) {
        qDebug() << "Can't connect to rotracking service";
        qDebug() << m_connection.lastError();
    }

    m_connection.connect("com.robot.pwm",
                         "/servos",
                         "com.robot.servoscontroller",
                         "positionChanged",
                         this,
                         SLOT(onPositionChanged(int, int)));
}

void IRCameraWidget::onPositionChanged(QPoint pos1, QPoint pos2, QPoint pos3, QPoint pos4)
{
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
