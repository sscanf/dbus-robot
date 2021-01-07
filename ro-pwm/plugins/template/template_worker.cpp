#include <QDebug>
#include "@@name@@_worker.h"
#include "@@name@@_worker_interface.h"
#include <QAudio>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QMediaPlayer>

@@name@@Worker::@@name@@Worker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_strName   (strName),
    m_connection(QDBusConnection::systemBus())
{
    m_bEnabled          = bEnabled;
    m_strDescription    = strDescription;
    m_strAddress        = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);

    new @@name@@_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);
    m_connection.registerService(strAddress.replace("/","."));


    QMediaPlayer *player = new QMediaPlayer;
    // ...
    player->setMedia(QUrl::fromLocalFile("/usr/share/lbreakout2/sounds/shot.wav"));
    player->setVolume(50);
    player->play();
    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        qDebug() << "Device name: " << deviceInfo.deviceName();
}
