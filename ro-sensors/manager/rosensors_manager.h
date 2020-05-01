#ifndef ROSENSORS_MANAGER_H
#define ROSENSORS_MANAGER_H

#include <QCoreApplication>
#include <QTimer>
#include <QList>
#include <QPluginLoader>
#include <QtDBus/QtDBus>
#include "rosensors_plugin.h"

class rosensorsManager : public QCoreApplication
{
    Q_OBJECT
    Q_CLASSINFO ("D-Bus Interface","com.robot.rosensors")

public:
    explicit rosensorsManager(int & argc, char ** argv);

public Q_SLOTS:
    QString getVersion(){
        return APP_VERSION;
    }

    /**
     * @brief Retrieve a string list with DBus address of all plugins enabled.
     * @return QStringList with all DBus plugins address
     *
     * Retrieve a string list with DBus address of all plugins that are enabled.
     */
    QStringList getObjects ();
    QStringList getObjectsByType (QString strType);


    /**
    * @brief Retrieve a string list with DBus address of all plugins enabled by name.
    * @param QString: Name of object to retrieve
    * @return QStringList: String list with all DBus plugins address
    *
    * Retrieve a string list with DBus address of all plugins that are enabled by type.\n
    */
    QStringList getObjectsByName (QString strName);

private: //Functions
    QPluginLoader *loadPlugin (const char *pstrPlugin);
    int            parseConfig(QString strFilePath);

private: //Variables

    QDBusConnection          m_connection;
    QList <rosensorsPlugin*>  m_plugins;         /**< Plugins list*/
    QList <QPluginLoader *>  m_hPlugins;        /**< Plugin handlers list*/
};

#endif // ROSENSORS_MANAGER_H
