#ifndef ROBOTVIEWER_H
#define ROBOTVIEWER_H

#include <QQuickItem>
#include <QTcpSocket>
#include <QImage>
#include <QTimer>

#define ILOW_H  0
#define IHIGH_H 188
#define ILOW_S  92
#define IHIGH_S 255
#define ILOW_V  105
#define IHIGH_V 255

struct values
{
    quint8 m_iImgSelect;
    quint8 m_iLowH;
    quint8 m_iHighH;
    quint8 m_iLowS;
    quint8 m_iHighS;
    quint8 m_iLowV;
    quint8 m_iHighV;

};

class RobotViewer : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(RobotViewer)

    Q_PROPERTY(int lowH  READ lowH  WRITE setLowH )
    Q_PROPERTY(int highH READ highH WRITE setHighH)
    Q_PROPERTY(int lowS  READ lowS  WRITE setLowS)
    Q_PROPERTY(int highS READ highS WRITE setHighS)
    Q_PROPERTY(int lowV  READ lowV  WRITE setLowV)
    Q_PROPERTY(int highV READ highV WRITE setHighV)

public:
    void setLowH (int value);
    void setHighH(int value);
    void setLowS (int value);
    void setHighS(int value);
    void setHighV(int value);
    void setLowV (int value);

    int lowH ();
    int highH();
    int lowS ();
    int highS();
    int lowV ();
    int highV();
private:
    void conectamos (void);
    void sendData (void);

private:
    QTcpSocket *m_pSocket;
    QTcpSocket *m_pCtrlSocket;
    quint64     m_totalBytes;
    QByteArray  m_arrImage;
    quint64     m_bytesRead;
    QByteArray *m_pData;
    QWidget    *m_pWidget;
    QTimer     *m_pTimer;
    values     *m_pValues;
    QImage      m_image;

public slots:
    void on_connected();
    void on_ctrlConnected();
    void on_readyRead();
    void on_disconnected();
    void on_ctrlDisconnected();
    void on_timeout();
    void on_error(QAbstractSocket::SocketError);

public:
    RobotViewer(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
    ~RobotViewer();
};

#endif // ROBOTVIEWER_H
