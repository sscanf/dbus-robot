#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QImage>
#include <QTimer>


#define ILOW_H  0
#define IHIGH_H 188
#define ILOW_S  92
#define IHIGH_S 255
#define ILOW_V  105
#define IHIGH_V 255

namespace Ui {
class MainWindow;
}

struct values
{
    int m_iLowH;
    int m_iHighH;
    int m_iLowS;
    int m_iHighS;
    int m_iLowV;
    int m_iHighV;

    values(): m_iLowH   (ILOW_H),
              m_iHighH  (IHIGH_H),
              m_iLowS   (ILOW_S),
              m_iHighS  (IHIGH_S),
              m_iLowV   (ILOW_V),
              m_iHighV  (IHIGH_V){}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void sendData (void);

private:
    Ui::MainWindow  *ui;
    QTcpSocket      *m_pSocket;
    quint64          m_totalBytes;
    QByteArray       m_arrImage;
    qint32           m_bytesRead;
    QByteArray      *m_pData;
    QWidget         *m_pWidget;
    QTimer          *m_pTimer;
    values          *m_pValues;

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
