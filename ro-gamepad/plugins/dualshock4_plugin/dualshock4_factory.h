#ifndef dualshock4_FACTORY_H
#define dualshock4_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <gamepad_plugin.h>
#include "dualshock4_worker.h"

class dualshock4_factory : public gamepadPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.dualshock4/1.0")
    Q_INTERFACES(gamepadPlugin)

public:
   dualshock4_factory  ();
   ~dualshock4_factory ();
   int init            (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release        ();

private:
    QList <dualshock4Worker *> m_listManagers;
};
#endif
