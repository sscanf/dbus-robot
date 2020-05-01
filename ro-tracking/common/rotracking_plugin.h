#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#include <QObject>

class busdio;

#define ROOT_TAGNAME             "ROBOT"
#define PLUGINS_PATH             "/usr/lib/"
#define ROTRACKING_CONFIG_FILE   "/etc/robot/rotracking_config.xml"
#define DBUS_BASE_ADDRESS        "/rotracking/"

/**
 * @brief
 *
 */
class rotrackingPlugin: public QObject
{
public:
    virtual       ~rotrackingPlugin (){}
    virtual int    init              (QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void   release           ()=0;
    QStringList    getAllObjects     () { return m_listAllObjects; }
    QList <void *> getAllWorkers     () { return m_listWorkers;}

protected:
    QStringList m_listAllObjects;
    QList <void *> m_listWorkers;

signals:
};

Q_DECLARE_INTERFACE(rotrackingPlugin, "com.robot-plugin.rotrackingplugin/1.0")

#endif // clientMsgDispatcher_H
