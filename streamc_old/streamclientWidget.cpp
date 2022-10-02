#include "streamclientWidget.h"

streamClientWidget::streamClientWidget(QString host, int port, QWidget* parent)
    : QWidget(parent)
    , m_port(port)
    , m_strHost(host)
{
    setMinimumSize(QSize(1024, 768));
    resize(QSize(1024, 768));
    m_bytesRead = 0;
    m_pData     = new QByteArray();

    setWindowTitle(QStringLiteral("This is QTCPServer Window!"));
    m_pSocket = new QTcpSocket(this);
    // connect (m_pSocket,SIGNAL (connected()), this, SLOT (on_connected()));
    connect(m_pSocket, &QIODevice::readyRead, this, &streamClientWidget::on_readyRead);
    connect(m_pSocket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_pTimer->start(1000);
}

void streamClientWidget::on_connected()
{
    m_pTimer->stop();
}

void streamClientWidget::on_readyRead()
{
    QDataStream stream(m_pSocket);
    if (m_bytesRead == 0) {
        m_pData->clear();
        stream >> m_bytesRead;
        if (m_bytesRead > 90000)
            m_bytesRead = 0;
    }
    m_pData->append(m_pSocket->readAll());

    if (m_pData->size() >= m_bytesRead) {
        m_bytesRead = 0;
        QPixmap image;
        image.loadFromData(*m_pData);
        QPalette palette;
        image = image.scaled(QSize(1024, 768));
        palette.setBrush(QPalette::Background, QBrush(image));
        setPalette(palette);
        show();
    }
}

void streamClientWidget::on_disconnected()
{
    m_pTimer->start(1000);
}

void streamClientWidget::on_timeout()
{
    m_pSocket->connectToHost(m_strHost, m_port);
}
