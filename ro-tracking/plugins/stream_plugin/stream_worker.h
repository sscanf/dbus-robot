#ifndef stream_MANAGER_H
#define stream_MANAGER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTimer>
#include <rotracking_plugin.h>
#include <QtDBus/QtDBus>
#include <vlc/vlc.h>

#define PLUGIN_TYPE   " Please, define plugin type !!! "

class streamWorker : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.zitro.zone.zoaudio")

public:
    explicit streamWorker(QString strName, QString strDescription = 0, bool bEnabled=0, QObject *parent = 0);

public Q_SLOTS:
    QString getName        ()              { return m_strName; }
    QString getAddress     ()              { return m_strAddress; }
    QString getPluginType  ()              { return PLUGIN_TYPE; }
    QString getDescription ()              { return m_strDescription; }
    bool    isEnabled      ()              { return m_bEnabled; }
    void    setEnabled     (bool bEnabled) { m_bEnabled = bEnabled; }
    void    setImage       (const char *pImage);
    void    start          ();
private:    //Functions

    static int MyImemGetCallback (void *data,
                           const char *cookie,
                           int64_t *dts,
                           int64_t *pts,
                           unsigned *flags,
                           size_t * bufferSize,
                           void ** buffer);

    static int MyImemReleaseCallback (void *data,
                               const char *cookie,
                               size_t bufferSize,
                               void * buffer);

private:    //Variables
    int                     m_address;
    QString                 m_strName;
    QString                 m_strAddress;
    QString                 m_strDescription;
    bool                    m_bEnabled;
    QDBusConnection         m_connection;
    libvlc_instance_t      *m_pVlcInstance;
    libvlc_media_player_t  *m_pVlcMediaPlayer;
    libvlc_media_t         *m_pVlcMedia;
    const char             *m_pImage;

signals:
    void  error (bool bError);

private slots:

};

#endif // stream_MANAGER_H
