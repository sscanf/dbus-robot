#ifndef @@NAME@@_FACTORY_H
#define @@NAME@@_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <zoaudio_plugin.h>
#include "@@name@@_worker.h"

class @@name@@_factory : public zoaudioPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.zitro.zone.pio.@@name@@/1.0" FILE "")
    Q_INTERFACES(zoaudioPlugin)

public:
   @@name@@_factory  ();
   ~@@name@@_factory ();
   int init              (QString strName, QString strDescription=QString(), bool bEnabled=true);
   void release          ();

private:
    QList <@@name@@Worker *> m_listManagers;
};
#endif
