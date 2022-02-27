#ifndef L298N_FACTORY_H
#define L298N_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <roengines_plugin.h>
#include "l298n_worker.h"

class l298n_factory : public roenginesPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.zitro.zone.pio.l298n/1.0" )
    Q_INTERFACES(roenginesPlugin)

public:
   l298n_factory  ();
   ~l298n_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <l298nWorker *> m_listManagers;
};
#endif
