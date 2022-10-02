#include "itembase.h"
#include <QDebug>

itemBase::itemBase(QWidget *parent)
    : QQuickWidget(parent)
    , m_connection(QLatin1String("")) {

    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_pTimer->start(1000);
}

void itemBase::onConnected() {
    connectToDBusRobot();
}

void itemBase::onDisconnected() {
    m_pSocket->abort();
    m_pSocket->connectToHost(QStringLiteral(ROBOT_IP), ROBOT_DBUS_PORT);
}

void itemBase::onError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
}

void itemBase::onTimeout() {
    if (m_pSocket->state() != QAbstractSocket::ConnectedState) {
        m_pSocket->abort();
        m_pSocket->connectToHost(QStringLiteral(ROBOT_IP), ROBOT_DBUS_PORT);
    }
}
