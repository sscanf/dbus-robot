#ifndef IRCAMERAWIDGET_H
#define IRCAMERAWIDGET_H

#include <QQuickItem>
#include <QQuickWidget>
#include <QWidget>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QtDBus>
#include <QTcpSocket>

class IRCameraWidget : public QWidget {
    Q_OBJECT
public:
    explicit IRCameraWidget(QWidget *parent = nullptr);
    void connectToRobot();

private:
    QDBusConnection m_connection;
    QQuickWidget   *m_pWidget;
    QQuickItem     *m_pTarget    = nullptr;
    QQuickItem     *m_pLabelX    = nullptr;
    QQuickItem     *m_pLabelY    = nullptr;
    QQuickItem     *m_pAzimut    = nullptr;
    QQuickItem     *m_pElevation = nullptr;
    QTcpSocket     *m_pSocket;
    QTimer         *m_pTimer;

private slots:
    void onPositionChanged(QPoint, QPoint, QPoint, QPoint);
    void onConnected();
    void onDisconnected();
    void onTimeout();

signals:
};

#endif // IRCAMERAWIDGET_H
