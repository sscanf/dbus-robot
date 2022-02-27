#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <pwm_manager.h>
#include "pwm_manager_interface.h"

pwmManager::pwmManager(int & argc, char ** argv) :
    QCoreApplication(argc, argv),
    m_connection (QDBusConnection::systemBus()),
    m_pwm (0x40)
{
    new pwm_managerInterface(this);
    m_connection.registerObject("/pwm",this);
    m_connection.registerService("com.robot.pwm");
    parseConfig (ROPWM_CONFIG_FILE);
    m_pwm.begin();
    m_pwm.setPWM(4, 0, 4095);

//    m_timerID = startTimer (1);
}

void pwmManager::timerEvent(QTimerEvent *event)
{
    static unsigned int num=0;
    static int inc=+10;
    if (event->timerId() == m_timerID) {
        num+=inc;
        m_pwm.setPWM(4, 0, num);
        qDebug() << num;
        if (num>4096)
            inc=-10;
        if (num==0)
            inc=+10;
    }
}

QStringList pwmManager::getObjects()
{
  QStringList strObjects;
  foreach (QPluginLoader *pLoader, m_hPlugins) {
    pwmPlugin *pPlugin = qobject_cast<pwmPlugin*>(pLoader->instance());
    strObjects << pPlugin->getAllObjects ();
  }
  return strObjects;
}

QStringList pwmManager::getObjectsByType(QString strType)
{
  QStringList strAllObjects = getObjects();
  QStringList strObjects;

  foreach (QString object, strAllObjects) {
    QString strInterface = DBUS_BASE_ADDRESS;
    object.remove (DBUS_BASE_ADDRESS);
    strInterface.replace ("/",".").remove (0,1);

    QDBusConnection bus = QDBusConnection::systemBus ();
    QDBusInterface interface ("com.robot.pwm",
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

QStringList pwmManager::getObjectsByName(QString strName)
{
  QStringList strAllObjects = getObjects();
  QStringList strObjects;

  foreach (QString object, strAllObjects) {
    QString strInterface = DBUS_BASE_ADDRESS;
    object.remove (DBUS_BASE_ADDRESS);
    strInterface.replace ("/",".").remove (0,1);

    QDBusConnection bus = QDBusConnection::systemBus ();
    QDBusInterface interface ("com.robot.pwm",
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

QPluginLoader *pwmManager::loadPlugin (const char *pstrPlugin)
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

int pwmManager::parseConfig(QString strFilePath)
{
  QDomDocument doc ("ROBOT");
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
  pwmPlugin *pZPlugin = NULL;

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

    pZPlugin = qobject_cast <pwmPlugin*>( pPlugin->instance ());
    if (!pZPlugin)
      return EXIT_FAILURE;

    if (pZPlugin->init (&m_pwm, name, description, bEnabled) == EXIT_FAILURE)
      qDebug () << "Error initializing plugin " << filePath;

    config = config .nextSiblingElement ();
  }
  return EXIT_SUCCESS;
}
