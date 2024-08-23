#ifndef facetracker_FACTORY_H
#define facetracker_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rotracking_plugin.h>
#include "facetracker_worker.h"

class facetracker_factory : public rotrackingPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.facetracker/1.0" )
    Q_INTERFACES(rotrackingPlugin)

public:
   facetracker_factory  ();
   ~facetracker_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <facetrackerWorker *> m_listManagers;
};
#endif
