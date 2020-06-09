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

    m_pUsbBufferTx = new quint8[USB_BUFFER_LEN];
    m_pUsbBufferRx = new quint8[USB_BUFFER_LEN];

    m_pTimer = new QTimer (this);
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT (on_timeout()));
    m_pTimer->start (100);

    m_pCheckMotorsTimer = new QTimer(this);
    connect (m_pCheckMotorsTimer,SIGNAL (timeout()), this, SLOT (on_CheckMotors()));
}

void piccontrollerWorker::getEngineData()
{
    unsigned int speed;
    if (m_libUsb.get (m_pUsbBufferRx,USB_BUFFER_LEN)) {
        //Error de USB
        //Posiblemente el USB se ha desconectado.
        emit error(true);
    } else {
        speed      = m_pUsbBufferRx[0] << 8;
        speed     |= m_pUsbBufferRx[1];
        m_realSpeed = (int16_t)(speed)*-1;

        m_encoderLeft   = m_pUsbBufferRx[2] << 8;
        m_encoderLeft  |= m_pUsbBufferRx[3];
        m_encoderRight  = m_pUsbBufferRx[4] << 8;
        m_encoderRight |= m_pUsbBufferRx[5];

        if (m_encoderLeft != m_lastEncoderLeft) {
            m_lastEncoderLeft=m_encoderLeft;
            emit encoderLeftChange(m_encoderLeft);
        }

        if (m_encoderRight != m_lastEncoderRight) {
            m_lastEncoderRight=m_encoderRight;
            emit encoderRightChange(m_encoderRight);
        }
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

void piccontrollerWorker::on_CheckMotors()
{
    qDebug() << "Checking Motors : " << m_encoderLeft << m_encoderRight << getSpeed();
    if ((m_encoderLeft == 0) && getSpeed() ) {
        emit error (ERR_MOTOR_LEFT);
    }
    if ((m_encoderRight == 0) && getSpeed() ) {
        emit error (ERR_MOTOR_RIGHT);
    }
}

int piccontrollerWorker::getSpeed()
{
    return m_realSpeed*-1;
}

int piccontrollerWorker::getEncoderLeft()
{
    return m_encoderLeft;
}

int piccontrollerWorker::getEncoderRight()
{
    return m_encoderRight;
}

void piccontrollerWorker::setSpeed(int speed)
{
    int bPid = 1;
//    speed*=-1;
    if (speed>m_maxSpeed)
        speed=m_maxSpeed;

    if (speed<-m_maxSpeed)
        speed=-m_maxSpeed;

    m_pUsbBufferTx[VELOCIDAD_H]=speed>>8;
    m_pUsbBufferTx[VELOCIDAD_L]=speed&0x00ff;

    m_pUsbBufferTx[MOTOR_LEFT_H]=speed>>8;
    m_pUsbBufferTx[MOTOR_LEFT_L]=speed&0x00ff;

    m_pUsbBufferTx[MOTOR_RIGHT_H]=speed>>8;
    m_pUsbBufferTx[MOTOR_RIGHT_L]=speed&0x00ff;

    m_pUsbBufferTx[BPID_H]=bPid>>8;
    m_pUsbBufferTx[BPID_L]=bPid&0x00ff;

    m_libUsb.send (m_pUsbBufferTx, USB_BUFFER_LEN);

    if (speed) {
        m_pCheckMotorsTimer->start (2000);
    } else
        m_pCheckMotorsTimer->stop();

    if (speed>0)
        m_direction = DIR_FORWARDING;
    else if (speed<0)
        m_direction = DIR_BACKWARDING;
    else
        m_direction = DIR_STOPPED;
}

void piccontrollerWorker::setDualSpeed(int left, int right)
{
    int bPid = 1;
    if (left == right) {
        if (left>0)
            m_direction = DIR_FORWARDING;
        else if (left<0)
            m_direction = DIR_BACKWARDING;
        else
            m_direction = DIR_STOPPED;
    }

    if (left > right)
        m_direction = DIR_TURNING_RIGHT;

    if (left < right)
        m_direction = DIR_TURNING_RIGHT;


    if (left>m_maxSpeed)
        left=m_maxSpeed;

    if (right>m_maxSpeed)
        right=m_maxSpeed;

    if (left<-m_maxSpeed)
        left=-m_maxSpeed;

    if (right<-m_maxSpeed)
        right=-m_maxSpeed;

    m_pUsbBufferTx[VELOCIDAD_H]=left>>8;
    m_pUsbBufferTx[VELOCIDAD_L]=left&0x00ff;

    m_pUsbBufferTx[MOTOR_LEFT_H]=left>>8;
    m_pUsbBufferTx[MOTOR_LEFT_L]=left&0x00ff;

    m_pUsbBufferTx[MOTOR_RIGHT_H]=right>>8;
    m_pUsbBufferTx[MOTOR_RIGHT_L]=right&0x00ff;

    m_pUsbBufferTx[BPID_H]=bPid>>8;
    m_pUsbBufferTx[BPID_L]=bPid&0x00ff;

    m_libUsb.send (m_pUsbBufferTx, USB_BUFFER_LEN);
    if (left || right) {
        m_pCheckMotorsTimer->start (2000);
    } else if ( !left && !right)
        m_pCheckMotorsTimer->stop();
}

void piccontrollerWorker::setMaximumSpeed(int speed)
{
    m_maxSpeed = speed;
}

int piccontrollerWorker::getDirection()
{
    return m_direction;
}

void piccontrollerWorker::setTurn(int turn)
{
    int engineLeft =0;
    int engineRight=0;

    if (m_speed==0) {
        if (turn>0) {
            engineRight=turn;
            engineLeft=turn*-1;
        } else {
            engineRight=turn;
            engineLeft=turn*-1;
        }
    } else {
        if (turn>0) {
            engineRight=m_speed+turn;
            engineLeft=m_speed;
        } else {
            engineLeft=m_speed+turn;
            engineRight=m_speed;
        }
    }
    setDualSpeed (engineLeft, engineRight);

    if (engineLeft> engineRight)
        m_direction = DIR_TURNING_RIGHT;

    if (engineLeft < engineRight)
        m_direction = DIR_TURNING_RIGHT;
}

