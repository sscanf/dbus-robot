#ifndef ROCAMERA_MANAGER_H
#define ROCAMERA_MANAGER_H

#include <QCoreApplication>
#include <QTimerEvent>
#include <QList>

#include <QPluginLoader>
#include <QtDBus/QtDBus>
#include <Adafruit_PWMServoDriver.h>

#include "pwm_plugin.h"

class pwmManager : public QCoreApplication
{
    Q_OBJECT
    Q_CLASSINFO ("D-Bus Interface","com.robot.pwm")

public:
    explicit pwmManager(int & argc, char ** argv);
    void timerEvent(QTimerEvent *event);

public Q_SLOTS:
    QString getVersion(){
        return APP_VERSION;
    }

    QStringList getObjects ();
    QStringList getObjectsByType(QString strType);
    QStringList getObjectsByName(QString strName);

private: //Functions
    QPluginLoader  *loadPlugin (const char *pstrPlugin);
    int             parseConfig(QString strFilePath);
    int             m_timerID=0;

private: //Variables

    QDBusConnection          m_connection;
    QList <pwmPlugin*>       m_plugins;         /**< Plugins list*/
    QList <QPluginLoader *>  m_hPlugins;        /**< Plugin handlers list*/
    Adafruit_PWMServoDriver  m_pwm;
};

#endif // ROCAMERA_MANAGER_H
