#ifndef balltracker_FACTORY_H
#define balltracker_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rotracking_plugin.h>
#include "irtracker_worker.h"

class irtracker_factory : public rotrackingPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.balltracker/1.0" )
    Q_INTERFACES(rotrackingPlugin)

public:
   irtracker_factory  ();
   ~irtracker_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <irtrackerWorker *> m_listManagers;
};
#endif
