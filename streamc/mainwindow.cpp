#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_totalBytes = 0;
    m_pData = new QByteArray();
    ui->setupUi(this);
    m_pSocket = new QTcpSocket (this);
    //connect (m_pSocket,SIGNAL (connected()), this, SLOT (on_connected()));
    connect (m_pSocket,SIGNAL (readyRead()), this, SLOT (on_readyRead()));
    connect (m_pSocket,SIGNAL (connected()), this, SLOT (on_connected()));
    connect (m_pSocket,SIGNAL (disconnected()), this, SLOT (on_disconnected()));


    m_pWidget = new QWidget();
    m_pTimer = new QTimer();
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT (on_timeout()));
    m_pTimer->start (1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connected()
{
    m_pTimer->stop();
}

void MainWindow::on_readyRead()
{
    QDataStream stream (m_pSocket);

    if (m_bytesRead == 0) {
        m_pData->clear();
        stream >> m_bytesRead;
        if (m_bytesRead > 90000)
            m_bytesRead = 0;
    }
    m_pData->append (m_pSocket->readAll());

    if (m_pData->size() >= m_bytesRead) {
        m_bytesRead=0;
        QImage image;
        image.loadFromData(*m_pData);
        QPalette palette;
        palette.setBrush(QPalette::Background,QBrush(image));

        m_pWidget->setWindowTitle("This is QTCPServer Window!");

        m_pWidget->setPalette(palette);
        m_pWidget->show();
    }
}

void MainWindow::on_disconnected()
{
    m_pTimer->start(1000);
}

void MainWindow::on_timeout()
{
    m_pSocket->connectToHost("192.168.0.1",1234);
}
