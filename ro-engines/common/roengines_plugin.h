#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#include <QObject>

#define ROOT_TAGNAME             "ROBOT"
#define PLUGINS_PATH             "/usr/lib/"
#define ROTRACKING_CONFIG_FILE   "/etc/robot/roenginesserver.xml"
#define DBUS_BASE_ADDRESS        "roengines/engines"

/**
 * @brief
 *
 */
class roenginesPlugin: public QObject
{
public:
    virtual     ~roenginesPlugin (){}
    virtual int  init   	(QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release 	()=0;
    QStringList  getAllObjects  () { return m_listAllObjects; }

protected:
    QStringList m_listAllObjects;

signals:
};

Q_DECLARE_INTERFACE(roenginesPlugin, "com.robot-plugin.roenginesplugin/1.0")

#endif // clientMsgDispatcher_H
