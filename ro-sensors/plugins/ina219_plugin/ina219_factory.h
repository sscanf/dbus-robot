#ifndef ina219_FACTORY_H
#define ina219_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rosensors_plugin.h>
#include "ina219_worker.h"

class ina219_factory : public rosensorsPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.rosensors/1.0")
    Q_INTERFACES(rosensorsPlugin)

public:
   ina219_factory  ();
   ~ina219_factory ();
   int init        (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release    ();

private:
    QList <ina219Worker *> m_listManagers;
};
#endif
