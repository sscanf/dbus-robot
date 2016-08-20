#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QImage>
#include <QTimer>

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
    Ui::MainWindow  *ui;
    QTcpSocket      *m_pSocket;
    quint64          m_totalBytes;
    QByteArray       m_arrImage;
    qint32           m_bytesRead;
    QByteArray      *m_pData;
    QWidget         *m_pWidget;
    QTimer          *m_pTimer;

private slots:
    void on_connected();
    void on_readyRead();
    void on_disconnected();
    void on_timeout();
};

#endif // MAINWINDOW_H
