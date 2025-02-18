#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include <rotracking_manager.h>
#include "rotracking_manager_interface.h"


rotrackingManager::rotrackingManager(int &argc, char **argv)
    : QCoreApplication(argc, argv)
    , m_connection(QDBusConnection::systemBus()) {
    new rotracking_managerInterface(this);
    m_connection.registerService(QStringLiteral("com.robot.rotracking"));
    m_connection.registerObject(QStringLiteral("/rotracking"), this);
    parseConfig(ROTRACKING_CONFIG_FILE);
}

QStringList rotrackingManager::getObjects() {
    QStringList strObjects;
    foreach (QPluginLoader *pPlugin, m_hPlugins) {
        rotrackingPlugin *plugin = qobject_cast<rotrackingPlugin *>(pPlugin->instance());
        strObjects << plugin->getAllObjects();
    }
    return strObjects;
}

QStringList rotrackingManager::getObjectsByType(const QString &strType) {
    QStringList strAllObjects = getObjects();
    QStringList strObjects;

    foreach (QString object, strAllObjects) {
        QString strInterface = DBUS_BASE_ADDRESS;
        object.remove(DBUS_BASE_ADDRESS);
        strInterface.replace(QLatin1String("/"), QLatin1String(".")).remove(0, 1);

        QDBusConnection bus = QDBusConnection::systemBus();
        QDBusInterface  interface(QStringLiteral("com.robot.rotracking"), object, strInterface, bus, this);

        QDBusPendingReply<QString> reply = interface.call(QStringLiteral("getPluginType"));
        if (reply.isValid()) {
            if (reply.value() == strType) {
                QDBusPendingReply<QString> strAddress = interface.call(QStringLiteral("getAddress"));
                strObjects << strAddress;
            }
        } else
            qDebug() << "error " << reply.error();
    }
    return strObjects;
}

QStringList rotrackingManager::getObjectsByName(const QString &strName) {
    QStringList strAllObjects = getObjects();
    QStringList strObjects;

    foreach (QString object, strAllObjects) {
        QString strInterface = DBUS_BASE_ADDRESS;
        object.remove(DBUS_BASE_ADDRESS);
        strInterface.replace(QLatin1String("/"), QLatin1String(".")).remove(0, 1);

        QDBusConnection bus = QDBusConnection::systemBus();
        QDBusInterface  interface(QLatin1String("com.robot.rotracking"), object, strInterface, bus, this);

        QDBusPendingReply<QString> reply = interface.call(QLatin1String("getName"));
        if (reply.isValid()) {
            if (reply.value() == strName) {
                QDBusPendingReply<QString> strAddress = interface.call(QLatin1String("getAddress"));
                strObjects << strAddress;
            }
        } else
            qDebug() << "error " << reply.error();
    }
    return strObjects;
}

QPluginLoader *rotrackingManager::loadPlugin(const char *pstrPlugin) {
    QString strPlugin(pstrPlugin);

    QPluginLoader *pluginLoader = new QPluginLoader(strPlugin);

    if (!pluginLoader->isLoaded()) {
        bool ret = pluginLoader->load();
        m_hPlugins.append(pluginLoader);
        if (!ret) {
            qDebug() << "Could not load plugin" << strPlugin;
            qDebug() << pluginLoader->errorString();

            delete pluginLoader;
            return (QPluginLoader *)NULL;
        }
    }
    return pluginLoader;
}

int rotrackingManager::parseConfig(QString strFilePath) {
    QDomDocument doc("rotracking");
    QString      errorMsg;
    int          errorLine;
    int          errorColumn;

    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly))
        return EXIT_FAILURE;

    if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
        qDebug() << errorMsg << errorLine << errorColumn;
        file.close();
        return EXIT_FAILURE;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != ROOT_TAGNAME)
        return EXIT_FAILURE;

    QDomElement       config   = root.firstChildElement("Plugin");
    rotrackingPlugin *pZPlugin = NULL;

    while (!config.isNull()) {
        QDomElement e           = config.toElement();
        QString     name        = e.attribute("name");
        QString     filePath    = e.attribute("file");
        QString     description = e.attribute("description");
        QString     active      = e.attribute("active");

        qDebug() << name << filePath << description << active;

        bool bEnabled = active == "true" ? true : false;

        QString        pluginPath = PLUGINS_PATH + filePath;
        QPluginLoader *pPlugin    = loadPlugin((const char *)pluginPath.toLocal8Bit().data());
        if (!pPlugin)
            return EXIT_FAILURE;

        pZPlugin = qobject_cast<rotrackingPlugin *>(pPlugin->instance());
        if (!pZPlugin)
            return EXIT_FAILURE;

        if (pZPlugin->init(name, description, bEnabled) == EXIT_FAILURE)
            qDebug() << "Error initializing plugin " << filePath;

        config = config.nextSiblingElement();
    }
    return EXIT_SUCCESS;
}
