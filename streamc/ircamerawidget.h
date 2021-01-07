#ifndef IRCAMERAWIDGET_H
#define IRCAMERAWIDGET_H

#include <QQuickWidget>
#include <QWidget>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnection>
#include <QQuickWidget>
#include <QQuickItem>

class IRCameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IRCameraWidget(QWidget *parent = nullptr);
    void connectToRobot();


private:
    QQuickWidget *m_pWidget;
    QDBusConnection m_connection;
    QQuickItem      *m_pTarget=nullptr;
    QQuickItem      *m_pLabelX=nullptr;
    QQuickItem      *m_pLabelY=nullptr;
    QQuickItem      *m_pAzimut=nullptr;
    QQuickItem      *m_pElevation=nullptr;


private slots:
    void onPositionChanged(QPoint, QPoint, QPoint, QPoint);

signals:

};

#endif // IRCAMERAWIDGET_H
