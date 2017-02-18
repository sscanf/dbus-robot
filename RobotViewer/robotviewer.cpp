#include <QSGSimpleTextureNode>
#include <QSGTexture>
#include <QQuickWindow>
#include <QDebug>
#include <QIODevice>
#include "robotviewer.h"

RobotViewer::RobotViewer(QQuickItem *parent):
    QQuickItem(parent)
{
    m_pSocket = nullptr;
    setFlag(ItemHasContents, true);
    m_totalBytes = 1;
    m_pData = new QByteArray();
    m_pValues = new struct values;
    m_pValues->m_iImgSelect=1;
    m_pValues->m_iLowH =ILOW_H;
    m_pValues->m_iHighH=IHIGH_H;
    m_pValues->m_iLowS =ILOW_S;
    m_pValues->m_iHighS=IHIGH_S;
    m_pValues->m_iLowV =ILOW_V;
    m_pValues->m_iHighV=IHIGH_V;
    m_pTimer = new QTimer();
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT (on_timeout()));

    m_pSocket = new QTcpSocket (this);
    connect (m_pSocket,SIGNAL (connected()),    this, SLOT (on_connected()));
    connect (m_pSocket,SIGNAL (readyRead()),    this, SLOT (on_readyRead()));
    connect (m_pSocket,SIGNAL (disconnected()), this, SLOT (on_disconnected()));
    connect (m_pSocket,SIGNAL (error(QAbstractSocket::SocketError)), this, SLOT (on_error(QAbstractSocket::SocketError)));

    m_pCtrlSocket = new QTcpSocket (this);
    connect (m_pCtrlSocket,SIGNAL (connected()),    this, SLOT (on_ctrlConnected()));
    connect (m_pCtrlSocket,SIGNAL (disconnected()), this, SLOT (on_ctrlDisconnected()));
    conectamos();

    //m_pTimer->start (1000);
}

QSGNode *RobotViewer::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleTextureNode();
    }
    QSGTexture *texture = window()->createTextureFromImage(m_image);
    node->setTexture(texture);
    node->setRect(boundingRect());
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

void RobotViewer::on_timeout()
{
}

void RobotViewer::on_error(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED (socketError);
    qDebug() << m_pSocket->errorString();
}

void RobotViewer::setLowH(int value)
{
   m_pValues->m_iLowH = value;
   sendData();
}

void RobotViewer::setHighV(int value)
{
   m_pValues->m_iHighV = value;
   sendData();
}

void RobotViewer::setLowV(int value)
{
   m_pValues->m_iLowV = value;
   sendData();
}

void RobotViewer::setHighH(int value)
{
   m_pValues->m_iHighH = value;
   sendData();
}

void RobotViewer::setLowS(int value)
{
   m_pValues->m_iLowS = value;
   sendData();
}

void RobotViewer::setHighS(int value)
{
   m_pValues->m_iHighS = value;
   sendData();
}

int RobotViewer::lowH()
{
    return m_pValues->m_iLowH;
}

int RobotViewer::highH()
{
    return m_pValues->m_iHighH;
}

int RobotViewer::lowS()
{
    return m_pValues->m_iLowS;
}

int RobotViewer::highS()
{
    return m_pValues->m_iHighS;
}

int RobotViewer::lowV()
{
    return m_pValues->m_iLowV;
}

int RobotViewer::highV()
{
    return m_pValues->m_iHighV;
}

void RobotViewer::conectamos()
{
    qDebug() << "Conneting ... ";
    m_pSocket->abort();
    m_pSocket->reset();
    m_pSocket->close();
    m_pSocket->connectToHost("192.168.0.1",1234);

    m_pCtrlSocket->abort();
    m_pCtrlSocket->reset();
    m_pCtrlSocket->close();
    m_pCtrlSocket->connectToHost("192.168.0.1",1235);
}

void RobotViewer::sendData()
{
    m_pCtrlSocket->write ((const char *)m_pValues, sizeof(struct values));
    quint8 pepe[sizeof (values)];
    memcpy (pepe,m_pValues,sizeof(values));

    for (int n=0;n<sizeof(values);n++) {
        printf ("%x ",pepe[n]);
    }
    printf ("\n");
}

void RobotViewer::on_connected()
{
    m_pTimer->stop();
    qDebug() << "Connected!";
}

void RobotViewer::on_ctrlConnected()
{
    qDebug() << "Control channel connected!";
}

void RobotViewer::on_readyRead()
{
    QDataStream stream (m_pSocket);

    do {
        if (m_bytesRead == 0) {
            m_pData->clear();
            stream >> m_bytesRead;
            if (m_bytesRead > 90000)
                m_bytesRead = 0;
        }

        m_pData->append (m_pSocket->readAll());

        if (m_pData->size() >= m_bytesRead) {
            m_bytesRead=0;
            m_image.loadFromData(*m_pData);
            this->update();
        }

        qDebug() << m_pData->size();
    }while (m_pSocket->bytesAvailable());
}

void RobotViewer::on_disconnected()
{
    qDebug() << "Disconnected!";
    conectamos();
}

void RobotViewer::on_ctrlDisconnected()
{
    qDebug() << "Control channel disconnected!";
}

RobotViewer::~RobotViewer()
{
}
