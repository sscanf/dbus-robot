#ifndef IMAGESENDER_H
#define IMAGESENDER_H

#include <QThread>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <QQueue>
#include <QTimer>

using namespace cv;

class streamServer : public QThread {
    Q_OBJECT
public:
    explicit streamServer(int port, QThread *parent = nullptr);
    void startListening();
    void stopListening();
    void pushFrame(Mat const &img);
    void run();

private:
    void sendTcpFrame(Mat const &img, QTcpSocket *pSocekt);

private:
    QTcpServer         *m_pSocket = nullptr;
    QList<QTcpSocket *> m_listClients;
    int                 m_port = 0;
    QMutex              m_mutex;
    QQueue<Mat>         m_frames;
    bool                m_bStop = false;

signals:

private slots:
    void onNewConnection();
    void onDisconnected();
    void onReadyRead();
    void onTimeout();
};

#endif // IMAGESENDER_H
