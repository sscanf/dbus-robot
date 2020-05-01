#include <QDebug>
#include <QVector3D>
#include <math.h>
#include "mpu92_worker.h"
#include <rosensors_plugin.h>
#include "mpu92_worker_interface.h"

mpu92Worker::mpu92Worker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled          = bEnabled;
    m_strDescription    = strDescription;
    m_strAddress        = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new mpu92_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);

    m_pTimer = new QTimer(this);
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT(onTimeout()));
    m_pTimer->start(5);
}

void mpu92Worker::setlTest()
{
    qDebug() << "Performing SelfTest ... ";
    float SelfTest[6];
    m_c9250.selfTest (SelfTest);
    qDebug() << "x-axis self test: acceleration trim within : " << SelfTest[0] << "% of factory value";
    qDebug() << "y-axis self test: acceleration trim within : " << SelfTest[1] << "% of factory value";
    qDebug() << "z-axis self test: acceleration trim within : " << SelfTest[2] << "% of factory value";
    qDebug() << "x-axis self test: gyration trim within : " << SelfTest[3] << "% of factory value";
    qDebug() << "y-axis self test: gyration trim within : " << SelfTest[4] << "% of factory value";
    qDebug() << "z-axis self test: gyration trim within : " << SelfTest[5] << "% of factory value";
}

void mpu92Worker::onTimeout()
{
    m_accelPos = m_c9250.getAccelPosition();
    m_gyroPos  = m_c9250.getGyroPosition();
    m_magPos   = m_c9250.getMagPosition();

//    qDebug("%012.2f %012.2f %012.2f",m_magPos.x(), m_magPos.y(), m_magPos.z());
//    qDebug() << m_accelPos.x()*1000 << m_accelPos.y()*1000 << m_accelPos.z()*1000;

    int sroll=1;
    int spitch=-1;
    int syaw=1;

    int roll = sroll*m_magPos.x();
    int pitch = spitch*m_magPos.y();
    int yaw = syaw*m_magPos.z();

    float heading = 180/M_PI * atan2 (pitch,roll);
    if (heading < 0)
        heading += 360;

    if (heading < 0)
        heading += 2*M_PI;

    if (heading > 2*M_PI)
        heading -= 2*M_PI;

//    float dip=180/M_PI*atan2(sqrt(roll*roll+pitch*pitch),yaw);
//    float dip=180/M_PI*atan(yaw/sqrt(roll*roll+pitch*pitch));
    m_listPos.append (heading);
    m_listYaw.append (yaw);
//    qDebug("%d",yaw);

    if (m_countAvg++ == 5) {
        float avg=0.;
        int yawAvg=0.;
        for (int n=0;n<m_countAvg;n++) {
            avg+=m_listPos.at(n);
            yawAvg+=m_listYaw.at(n);
        }
        qDebug("%06.2f %d",avg/m_countAvg, yawAvg/m_countAvg);
        m_countAvg=0;
        m_listPos.clear();
    }


}
