#ifndef hcsr04_FACTORY_H
#define hcsr04_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rosensors_plugin.h>
#include "distance_worker.h"

class distance_factory : public rosensorsPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.rosensors/1.0")
    Q_INTERFACES(rosensorsPlugin)

public:
   distance_factory  ();
   ~distance_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <distanceWorker *> m_listManagers;
};
#endif
