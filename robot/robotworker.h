#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H
#include "manualcamerathrd.h"
#include "manualmotorsthrd.h"
#include "pid.h"
#include "positionthrd.h"
#include "walkthread.h"
#include <QCoreApplication>
#include <QtDBus>
#include <qdbusconnection.h>

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

public:
    enum distances {
        frontCenter,
        frontLeft,
        frontRight,
        rearRight,
        rearLeft,
        rearCenter
    };
    robotWorker(int &argc, char **argv);

    struct minDistances {
        int  minDistance;
        bool bAlarm;
    };

private: // Functions
    void                  initTracker();
    void                  initDistSensors();
    void                  initGamepad();
    double                map(double x, double in_min, double in_max, double out_min, double out_max);
    RO3DPoint             getCenterDistance();
    void                  setDir(const tasks &task);
    walkThread::direction getDir();
    void                  setAutonomous(bool bValue);
    void                  setGamepadColor(int red, int blue, int green);
    void                  setConnectedStatus(bool value);
    void                  setSpeed();

private: // Variables
    QTimer           *m_pTimer;
    QTimer           *m_pRandomTimer;
    QTimer           *m_pTurnTimer;
    QDBusConnection   m_connection;
    QDBusInterface   *m_pServosIRIface;
    QDBusInterface   *m_pTrackingIface;
    QDBusInterface   *m_pDistanceIface;
    QDBusInterface   *m_pGamepadIface;
    int               m_azimut;
    int               m_elev;
    int               m_lastAzimut;
    int               m_lastElev;
    int               m_lastDirElev;
    int               m_lastDirAzim;
    positionThrd     *m_pPositionThrd;
    walkThread       *m_pWalkThread;
    manualCameraThrd *m_pCameraThrd;
    manualMotorsThrd *m_pMotorsThrd;
    PID              *m_pPid;
    bool              m_bAutonomous;
    bool              m_ballLost          = false;
    int               m_totalCameraRounds = 0;
    int               m_valL              = 0;
    int               m_valR              = 0;
    int               m_speed             = 0;
    minDistances      m_collisionSensors[6];

private slots:
    void onTimeout();
    void onPositionChanged(const QPoint &position);
    void onPositionChanged(const QPoint &pos1, const QPoint &pos2, const QPoint &pos3, const QPoint &pos4);
    void onBallLost();
    void onDistanceChanged(int sensor, int distance);
    void onMotorsError(int err);
    void onButtonPS(bool);
    void onGamepadConnected();
    void onGamepadDisconnected();
};

#endif // ROBOTWORKER_H
