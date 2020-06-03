#ifndef POSITIONTHRD_H
#define POSITIONTHRD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>
#include <QThread>

class positionThrd : public QThread
{

public:
    explicit positionThrd(QDBusConnection connection, quint16 azim, quint16 elev, QObject *parent = nullptr);
    void run();
    void setPossition (quint16 azim, quint16 elev);
    void setAzimuth   (quint16 azim);
    void setElevation (quint16 elev);

private:
    void setAngle(quint16 azim, quint16 elev);
private:
    QDBusInterface *m_pCameraIface;
    QDBusConnection m_connection;
    int             m_azim=90;
    int             m_elev=70;
    int             m_newAzim;
    int             m_newElev;
};

#endif // POSITIONTHRD_H
