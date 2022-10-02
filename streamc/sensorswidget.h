#ifndef SENSORSWIDGET_H
#define SENSORSWIDGET_H

#include <QtQuickWidgets/QQuickWidget>
#include "itembase.h"

class SensorsWidget : public itemBase {
    Q_OBJECT
public:
    explicit SensorsWidget(QWidget *parent = nullptr);

private:
    void connectToDBusRobot();

private:
    QQuickItem *m_pFrontLeft   = nullptr;
    QQuickItem *m_pFrontCenter = nullptr;
    QQuickItem *m_pFronRight   = nullptr;
    QQuickItem *m_pRearLeft    = nullptr;
    QQuickItem *m_pRearCenter  = nullptr;
    QQuickItem *m_pRearRight   = nullptr;

private slots:
    void onStatusChanged(QQuickWidget::Status status);
    void onDistanceChanged(int sensor, int distance);

signals:
};

#endif // SENSORSWIDGET_H
