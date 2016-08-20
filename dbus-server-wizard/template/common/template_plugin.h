#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#include <QObject>

class busdio;

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

Q_DECLARE_INTERFACE(@@name@@Plugin, "com.zitro.zone-plugin.@@name@@plugin/1.0")

#endif // clientMsgDispatcher_H
