#ifndef stream_FACTORY_H
#define stream_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rotracking_plugin.h>
#include "stream_worker.h"

class stream_factory : public rotrackingPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.zitro.zone.pio.stream/1.0" FILE "")
    Q_INTERFACES(rotrackingPlugin)

public:
   stream_factory ();
   ~stream_factory();
   int init       (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release   ();
};
#endif
