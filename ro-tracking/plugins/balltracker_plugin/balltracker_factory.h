#ifndef balltracker_FACTORY_H
#define balltracker_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rotracking_plugin.h>
#include "balltracker_worker.h"

class balltracker_factory : public rotrackingPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.balltracker/1.0" )
    Q_INTERFACES(rotrackingPlugin)

public:
   balltracker_factory  ();
   ~balltracker_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <balltrackerWorker *> m_listManagers;
};
#endif
