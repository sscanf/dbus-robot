#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnection>
#include <QtQuickWidgets/QQuickWidget>
#include <QTcpSocket>

#define ROBOT_IP "192.168.0.1"
#define ROBOT_PORT 6667

class statusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit statusWidget(QWidget *parent = nullptr);

private:
    void connectToRobot();
    int  getRightSpeed ();
    int  getLeftSpeed  ();
    QStringList getProperties(QQuickItem *pItem);
    double map(double x, double in_min, double in_max, double out_min, double out_max);

private:
    QDBusConnection  m_connection;
    QTimer          *m_pTimer;
    QQuickWidget    *m_pWidget;
    QQuickItem      *m_pRightMotor;
    QQuickItem      *m_pLeftMotor;
    QQuickItem      *m_pMaximumSpeed;
    QTcpSocket      *m_pSocket;


private slots:
    void onTimeout();
    void onStatusChanged (QQuickWidget::Status status);
    void onEncoderLeftChanged (int);
    void onEncoderRightChanged (int);
    void onSetPressed();
    void onConnected();
    void onDisconnected();

signals:

};

#endif // STATUSWIDGET_H