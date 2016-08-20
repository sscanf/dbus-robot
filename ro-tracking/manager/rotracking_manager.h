#ifndef ROTRACKING_MANAGER_H
#define ROTRACKING_MANAGER_H

#include <QCoreApplication>
#include <QTimer>
#include <QList>
#include <QPluginLoader>
#include <QtDBus/QtDBus>
#include "rotracking_plugin.h"


class rotrackingManager : public QCoreApplication
{
    Q_OBJECT
    Q_CLASSINFO ("D-Bus Interface","com.robot.rotracking")

public:
    explicit rotrackingManager(int & argc, char ** argv);

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

    /**
     * @brief Retrieve a string list with DBus address of all plugins enabled by type.
     * @param QString: Type of objects to retrieve
     * @return QStringList: String list with all DBus plugins address
     *
     * Retrieve a string list with DBus address of all plugins that are enabled by type.\n
     */
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
    QList <rotrackingPlugin*>  m_plugins;         /**< Plugins list*/
    QList <QPluginLoader *>  m_hPlugins;        /**< Plugin handlers list*/
};

#endif // ROTRACKING_MANAGER_H
