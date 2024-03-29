#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ircamerawidget.h"
#include "powerwidget.h"
#include "statuswidget.h"
#include "streamclientWidget.h"
#include "sensorswidget.h"
#include <QMainWindow>

#define ILOW_H  100
#define ILOW_S  100
#define ILOW_V  100
#define IHIGH_H 10
#define IHIGH_S 255
#define IHIGH_V 255

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void sendData(void);

private:
    Ui::MainWindow     *ui;
    QQuickWidget       *m_pWidget          = nullptr;
    streamClientWidget *m_pWidgetThreshold = nullptr;
    streamClientWidget *m_pWidgetResult    = nullptr;
    statusWidget       *m_pWidgetStatus    = nullptr;
    powerWidget        *m_pWidgetPower     = nullptr;
    IRCameraWidget     *m_pWidgetIRCamera  = nullptr;
    SensorsWidget      *m_pSensorsWidget   = nullptr;

private slots:
    void onApp(const QString&);
};

#endif // MAINWINDOW_H
