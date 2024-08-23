#ifndef mpu950_FACTORY_H
#define mpu950_FACTORY_H

#include <QObject>
#include <QDBusConnection>
#include <rosensors_plugin.h>
#include "mpu92_worker.h"

class mpu92_factory : public rosensorsPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.robot.mpu950/1.0")
    Q_INTERFACES(rosensorsPlugin)

public:
    mpu92_factory();
    ~mpu92_factory();
    int  init(const QString &strName, const QString &strDescription = QString(), bool bEnabled = true);
    void release();

private:
    QList<mpu92Worker *> m_listManagers;
};
#endif
