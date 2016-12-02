#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#define ROOT_TAGNAME             "ROBOT"
#define PLUGINS_PATH             "/usr/lib/"
#define ROTRACKING_CONFIG_FILE   "/etc/robot/@@name@@_config.xml"
#define DBUS_BASE_ADDRESS        "/com/robot"

#include <QObject>

/**
 * @brief
 *
 */
class @@name@@Plugin: public QObject
{
public:
    virtual     ~@@name@@Plugin (){}
    virtual int  init   	(QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release 	()=0;
    QStringList  getAllObjects  () { return m_listAllObjects; }

protected:
    QStringList m_listAllObjects;

signals:
};

Q_DECLARE_INTERFACE(@@name@@Plugin, "com.robot-plugin.@@name@@plugin/1.0")

#endif // clientMsgDispatcher_H
