#include <QDebug>
#include "piccontroller_worker.h"
#include "piccontroller_worker_interface.h"

piccontrollerWorker::piccontrollerWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled          = bEnabled;
    m_strDescription    = strDescription;
    m_strAddress        = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);
    m_pUsbBufferTx      = 0;
    m_pUsbBufferRx      = 0;

    new piccontroller_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
    m_connection.registerService(strAddress.replace("/","."));

    m_pUsbBufferTx = new quint8[USB_BUFFER_LEN];
    m_pUsbBufferRx = new quint8[USB_BUFFER_LEN];

    m_pTimer = new QTimer (this);
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT (on_timeout()));
    m_pTimer->start (1000);
}

void piccontrollerWorker::getEngineData()
{
    if (m_libUsb.get (m_pUsbBufferRx,USB_BUFFER_LEN)) {
        //Error de USB
        //Posiblemente el SUB se ha desconectado.
        emit error(true);
    } else {
        m_speed      = m_pUsbBufferRx[0] << 8;
        m_speed     |= m_pUsbBufferRx[1];
        m_encoder1   = m_pUsbBufferRx[2] << 8;
        m_encoder1  |= m_pUsbBufferRx[3];
        m_encoder2   = m_pUsbBufferRx[4] << 8;
        m_encoder2  |= m_pUsbBufferRx[5];
    }
}

void piccontrollerWorker::on_timeout()
{
    if (!m_libUsb.isOpen()) {
        if (!m_libUsb.open (0x04d8, 0x4541)) {
            memset (m_pUsbBufferTx, 0, USB_BUFFER_LEN);
            memset (m_pUsbBufferRx, 0, USB_BUFFER_LEN);
            m_libUsb.send (m_pUsbBufferTx, USB_BUFFER_LEN);
        }
    } else {
        getEngineData();
    }
}

int piccontrollerWorker::getSpeed()
{
    return m_speed;
}

int piccontrollerWorker::getEncoder1()
{
    return m_encoder1;
}

int piccontrollerWorker::getEncoder2()
{
    return m_encoder2;
}

void piccontrollerWorker::setSpeed(int speed)
{
    int bPid = 1;

    m_pUsbBufferTx[VELOCIDAD_H]=speed>>8;
    m_pUsbBufferTx[VELOCIDAD_L]=speed&0x00ff;

    m_pUsbBufferTx[MOTOR_LEFT_H]=speed>>8;
    m_pUsbBufferTx[MOTOR_LEFT_L]=speed&0x00ff;

    m_pUsbBufferTx[MOTOR_RIGHT_H]=speed>>8;
    m_pUsbBufferTx[MOTOR_RIGHT_L]=speed&0x00ff;

    m_pUsbBufferTx[BPID_H]=bPid>>8;
    m_pUsbBufferTx[BPID_L]=bPid&0x00ff;

    m_libUsb.send (m_pUsbBufferTx, USB_BUFFER_LEN);
}

void piccontrollerWorker::setDualSpeed(int left, int right)
{
    int bPid = 1;

    m_pUsbBufferTx[VELOCIDAD_H]=left>>8;
    m_pUsbBufferTx[VELOCIDAD_L]=left&0x00ff;

    m_pUsbBufferTx[MOTOR_LEFT_H]=left>>8;
    m_pUsbBufferTx[MOTOR_LEFT_L]=left&0x00ff;

    m_pUsbBufferTx[MOTOR_RIGHT_H]=right>>8;
    m_pUsbBufferTx[MOTOR_RIGHT_L]=right&0x00ff;

    m_pUsbBufferTx[BPID_H]=bPid>>8;
    m_pUsbBufferTx[BPID_L]=bPid&0x00ff;

    m_libUsb.send (m_pUsbBufferTx, USB_BUFFER_LEN);
}

void piccontrollerWorker::setTurn(int turn)
{
    int tmp = (m_speed - (turn+m_speed));
    int engineLeft  = 15;
    int engineRight = 15;

    if (tmp<0)
      engineLeft+=tmp;
    else
      engineRight-=tmp;

    engineLeft -= (m_speed*-1)+15;
    engineRight -= (m_speed*-1)+15;

    if (engineLeft<0) engineLeft=0;
    if (engineRight<0) engineRight=0;
    setDualSpeed (engineLeft, engineRight);
}
