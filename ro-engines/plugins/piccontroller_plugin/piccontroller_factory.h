#ifndef piccontroller_FACTORY_H
#define piccontroller_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <roengines_plugin.h>
#include "piccontroller_worker.h"

class piccontroller_factory : public roenginesPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.piccontroller/1.0" )
    Q_INTERFACES(roenginesPlugin)

public:
   piccontroller_factory  ();
   ~piccontroller_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <piccontrollerWorker *> m_listManagers;
};
#endif
