#include "positionthrd.h"

positionThrd::positionThrd(quint16 azim, quint16 elev, QObject *parent) :
    QThread (parent)
{
    m_azim = azim;
    m_elev = elev;
    setPossition (m_azim, m_elev);
}

void positionThrd::run()
{
    QDBusConnection connection (QDBusConnection::systemBus());
    m_pCameraIface = new QDBusInterface ("com.robot.rocamera",
                                       "/servos",
                                       "com.robot.servoscontroller",
                                       connection,
                                       this);
    int antElev=0;
    int antAzim=0;
    forever {
        if (m_azim < m_newAzim) {
            m_azim++;
        } else   if (m_azim > m_newAzim) {
            m_azim--;
        }

        if (m_elev < m_newElev) {
            m_elev++;
        } else   if (m_elev > m_newElev) {
            m_elev--;
        }

        if (antElev != m_elev || antAzim != m_azim) {
            antElev=m_elev;
            antAzim=m_azim;
            setAngle (m_azim, m_elev);
        } else
            msleep(1);
    }
}

void positionThrd::setPossition(quint16 azim, quint16 elev)
{
    m_newAzim=azim;
    m_newElev=elev;

}

void positionThrd::setAngle(quint16 azim, quint16 elev)
{
    m_pCameraIface->call ("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(azim)));
    m_pCameraIface->call ("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(elev)));
}
