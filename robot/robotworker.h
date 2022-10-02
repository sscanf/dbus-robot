#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H
#include "manualcamerathrd.h"
#include "manualmotorsthrd.h"
#include "pid.h"
#include "positionthrd.h"
#include <motiontasks_defs.h>
#include <QCoreApplication>
#include <QtDBus>
#include <qdbusconnection.h>
#include <QQueue>

#define LOW_SPEED 2

class RO3DPoint {
public:
    RO3DPoint() {}

    int x() const { //
        return m_x;
    }
    void setX(double x) { //
        m_x = x;
    }
    int y() const { //
        return m_y;
    }
    void setY(double y) { //
        m_y = y;
    }
    int z() const { //
        return m_z;
    }
    void setZ(double z) { //
        m_z = z;
    }

private:
    qint32 m_x;
    qint32 m_y;
    qint32 m_z;
};

class robotWorker : public QCoreApplication {
    Q_OBJECT
    Q_ENUM(tasks)

public:
    enum dirs {
        DIR_STOP,
        DIR_FORWARD,
        DIR_BACKWARD,
        DIR_TURN_RIGHT,
        DIR_TURN_LEFT
    };

    enum distances {
        frontCenter,
        frontLeft,
        frontRight,
        rearRight,
        rearLeft,
        rearCenter
    };

    robotWorker(int &argc, char **argv);

private: // Functions
    void      initTracker();
    void      initDistSensors();
    void      initGamepad();
    void      initMotors();
    double    map(double x, double in_min, double in_max, double out_min, double out_max);
    RO3DPoint getCenterDistance();
    void      setDir(dirs dir);
    void      setAutonomous(bool bValue);
    void      setGamepadColor(int red, int blue, int green);
    void      setConnectedStatus(bool value);
    int       getTotalSensors();
    void      pushTask(tasks task, int tSecs);

private: // Variables
    QTimer           *m_pTimer;
    QDBusConnection   m_connection;
    QDBusInterface   *m_pServosIRIface;
    QDBusInterface   *m_pTrackingIface;
    QDBusInterface   *m_pDistanceIface;
    QDBusInterface   *m_pGamepadIface;
    QDBusInterface   *m_pMotorsIface;
    int               m_azimut;
    int               m_elev;
    int               m_lastAzimut;
    int               m_lastElev;
    int               m_lastDirElev;
    int               m_lastDirAzim;
    positionThrd     *m_pPositionThrd;
    manualCameraThrd *m_pCameraThrd;
    manualMotorsThrd *m_pMotorsThrd;
    bool              m_bAutonomous;
    bool              m_ballLost          = false;
    int               m_totalCameraRounds = 0;
    int               m_speed             = 20;
    int               m_direction         = DIR_STOP;
    QList<int>        m_minDistanceSensors;

private slots:
    void onTimeout();
    void onPositionChanged(const QPoint &position);
    void onPositionChanged(const QPoint &pos1, const QPoint &pos2, const QPoint &pos3, const QPoint &pos4);
    void onBallLost();
    // void onDistanceChanged(int sensor, int distance);
    void onCollision(int sensor);
    void onMotorsError(int err);
    void onButtonPS(bool);
    void onGamepadConnected();
    void onGamepadDisconnected();
};

#endif // ROBOTWORKER_H
