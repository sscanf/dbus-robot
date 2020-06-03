#include <QDebug>
#include "@@name@@_worker.h"
#include "@@name@@_worker_interface.h"

@@name@@Worker::@@name@@Worker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled      = bEnabled;
    m_strDescription= strDescription;
    m_strAddress    = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new @@name@@_workerInterface(this);
    m_connection.registerObject(m_strAddress,this);

}
