#ifndef GAMEPAD_MANAGER_H
#define GAMEPAD_MANAGER_H

#include <QCoreApplication>
#include <QTimer>
#include <QList>
#include <QPluginLoader>
#include <QtDBus/QtDBus>
#include "gamepad_plugin.h"

#define PLUGINS_PATH        "/usr/lib/"
#define GAMEPAD_CONFIG_FILE "/etc/robot/rogamepad_config.xml"

class gamepadManager : public QCoreApplication
{
    Q_OBJECT
    Q_CLASSINFO ("D-Bus Interface","com.robot.rogamepad")

public:
    explicit gamepadManager(int & argc, char ** argv);

public Q_SLOTS:
    QString getVersion(){
        return APP_VERSION;
    }
    QStringList getObjects ();
    QStringList getObjectsByType (QString strType);
    QStringList getObjectsByName (QString strName);

private: //Functions
    QPluginLoader *loadPlugin (const char *pstrPlugin);
    int            parseConfig(QString strFilePath);

private: //Variables

    QDBusConnection          m_connection;
    QList <gamepadPlugin*>  m_plugins;         /**< Plugins list*/
    QList <QPluginLoader *>  m_hPlugins;        /**< Plugin handlers list*/
};

#endif // GAMEPAD_MANAGER_H
