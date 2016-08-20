#ifndef @@name@@_MANAGER_H
#define @@name@@_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <zoaudio_plugin.h>
#include <QtDBus/QtDBus>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class @@name@@Worker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.zitro.zone.zoaudio")

public:
    explicit @@name@@Worker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName        ()              { return m_strName; }
    QString getAddress     ()              { return m_strAddress; }
    QString getPluginType  ()              { return PLUGIN_TYPE; }
    QString getDescription ()              { return m_strDescription; }
    bool    isEnabled      ()              { return m_bEnabled; }
    void    setEnabled     (bool bEnabled) { m_bEnabled = bEnabled; }

private:    //Functions


private:    //Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    
signals:
    void  error (bool bError);

private slots:

};

#endif // @@name@@_MANAGER_H
