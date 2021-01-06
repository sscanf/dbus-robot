#include <QDebug>
#include <QThread>
#include "zoposircam.h"

ZOPosIRCam::ZOPosIRCam(QObject *parent) :
    QObject(parent),
    m_slaveAddress(0x58)
{
}

void ZOPosIRCam::cameraInit()
{
    m_zoi2c.setAddress(m_slaveAddress);
    m_zoi2c.send (QByteArray("\x30\x01",2)); QThread::msleep(10);
    m_zoi2c.send (QByteArray("\x30\x08",2)); QThread::msleep(10);
    m_zoi2c.send (QByteArray("\x06\x90",2)); QThread::msleep(10);
    m_zoi2c.send (QByteArray("\x80\xc0",2)); QThread::msleep(10);
    m_zoi2c.send (QByteArray("\x1a\x40",2)); QThread::msleep(10);
    m_zoi2c.send (QByteArray("\x33\x33",2)); QThread::msleep(10);
    QThread::msleep(100);
}

void ZOPosIRCam::process()
{
    unsigned char data[16];
    int Ix[4];
    int Iy[4];
    int s;

    cameraInit();

    forever{
        m_zoi2c.send (0x36); //IR sensor read
        memset (data,0,16);
        int ret = m_zoi2c.receive (data,16);
        if (ret<0) {
            qDebug() << m_zoi2c.getErrorMessage();
        }

        Ix[0] = static_cast<unsigned char>(data[1]);
        Iy[0] = static_cast<unsigned char>(data[2]);
        s   = static_cast<unsigned char>(data[3]);
        Ix[0] += (s & 0x30) <<4;
        Iy[0] += (s & 0xC0) <<2;

        Ix[1] = static_cast<unsigned char>(data[4]);
        Iy[1] = static_cast<unsigned char>(data[5]);
        s   = static_cast<unsigned char>(data[6]);
        Ix[1] += (s & 0x30) <<4;
        Iy[1] += (s & 0xC0) <<2;

        Ix[2] = static_cast<unsigned char>(data[7]);
        Iy[2] = static_cast<unsigned char>(data[8]);
        s   = static_cast<unsigned char>(data[9]);
        Ix[2] += (s & 0x30) <<4;
        Iy[2] += (s & 0xC0) <<2;

        Ix[3] = static_cast<unsigned char>(data[10]);
        Iy[3] = static_cast<unsigned char>(data[11]);
        s   = static_cast<unsigned char>(data[12]);
        Ix[3] += (s & 0x30) <<4;
        Iy[3] += (s & 0xC0) <<2;

        for(int i=0; i<4; i++) {
          printf("Ix[%d] = %d\n", i,static_cast<int>(Ix[i]));
          printf("Iy[%d] = %d\n", i,static_cast<int>(Iy[i]));
          fflush (stdout);
        }
        printf ("\n");
        emit detection (QPoint (Ix[0],Iy[0]),
                        QPoint (Ix[1],Iy[1]),
                        QPoint (Ix[2],Iy[2]),
                        QPoint (Ix[3],Iy[3]));

        QThread::msleep(15);
    }
}
