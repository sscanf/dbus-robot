#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_iLowH   (ILOW_H),
    m_iHighH  (IHIGH_H),
    m_iLowS   (ILOW_S),
    m_iHighS  (IHIGH_S),
    m_iLowV   (ILOW_V),
    m_iHighV  (IHIGH_V)
{
    m_totalBytes = 0;
    ui->setupUi(this);
    m_pSocket = new QTcpSocket (this);
    //connect (m_pSocket,SIGNAL (connected()), this, SLOT (on_connected()));
    connect (m_pSocket,SIGNAL (readyRead()), this, SLOT (on_readyRead()));
    connect (m_pSocket,SIGNAL (connected()), this, SLOT (on_connected()));
    connect (m_pSocket,SIGNAL (disconnected()), this, SLOT (on_disconnected()));

    connect (ui->highh,SIGNAL (valueChanged(int)), this, SLOT (on_highChanged(int)));
    connect (ui->highs,SIGNAL (valueChanged(int)), this, SLOT (on_highChanged(int)));
    connect (ui->highv,SIGNAL (valueChanged(int)), this, SLOT (on_highChanged(int)));

    connect (ui->lowh,SIGNAL (valueChanged(int)), this, SLOT (on_lowChanged(int)));
    connect (ui->lows,SIGNAL (valueChanged(int)), this, SLOT (on_lowChanged(int)));
    connect (ui->lowv,SIGNAL (valueChanged(int)), this, SLOT (on_lowChanged(int)));

    connect (ui->camBrightness, SIGNAL (valueChanged(int)), this, SLOT (on_cameraChanged(int)));

    ui->highh->setMaximum(255);
    ui->highs->setMaximum(255);
    ui->highv->setMaximum(255);
    ui->lowh->setMaximum(255);
    ui->lows->setMaximum(255);
    ui->lowv->setMaximum(255);

    ui->highh->setValue(m_iHighH);
    ui->highs->setValue(m_iHighS);
    ui->highv->setValue(m_iHighV);
    ui->lowh->setValue(m_iLowH);
    ui->lows->setValue(m_iLowS);
    ui->lowv->setValue(m_iLowV);

    m_pWidgetThreshold = new streamClientWidget("192.168.0.1",1235);
    m_pWidgetResult = new streamClientWidget("192.168.0.1",1236);
    m_pWidgetStatus = new statusWidget();
    m_pWidgetStatus->show();
    m_pWidgetPower = new powerWidget();
    m_pWidgetPower->show();


    m_pTimer = new QTimer();
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT (on_timeout()));
    m_pTimer->start (1000);

    on_lowChanged(0);
    on_highChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendData()
{
    QByteArray arr;
    QDataStream out (&arr, QIODevice::WriteOnly);
    out << m_iLowH << m_iHighH << m_iLowS << m_iHighS << m_iLowV << m_iHighV << ui->camBrightness->value();
    if (m_pSocket->isOpen())
        m_pSocket->write (arr);
}

void MainWindow::on_connected()
{
    m_pTimer->stop();
    sendData();
}

void MainWindow::on_readyRead()
{
}

void MainWindow::on_disconnected()
{
    m_pTimer->start(1000);
}

void MainWindow::on_timeout()
{
    m_pSocket->connectToHost("192.168.0.1",1234);
}

void MainWindow::on_lowhChanged(int value)
{
    m_iLowH = value;
    sendData();
}

void MainWindow::on_lowsChanged(int value)
{
    m_iLowS = value;
    sendData();
}

void MainWindow::on_lowvChanged(int value)
{
    m_iLowV = value;
    sendData();
}

void MainWindow::on_highhChanged(int value)
{
    m_iHighH = value;
    sendData();
}

void MainWindow::on_highsChanged(int value)
{
    m_iHighS = value;
    sendData();
}

void MainWindow::on_highvChanged(int value)
{
    m_iHighV = value;
    sendData();
}

void MainWindow::on_lowChanged(int value)
{
    Q_UNUSED (value);
    m_color.setHsv(ui->lowh->value(), ui->lows->value(), ui->lowv->value());
    QPalette pal = ui->displayL->palette();
    pal.setColor (QPalette::Window,m_color);
    ui->displayL->setPalette(pal);
}

void MainWindow::on_cameraChanged(int)
{
    sendData();
}

void MainWindow::on_highChanged(int value)
{
    Q_UNUSED (value);
    m_color.setHsv(ui->highh->value(), ui->highs->value(), ui->highv->value());
    QPalette pal = ui->displayH->palette();
    pal.setColor (QPalette::Window,m_color);
    ui->displayH->setPalette(pal);
    ui->displayH->repaint();
}
