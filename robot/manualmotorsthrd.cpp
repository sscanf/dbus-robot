#include <QDebug>
#include "manualmotorsthrd.h"

manualMotorsThrd::manualMotorsThrd(QDBusConnection connection, QThread *parent) :
    QThread(parent)
{
    m_pEnginesIface = new QDBusInterface ("com.robot.roengines",
                                         "/engines",
                                         "com.robot.roengines",
                                         connection,
                                         this);
    if (!m_pEnginesIface->isValid()){
        qDebug() << "Engines interface is not valid";
    }

}

void manualMotorsThrd::run()
{
    int ret;
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisLeftX",
                                              this,
                                              SLOT (onAxisLeftX(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisLeftY",
                                              this,
                                              SLOT (onAxisLeftY(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }

}

void manualMotorsThrd::terminate()
{
    int ret;
    ret=QDBusConnection::systemBus().disconnect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisLeftX",
                                              this,
                                              SLOT (onAxisLeftX(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret=QDBusConnection::systemBus().disconnect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisLeftY",
                                              this,
                                              SLOT (onAxisLeftY(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
}

double manualMotorsThrd::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void manualMotorsThrd::onAxisLeftX(double value)
{
    int speed = map (value, -1,1, -MAX_SPEED/2, MAX_SPEED/2);
    if (value<0)
        m_valL = qAbs(speed)*-1;
    else
        m_valR = qAbs(speed)*-1;

    if (value==0) {
        m_valR=0;
        m_valL=0;
    }
    setSpeed ();
}

void manualMotorsThrd::onAxisLeftY(double value)
{
    m_speed = map (value, -1,1, -MAX_SPEED/2, MAX_SPEED/2);
    setSpeed();
}

void manualMotorsThrd::setSpeed()
{
    int speedL = (m_speed-m_valL)*-1;
    int speedR = (m_speed-m_valR)*-1;

    if (speedL<-15)
        speedL=-15;

    if (speedR<-15)
        speedR=-15;

    qDebug() << speedL << speedR;
    m_pEnginesIface->call ("setDualSpeed", QVariant::fromValue(qint32(speedL)), QVariant::fromValue(qint32(speedR)));
}
