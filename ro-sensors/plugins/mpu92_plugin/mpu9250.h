#ifndef MPU9250_H
#define MPU9250_H

#include <QObject>
#include <zoi2c.h>
#include <QVector3D>
#include <mpu9250_registers.h>
#include <QTimer>
#include "qsoc.h"

#define MPU9250_ADDRESS   0x69

enum Ascale {
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_16G
};

enum Gscale {
  GFS_250DPS = 0,
  GFS_500DPS,
  GFS_1000DPS,
  GFS_2000DPS
};

enum Mscale {
  MFS_14BITS = 0, // 0.6 mG per LSB
  MFS_16BITS      // 0.15 mG per LSB
};

class mpu9250 : public QObject
{
    Q_OBJECT
public:
    explicit mpu9250     (QObject *parent = nullptr);
    void      selfTest        (float *destination);
    void      enableInterrupt (QString strGPIOName, int (*callback)(void *), void *ptr);
    void      readAccelData   ();
    void      readGyroData    ();
    void      readMagData     ();
    quint8    interruptStatus ();
    QVector3D getGyroPosition ();
    QVector3D getAccelPosition();
    QVector3D getMagPosition  ();
    float     getTemperature  ();

private:
    void  initMPU9250     ();
    void  initAK8963      (float *destination);
    void  calibrateMPU9250(QVector3D *dest1, QVector3D *dest2);
    float getAres();
    float getGres();
    float getMres();

private:
    zoi2c      m_i2c9250;
    zoi2c      m_i2cMagneto;
    QSoc       m_soc;
    uint8_t    m_Gscale = GFS_250DPS;
    uint8_t    m_Ascale = AFS_2G;
    uint8_t    m_Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
    uint8_t    m_Mmode  = 0x02;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read
    float      m_gRes;
    float      m_mRes;      // scale resolutions per LSB for the sensors
    QVector3D  m_accelPos;
    QVector3D  m_gyroPos;
    QVector3D  m_magPos;
    float      m_magCalibration[3]= {0, 0, 0}; //Factory mag calibration
    QTimer    *m_pTimer;

signals:

private slots:
    void onTimeout();

};

#endif // MPU9250_H
