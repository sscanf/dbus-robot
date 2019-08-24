#ifndef POSITIONTHRD_H
#define POSITIONTHRD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>
#include <QObject>
#include <QThread>


class positionThrd : public QThread
{

public:
    explicit positionThrd(quint16 azim, quint16 elev, QObject *parent = nullptr);
    void run();
    void setPossition (quint16 azim, quint16 elev);

private:
    void setAngle(quint16 azim, quint16 elev);
private:
    QDBusInterface *m_pCameraIface;
    int             m_azim=90;
    int             m_elev=70;
    int             m_newAzim;
    int             m_newElev;
};

#endif // POSITIONTHRD_H
