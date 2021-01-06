#include <QDebug>
#include "manualcamerathrd.h"

manualCameraThrd::manualCameraThrd(QDBusConnection connection, QThread *parent) :
    QThread(parent)
{
    m_pPWMIface = new QDBusInterface ("com.robot.pwm",
                                         "/servos",
                                         "com.robot.servoscontroller",
                                         connection,
                                         this);

}

void manualCameraThrd::run()
{
    int ret;
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisRightX",
                                              this,
                                              SLOT (onAxisRightX(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "axisRightY",
                                              this,
                                              SLOT (onAxisRightY(double)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
}

void manualCameraThrd::terminate()
{
    int ret;
    ret=QDBusConnection::systemBus().disconnect("com.robot.rogamepad",
                                                "/rogamepad/dualshock4",
                                                "com.robot.rogamepad.dualshock4",
                                                "axisRightX",
                                                this,
                                                SLOT (onAxisRightX(double)));
    if (!ret) {
        qDebug() << "Error disconnecting gamepad";
    }
    ret=QDBusConnection::systemBus().disconnect("com.robot.rogamepad",
                                                "/rogamepad/dualshock4",
                                                "com.robot.rogamepad.dualshock4",
                                                "axisRightY",
                                                this,
                                                SLOT (onAxisRightY(double)));
    if (!ret) {
        qDebug() << "Error disconnecting gamepad";
    }
}

double manualCameraThrd::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void manualCameraThrd::onAxisRightX(double value)
{
    int angle = map (value, -1,1, 180, 0);
    if (m_processing==false) {
        m_processing=true;
        m_pPWMIface->call ("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(angle)));
        m_processing=false;
    }
}

void manualCameraThrd::onAxisRightY(double value)
{
    int angle = map (value, -1,1, 0, 120);
    if (m_processing==false) {
        m_processing=true;
        m_pPWMIface->call ("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(angle)));
        m_processing=false;
    }
}
