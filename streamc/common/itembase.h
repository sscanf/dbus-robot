#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnection>
#include <QtQuickWidgets/QQuickWidget>
#include <QTcpSocket>
#include "../common/robot.h"

class itemBase : public QQuickWidget {
    Q_OBJECT
public:
    explicit itemBase(QWidget *parent = nullptr);

protected:
    virtual void    connectToDBusRobot() = 0;
    QDBusConnection m_connection;

private:
    QTimer     *m_pTimer  = nullptr;
    QTcpSocket *m_pSocket = nullptr;

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void onTimeout();
};

#endif // ITEMBASE_H
