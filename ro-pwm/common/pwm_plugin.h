#ifndef MSGDISPATCHER_1H
#define MSGDISPATCHER_1H

#include <QObject>
#include "Adafruit_PWMServoDriver.h"

#define ROOT_TAGNAME         "ROBOT"
#define PLUGINS_PATH         "/usr/lib/"
#define ROPWM_CONFIG_FILE    "/etc/robot/ropwm_config.xml"
#define DBUS_BASE_ADDRESS    "/com/robot"

/**
 * @brief
 *
 */
class pwmPlugin: public QObject
{
public:
    virtual     ~pwmPlugin    (){}
    virtual int  init         (Adafruit_PWMServoDriver *pPwm, QString strName, QString strDescription=QString(), bool bEnabled=true)=0;
    virtual void release      ()=0;
    QStringList  getAllObjects() { return m_listAllObjects; }

protected:
    QStringList              m_listAllObjects;
signals:
};

Q_DECLARE_INTERFACE(pwmPlugin, "com.robot-plugin.pwmplugin/1.0")

#endif // clientMsgDispatcher_H
