#include "streamclientWidget.h"

streamClientWidget::streamClientWidget(const QString &host, int port, QWidget *parent)
    : QWidget(parent)
    , m_port(port)
    , m_strHost(host)
    , m_groupAddress4(QStringLiteral("192.168.0.255")) {
    setMinimumSize(QSize(1024, 768));
    resize(QSize(1024, 768));
    m_bytesRead = 0;
    m_pData     = new QByteArray();

    m_pUdpSocket = new QUdpSocket(this);
    m_pUdpSocket->bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);
    m_pUdpSocket->joinMulticastGroup(m_groupAddress4);

    connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &streamClientWidget::on_readyRead);
}

void streamClientWidget::on_connected() {
    m_pTimer->stop();
}
void streamClientWidget::on_readyRead() {
    QByteArray datagram;

    datagram.resize(int(m_pUdpSocket->pendingDatagramSize()));
    m_pUdpSocket->readDatagram(datagram.data(), datagram.size());

    QPixmap image;
    image.loadFromData(datagram);
    QPalette palette;
    image = image.scaled(QSize(1024, 768));
    palette.setBrush(QPalette::Window, QBrush(image));
    setPalette(palette);
    show();
}

void streamClientWidget::on_disconnected() {
    m_pTimer->start(1000);
}

void streamClientWidget::on_timeout() {
    m_pSocket->abort();
    m_pSocket->connectToHost(m_strHost, m_port);
}
