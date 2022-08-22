#ifndef STREAMCLIENT_H
#define STREAMCLIENT_H
#include <QTcpSocket>
#include <QTimer>
#include <QWidget>

class streamClientWidget : public QWidget {
    Q_OBJECT

public:
    streamClientWidget(QString host, int port, QWidget* parent = nullptr);

private:
    QTcpSocket* m_pSocket;
    int         m_port;
    QString     m_strHost;
    QTimer*     m_pTimer;
    QByteArray* m_pData;
    qint32      m_bytesRead;

private slots:
    void on_connected();
    void on_readyRead();
    void on_disconnected();
    void on_timeout();
};

#endif // STREAMCLIENT_H
