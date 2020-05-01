#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include <rosensors_manager.h>
#include "rosensors_manager_interface.h"

rosensorsManager::rosensorsManager(int & argc, char ** argv) :
    QCoreApplication(argc, argv),
    m_connection (QDBusConnection::systemBus())
{
    new rosensors_managerInterface(this);
    m_connection.registerService("com.robot.rosensors");
    m_connection.registerObject("/rosensors",this);
    parseConfig (ROSENSORS_CONFIG_FILE);
}

QStringList rosensorsManager::getObjects()
{
  QStringList strObjects;
  foreach (QPluginLoader *pLoader, m_hPlugins) {
    rosensorsPlugin *pPlugin = qobject_cast<rosensorsPlugin*>(pLoader->instance());
    strObjects << pPlugin->getAllObjects ();
  }
  return strObjects;
}

QStringList rosensorsManager::getObjectsByType(QString strType)
{
  QStringList strAllObjects = getObjects();
  QStringList strObjects;

  foreach (QString object, strAllObjects) {
    QString strInterface = DBUS_BASE_ADDRESS;
    object.remove (DBUS_BASE_ADDRESS);
    strInterface.replace ("/",".").remove (0,1);

    QDBusConnection bus = QDBusConnection::systemBus ();
    QDBusInterface interface ("com.robot.rosensors",
                              object,
                              strInterface,
                              bus,
                              this);

    QDBusPendingReply<QString> reply= interface.call(QLatin1String("getPluginType"));
    if (reply.isValid()) {
      if (reply.value() == strType) {
        QDBusPendingReply<QString> strAddress= interface.call(QLatin1String("getAddress"));
        strObjects << strAddress;
      }
    } else
        qDebug() << "error " << reply.error ();
  }
  return strObjects;
}

QStringList rosensorsManager::getObjectsByName(QString strName)
{
  QStringList strAllObjects = getObjects();
  QStringList strObjects;

  foreach (QString object, strAllObjects) {
    QString strInterface = DBUS_BASE_ADDRESS;
    object.remove (DBUS_BASE_ADDRESS);
    strInterface.replace ("/",".").remove (0,1);

    QDBusConnection bus = QDBusConnection::systemBus ();
    QDBusInterface interface ("com.robot.rosensors",
                              object,
                              strInterface,
                              bus,
                              this);

    QDBusPendingReply<QString> reply= interface.call(QLatin1String("getName"));
    if (reply.isValid()) {
      if (reply.value() == strName) {
        QDBusPendingReply<QString> strAddress= interface.call(QLatin1String("getAddress"));
        strObjects << strAddress;
      }
    } else
        qDebug() << "error " << reply.error ();
  }
  return strObjects;
}

QPluginLoader *rosensorsManager::loadPlugin (const char *pstrPlugin)
{
  QString strPlugin(pstrPlugin);

  QPluginLoader *pluginLoader = new QPluginLoader(strPlugin);

  if (!pluginLoader->isLoaded ()) {
    bool ret = pluginLoader->load();
    m_hPlugins.append (pluginLoader);
    if (!ret) {
      qDebug() << "zostorage could not load plugin" << strPlugin;
      qDebug() << pluginLoader->errorString();

      delete pluginLoader;
      return (QPluginLoader *)NULL;
    }
  }
  return pluginLoader;
}

int rosensorsManager::parseConfig(QString strFilePath)
{
  QDomDocument doc ("rosensors");
  QString      errorMsg;
  int          errorLine;
  int          errorColumn;

  QFile file(strFilePath);
  if (!file.open (QIODevice::ReadOnly))
    return EXIT_FAILURE;

  if ( !doc.setContent(&file, &errorMsg, &errorLine, &errorColumn) ) {
    qDebug() << errorMsg << errorLine << errorColumn;
    file.close();
    return EXIT_FAILURE;
  }

  QDomElement root = doc.documentElement();
  if (root.tagName() != ROOT_TAGNAME)
    return EXIT_FAILURE;

  QDomElement config = root.firstChildElement ("Plugin");
  rosensorsPlugin *pZPlugin = NULL;

  while (!config.isNull()) {
    QDomElement e           = config.toElement();
    QString     name        = e.attribute("name");
    QString     filePath    = e.attribute("file");
    QString     description = e.attribute("description");
    QString     active      = e.attribute("active");

    bool bEnabled = active == "true" ? true : false;

    QString pluginPath     = PLUGINS_PATH+filePath;
    QPluginLoader *pPlugin = loadPlugin ((const char *)pluginPath.toLocal8Bit ().data());
    if (!pPlugin)
        return EXIT_FAILURE;

    pZPlugin = qobject_cast <rosensorsPlugin*>( pPlugin->instance ());
    if (!pZPlugin)
      return EXIT_FAILURE;

    if (pZPlugin->init (name, description, bEnabled) == EXIT_FAILURE)
      qDebug () << "Error initializing plugin " << filePath;

    config = config .nextSiblingElement ();
  }
  return EXIT_SUCCESS;
}
