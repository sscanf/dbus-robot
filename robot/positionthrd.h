#ifndef POSITIONTHRD_H
#define POSITIONTHRD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>
#include <QThread>
#include <QTimer>

#define MAX_ELEV 60
#define MIN_ELEV 0

#define MAX_AZIM 100
#define MIN_AZIM 0

class positionThrd : public QThread {

public:
    explicit positionThrd(const QDBusConnection &connection, quint16 azim, quint16 elev, QObject *parent = nullptr);
    void run();
    void setPossition(quint16 azim, quint16 elev);
    void setAzimuth(quint16 azim);
    void setElevation(quint16 elev);
    void setAngle(quint16 azim, quint16 elev);

private:
    //    void setAngle(quint16 azim, quint16 elev);
private:
    QDBusInterface *m_pCameraIface;
    QDBusConnection m_connection;
    int             m_azim = 45;
    int             m_elev = 45;
    int             m_newAzim;
    int             m_newElev;

private slots:
};

#endif // POSITIONTHRD_H
