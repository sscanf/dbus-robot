#ifndef IMAGESENDER_H
#define IMAGESENDER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>
#include <QMutex>

using namespace cv;

class streamServer : public QObject
{
    Q_OBJECT
public:
    explicit streamServer(int port, QObject *parent = nullptr);
    void sendTcpFrame   (Mat const &img);
    void startListening ();
    void stopListening  ();

private:
    QTcpServer         *m_pSocket;
    QList<QTcpSocket *> m_listClients;
    int                 m_port=0;
    QMutex              m_mutex;

signals:

private slots:
    void on_newConnection();
    void on_disconnected();
    void on_readyRead();
};

#endif // IMAGESENDER_H
