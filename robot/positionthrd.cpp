#include "positionthrd.h"

positionThrd::positionThrd(QDBusConnection connection, quint16 azim, quint16 elev, QObject *parent)
    : QThread(parent)
    , m_connection(connection) {
    m_azim = azim;
    m_elev = elev;
}

void positionThrd::run() {
    m_pCameraIface = new QDBusInterface("com.robot.pwm", //
                                        "/servos",
                                        "com.robot.servoscontroller",
                                        m_connection );
    setPossition(m_azim, m_elev);
    int antElev = 0;
    int antAzim = 0;

    forever {
        if (m_azim < m_newAzim) {
            m_azim++;
        } else if (m_azim > m_newAzim) {
            m_azim--;
        }

        if (m_elev < m_newElev) {
            m_elev++;
        } else if (m_elev > m_newElev) {
            m_elev--;
        }

        if (antElev != m_elev || antAzim != m_azim) {
            antElev = m_elev;
            antAzim = m_azim;
            setAngle(m_azim, m_elev);
        }
        msleep(10);
    }
}

void positionThrd::setPossition(quint16 azim, quint16 elev) {
    m_newAzim = azim;
    m_newElev = elev;
}

void positionThrd::setAzimuth(quint16 azim) {
    m_pCameraIface->call("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(azim)));
}

void positionThrd::setElevation(quint16 elev) {
    m_pCameraIface->call("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(elev)));
}

void positionThrd::setAngle(quint16 azim, quint16 elev) {
    setAzimuth(azim);
    setElevation(elev);
}
