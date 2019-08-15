#include <QImage>
#include <QBuffer>
#include "streamServer.h"

streamServer::streamServer(int port, QObject *parent) :
    m_port (port),
    QObject(parent)
{
    m_pSocket = new QTcpServer(this);
    connect(m_pSocket, SIGNAL (newConnection()), this, SLOT(on_newConnection()));
}

void streamServer::sendTcpFrame(const Mat &img)
{
    Mat temp;
    QImage imgIn;
    if (m_pSocket->isListening()) {
        switch (img.type()) {
            case 0:
                cvtColor (img, temp, COLOR_GRAY2RGB);
                imgIn= QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888).rgbSwapped();
            break;

            case 16:
                imgIn= QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped();
            break;
        }
        QByteArray arr;
        QBuffer buffer(&arr);
        buffer.open (QIODevice::WriteOnly);
        imgIn.save (&buffer,"JPEG");

        QByteArray sendArr;
        QDataStream stream (&sendArr,QIODevice::WriteOnly);
        stream << arr;

        m_mutex.lock();
        foreach (QTcpSocket *pSocket, m_listClients) {
            pSocket->write (sendArr);
        }
        m_mutex.unlock();
    }
}

void streamServer::startListening()
{
    m_pSocket->listen(QHostAddress("0.0.0.0"),m_port);
}

void streamServer::stopListening()
{
    m_pSocket->close();
}

void streamServer::on_newConnection()
{
    qDebug() << "New TCP Connection";
    QTcpSocket *clientConnection = m_pSocket->nextPendingConnection();
    connect(clientConnection, SIGNAL (disconnected()), this, SLOT (on_disconnected()));
    connect(clientConnection, SIGNAL (readyRead()), this, SLOT (on_readyRead()));
    m_listClients.append (clientConnection);
}

void streamServer::on_disconnected()
{
    qDebug() << "TCP Connecton lost";
    QTcpSocket *pClient = (QTcpSocket *)sender();

    m_mutex.lock();
    int idx=0;
    foreach (QTcpSocket *pSocket, m_listClients) {
        if (pSocket == pClient) {
            m_listClients.removeAt (idx);
            pSocket->deleteLater();
            break;
        }
        idx++;
    }
    m_mutex.unlock();
}

void streamServer::on_readyRead()
{
}
