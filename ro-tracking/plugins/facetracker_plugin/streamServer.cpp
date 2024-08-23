#include <QImage>
#include <QBuffer>
#include "streamServer.h"
#include <QCoreApplication>

streamServer::streamServer(int port, QObject *parent)
    : QObject(parent)
    , m_port(port) {
    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &streamServer::onTimeout);
    m_pSocket = new QTcpServer();
    startListening();
    connect(m_pSocket, &QTcpServer::newConnection, this, &streamServer::onNewConnection);
}

void streamServer::sendTcpFrame(const Mat &img) {
    Mat    temp;
    QImage imgIn;
    if (m_pSocket->isListening()) {
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

        m_mutex.lock();
        foreach (QTcpSocket *pSocket, m_listClients) {
            pSocket->write(sendArr);
        }
        m_mutex.unlock();
    }
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

void streamServer::onNewConnection() {
    qDebug() << "New TCP Connection";
    QTcpSocket *clientConnection = m_pSocket->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, this, &streamServer::onDisconnected);
    connect(clientConnection, &QIODevice::readyRead, this, &streamServer::onReadyRead);
    m_listClients.append(clientConnection);
    m_pTimer->start(5);
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
    qDebug() << m_frames.count();
    if (!m_frames.isEmpty()) {
        Mat img = m_frames.dequeue();
        sendTcpFrame(img);
    }
}
