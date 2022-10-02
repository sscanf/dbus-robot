#include <QImage>
#include <QBuffer>
#include "streamServer.h"
#include <QCoreApplication>

streamServer::streamServer(int port, QThread *parent)
    : QThread(parent)
    , m_port(port) {}

void streamServer::sendTcpFrame(const Mat &img, QTcpSocket *pSocket) {
    Mat    temp;
    QImage imgIn;
    switch (img.type()) {
        case 0:
            cvtColor(img, temp, COLOR_GRAY2RGB);
            imgIn = QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888).rgbSwapped();
            break;

        case 16:
            imgIn = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped();
            break;
    }
    QByteArray arr;
    QBuffer    buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    imgIn.save(&buffer, "JPEG");

    QByteArray  sendArr;
    QDataStream stream(&sendArr, QIODevice::WriteOnly);
    stream << arr;
    pSocket->write(sendArr);
    pSocket->waitForBytesWritten();

}

void streamServer::startListening() {
    if (m_pSocket != nullptr) {
        qDebug() << "Starting listening ";
        m_pSocket->listen(QHostAddress("0.0.0.0"), m_port);
    }
}

void streamServer::stopListening() {
    if (m_pSocket != nullptr)
        m_pSocket->close();
}

void streamServer::pushFrame(const Mat &img) {
    m_frames.enqueue(img);
}

void streamServer::run() {
    m_pSocket = new QTcpServer;
    connect(m_pSocket, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    while (!m_bStop) {
        foreach (QTcpSocket *pSocket, m_listClients) { //
            if (!m_frames.isEmpty()) {
                Mat img = m_frames.dequeue();
                sendTcpFrame(img, pSocket);
                msleep(50);
            }
        }
        msleep(1);
    }
}

void streamServer::onNewConnection() {
    qDebug() << "New TCP Connection";
    QTcpSocket *clientConnection = m_pSocket->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_listClients.append(clientConnection);
}

void streamServer::onDisconnected() {
    qDebug() << "TCP Connecton lost";
    QTcpSocket *pClient = (QTcpSocket *)sender();

    m_mutex.lock();
    int idx = 0;
    foreach (QTcpSocket *pSocket, m_listClients) {
        if (pSocket == pClient) {
            m_listClients.removeAt(idx);
            pSocket->deleteLater();
            break;
        }
        idx++;
    }
    m_mutex.unlock();
}

void streamServer::onReadyRead() {
    qDebug() << "receiving ...";
}

void streamServer::onTimeout() {
    // qDebug() << m_frames.count();
}
