#include <QDebug>
#include "irtracker_worker.h"
#include "irtracker_worker_interface.h"

irtrackerWorker::irtrackerWorker(QString strName, QString strDescription, bool bEnabled, QObject *parent) :
    QObject     (parent),
    m_connection(QDBusConnection::systemBus())
{
    Q_UNUSED (strDescription);
    Q_UNUSED (bEnabled);

    m_strAddress = QString("%1/%2").arg(DBUS_BASE_ADDRESS).arg(strName);
    m_strName = strName;
    new irtracker_workerInterface(this);
    QString strAddress = m_strAddress;
    QString strObject = "/"+strName;
    m_connection.registerObject(strObject,this);

    QThread *pThread = new QThread;
    ZOPosIRCam *pWorker = new ZOPosIRCam();
    pWorker->moveToThread(pThread);
    connect (pThread, SIGNAL (started  ()), pWorker, SLOT (process()));
    connect (pWorker, SIGNAL(detection(QPoint, QPoint, QPoint, QPoint)), this, SLOT (onDetection(QPoint, QPoint, QPoint, QPoint)));
    pThread->start();
}

void irtrackerWorker::startTracking()
{
    emit nextTrack();
}

void irtrackerWorker::stopTracking()
{
}

void irtrackerWorker::startStream()
{
}

void irtrackerWorker::stopStream()
{
}

QPoint irtrackerWorker::centerDistance()
{
    return m_centerDistance;
}

bool irtrackerWorker::isBallDetected()
{
    return m_bBallDetected;
}

QPoint irtrackerWorker::xyPossition()
{
    QPoint pos;
    return pos;
}

int irtrackerWorker::zPossition()
{
   return 0;
}

void irtrackerWorker::on_track()
{
}

void irtrackerWorker::onDetection(QPoint pos1, QPoint pos2, QPoint pos3, QPoint pos4)
{
    if (pos1!=m_pos1 || pos2!=m_pos2 || pos3!=m_pos3 || pos4!=m_pos4) {
        m_pos1=pos1;
        m_pos2=pos2;
        m_pos3=pos3;
        m_pos4=pos4;
        emit positionChanged(pos1,pos2,pos3,pos4);
    }
}
