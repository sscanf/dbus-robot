#ifndef IMAGESENDER_H
#define IMAGESENDER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <QQueue>
#include <QTimer>

using namespace cv;

class streamServer : public QObject {
    Q_OBJECT
public:
    explicit streamServer(int port, QObject *parent = nullptr);
    void startListening();
    void stopListening();
    void pushFrame(Mat const &img);

private:
    void sendTcpFrame(Mat const &img);

private:
    QTcpServer         *m_pSocket = nullptr;
    QTimer             *m_pTimer;
    QList<QTcpSocket *> m_listClients;
    int                 m_port = 0;
    QMutex              m_mutex;
    QQueue<Mat>         m_frames;

signals:

private slots:
    void onNewConnection();
    void onDisconnected();
    void onReadyRead();
    void onTimeout();
};

#endif // IMAGESENDER_H
