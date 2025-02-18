#ifndef ina219_MANAGER_H
#define ina219_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <rosensors_plugin.h>
#include <QtDBus>

#define PLUGIN_TYPE " Please, define plugin type !!! "

class ina219Worker : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.robot.rosensors")

public:
    explicit ina219Worker(QString strName, QString strDescription = 0, bool bEnabled = 0, QObject *parent = 0);

public Q_SLOTS:
    QString getName();
    QString getAddress();
    QString getPluginType();
    QString getDescription();
    bool    isEnabled();
    void    setEnabled(bool bEnabled);
    int     getVoltage();
    int     getCurrent();
    int     getPower();
    int     init();

private: // Functions
    int  readFile(const QString &fileName);
    void updateValues();

private: // Variables
    int             m_address;
    QString         m_strName;
    QString         m_strAddress;
    QString         m_strDescription;
    QTimer         *m_pTimer;
    bool            m_bEnabled;
    QDBusConnection m_connection;
    int             m_voltage = 0;
    int             m_current = 0;
    int             m_power   = 0;

signals:
    void error(bool bError);
    void voltageChanged(int);
    void currentChanged(int);
    void powerChanged(int);

private slots:
    void onTimeout();
};

#endif // ina219_MANAGER_H
