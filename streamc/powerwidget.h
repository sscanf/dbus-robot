#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnection>
#include <QQuickWidget>
#include <QQuickItem>
#include <QTimer>
#include <QTcpSocket>
#include "../common/robot.h"

class powerWidget : public QWidget {
    Q_OBJECT
public:
    explicit powerWidget(QWidget *parent = nullptr);

private:
    void    connectToRobot();
    int     getCapacity();
    QString getStatus();
    double  map(double x, double in_min, double in_max, double out_min, double out_max);

private:
    QDBusConnection m_connection;
    QQuickWidget   *m_pWidget;
    QQuickItem     *m_pCapacity      = nullptr;
    QQuickItem     *m_pStatus        = nullptr;
    QQuickItem     *m_pVoltage       = nullptr;
    QQuickItem     *m_pCurrent       = nullptr;
    QQuickItem     *m_pPower         = nullptr;
    QQuickItem     *m_pRobotCapacity = nullptr;
    QTimer         *m_pTimer;
    QTcpSocket     *m_pSocket;

private slots:
    void onTimeout();
    void onStatusChanged(QQuickWidget::Status);
    void onConnected();
    void onDisconnected();
    void onVoltageChanged(int);
    void onCurrentChanged(int);
    void onPowerChanged(int);
    void onCapacityChanged(int val);
    void onStatusChanged(const QString &);

signals:
};

#endif // POWERWIDGET_H
