#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#include <QObject>

#define ROOT_TAGNAME         "ROBOT"
#define PLUGINS_PATH         "/usr/lib/"
#define ROCAMERA_CONFIG_FILE "/etc/robot/rocamera_config.xml"
#define DBUS_BASE_ADDRESS    "/com/robot"

/**
 * @brief
 *
 */
class rocameraPlugin: public QObject
{
public:
    virtual     ~rocameraPlugin (){}
    virtual int  init   	(QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release 	()=0;
    QStringList  getAllObjects  () { return m_listAllObjects; }

protected:
    QStringList m_listAllObjects;

signals:
};

Q_DECLARE_INTERFACE(rocameraPlugin, "com.robot-plugin.rocameraplugin/1.0")

#endif // clientMsgDispatcher_H
