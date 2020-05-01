#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#define ROOT_TAGNAME          "ROBOT"
#define PLUGINS_PATH          "/usr/lib/"
#define ROSENSORS_CONFIG_FILE "/etc/robot/rosensors_config.xml"
#define DBUS_BASE_ADDRESS     "/rosensors"

#include <QObject>

/**
 * @brief
 *
 */
class rosensorsPlugin: public QObject
{
public:
    virtual     ~rosensorsPlugin (){}
    virtual int  init   	(QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release 	()=0;
    QStringList  getAllObjects  () { return m_listAllObjects; }

protected:
    QStringList m_listAllObjects;

signals:
};

Q_DECLARE_INTERFACE(rosensorsPlugin, "com.robot-plugin.rosensorsplugin/1.0")

#endif // clientMsgDispatcher_H
