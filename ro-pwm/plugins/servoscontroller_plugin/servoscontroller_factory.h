#ifndef servoscontroller_FACTORY_H
#define servoscontroller_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <pwm_plugin.h>
#include "servoscontroller_worker.h"

class servoscontroller_factory : public pwmPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.servoscontroller/1.0" )
    Q_INTERFACES(pwmPlugin)

public:
   servoscontroller_factory  ();
   ~servoscontroller_factory ();
   int init              (Adafruit_PWMServoDriver *pPwm, QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <servoscontrollerWorker *> m_listManagers;
};
#endif
