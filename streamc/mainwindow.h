#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QImage>
#include <QTimer>
#include "streamclientWidget.h"

#define ILOW_H  0
#define IHIGH_H 219
#define ILOW_S  88
#define IHIGH_S 255
#define ILOW_V  105
#define IHIGH_V 255

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void sendData (void);

private:
    Ui::MainWindow     *ui;
    QTcpSocket         *m_pSocket;
    quint64             m_totalBytes;
    QByteArray          m_arrImage;
    QTimer             *m_pTimer;
    int                 m_iLowH;
    int                 m_iHighH;
    int                 m_iLowS;
    int                 m_iHighS;
    int                 m_iLowV;
    int                 m_iHighV;
    streamClientWidget *m_pWidgetThreshold;
    streamClientWidget *m_pWidgetResult;

private slots:
    void on_connected();
    void on_readyRead();
    void on_disconnected();
    void on_timeout();
    void on_lowhChanged(int value);
    void on_lowsChanged(int value);
    void on_lowvChanged(int value);
    void on_highhChanged(int value);
    void on_highsChanged(int value);
    void on_highvChanged(int value);
};

#endif // MAINWINDOW_H
