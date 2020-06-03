#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#define ROOT_TAGNAME           "ROBOT"
#define PLUGINS_PATH           "/usr/lib/"
#define GAMEPAD_CONFIG_FILE    "/etc/robot/gamepad_config.xml"
#define DBUS_BASE_ADDRESS      "/rogamepad"

#include <QObject>

/**
 * @brief
 *
 */
class gamepadPlugin: public QObject
{
public:
    virtual     ~gamepadPlugin (){}
    virtual int  init   	(QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release 	()=0;
    QStringList  getAllObjects  () { return m_listAllObjects; }

protected:
    QStringList m_listAllObjects;

signals:
};

Q_DECLARE_INTERFACE(gamepadPlugin, "com.robot-plugin.gamepadplugin/1.0")

#endif // clientMsgDispatcher_H
