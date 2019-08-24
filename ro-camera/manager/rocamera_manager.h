#ifndef ROCAMERA_MANAGER_H
#define ROCAMERA_MANAGER_H

#include <QCoreApplication>
#include <QTimer>
#include <QList>

#include <QPluginLoader>
#include <QtDBus/QtDBus>

#include "rocamera_plugin.h"

class rocameraManager : public QCoreApplication
{
    Q_OBJECT
    Q_CLASSINFO ("D-Bus Interface","com.robot.rocamera")

public:
    explicit rocameraManager(int & argc, char ** argv);

public Q_SLOTS:
    QString getVersion(){
        return APP_VERSION;
    }

    QStringList getObjects ();
    QStringList getObjectsByType (QString strType);
    QStringList getObjectsByName (QString strName);

private: //Functions
    QPluginLoader  *loadPlugin       (const char *pstrPlugin);
    int             parseConfig      (QString strFilePath);

private: //Variables

    QDBusConnection          m_connection;
    QList <rocameraPlugin*>  m_plugins;         /**< Plugins list*/
    QList <QPluginLoader *>  m_hPlugins;        /**< Plugin handlers list*/
};

#endif // ROCAMERA_MANAGER_H
