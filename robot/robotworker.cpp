#include "robotworker.h"

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

robotWorker::robotWorker(int & argc, char ** argv) :
    QCoreApplication(argc, argv),
    m_connection (QDBusConnection::systemBus())

{
    m_azimut=90;
    m_elev=70;
    m_lastDirAzim=-1;
    m_lastDirElev=0;
    m_lastAzimut=0;
    m_lastElev=0;

    qsrand(QTime::currentTime().msec());
    initTracker();
    initDistSensors();

    m_pPositionThrd = new positionThrd(m_connection, m_azimut, m_elev);

    m_pWalkThread = new walkThread(m_connection);
    connect (m_pWalkThread, SIGNAL (error(int)), this, SLOT (onMotorsError(int)));

    m_pCameraThrd = new manualCameraThrd(m_connection);
    m_pMotorsThrd = new manualMotorsThrd(m_connection);

    m_pTimer = new QTimer();
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));

    m_pTurnTimer = new QTimer();
    connect (m_pTurnTimer, SIGNAL (timeout()), this, SLOT (onTurnTimeout()));



    initGamepad();
    setAutonomous(false);
//    m_pTurnTimer->start (1000);


//    m_pRandomTimer = new QTimer();
//    connect (m_pRandomTimer, SIGNAL (timeout()), this, SLOT (on_randomTimeout()));
//    m_pRandomTimer->start (qrand()%(10*1000)+1000);
//    m_pTimer->start (1000);
}

void robotWorker::initTracker()
{
    m_pTrackingIface = new QDBusInterface ("com.robot.rotracking",
                                           "/balltracker",
                                           "com.robot.rotracking",
                                           m_connection,
                                           this);

    bool ret = QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                                     "/balltracker",
                                                     "com.robot.rotracking",
                                                     "possitionChanged",
                                                     this,
                                                     SLOT (onPossitionChanged(QPoint)));
    if (!ret) {
        qDebug() << "Can't catch signal possitionChanged";
    }

    ret = QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                                 "/balltracker",
                                                 "com.robot.rotracking",
                                                 "ballLost",
                                                 this,
                                                 SLOT (onBallLost()));
    if (!ret) {
        qDebug() << "Can't catch signal ballLost";
    }
}

void robotWorker::initDistSensors()
{
    m_pDistanceIface = new QDBusInterface ("com.robot.rosensors",
                                           "/rosensors/distance",
                                           "com.robot.rosensors",
                                           m_connection,
                                           this);

    bool ret = QDBusConnection::systemBus().connect( "com.robot.rosensors",
                                                     "/rosensors/distance",
                                                     "com.robot.rosensors",
                                                     "collision",
                                                     this,
                                                     SLOT (onCollision(int)));
    if (!ret) {
        qDebug() << "Can't catch signal Collision";
    }
}

void robotWorker::initGamepad()
{
    bool ret;
    m_pGamepadIface = new QDBusInterface ("com.robot.rogamepad",
                                           "/rogamepad/dualshock4",
                                           "com.robot.rogamepad.dualshock4",
                                           m_connection,
                                           this);
//    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
//                                              "/rogamepad/dualshock4",
//                                              "com.robot.rogamepad.dualshock4",
//                                              "axisLeftX",
//                                              this,
//                                              SLOT (onAxisLeftX(double)));
//    if (!ret) {
//        qDebug() << "Error initialitzing gamepad";
//    }
//    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
//                                              "/rogamepad/dualshock4",
//                                              "com.robot.rogamepad.dualshock4",
//                                              "axisLeftY",
//                                              this,
//                                              SLOT (onAxisLeftY(double)));
//    if (!ret) {
//        qDebug() << "Error initialitzing gamepad";
//    }
//    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
//                                              "/rogamepad/dualshock4",
//                                              "com.robot.rogamepad.dualshock4",
//                                              "axisRightX",
//                                              this,
//                                              SLOT (onAxisRightX(double)));
//    if (!ret) {
//        qDebug() << "Error initialitzing gamepad";
//    }
//    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
//                                              "/rogamepad/dualshock4",
//                                              "com.robot.rogamepad.dualshock4",
//                                              "axisRightY",
//                                              this,
//                                              SLOT (onAxisRightY(double)));
//    if (!ret) {
//        qDebug() << "Error initialitzing gamepad";
//    }
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "buttonPS",
                                              this,
                                              SLOT (onButtonPS(bool)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "connected",
                                              this,
                                              SLOT (onGamepadConnected()));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret=QDBusConnection::systemBus().connect( "com.robot.rogamepad",
                                              "/rogamepad/dualshock4",
                                              "com.robot.rogamepad.dualshock4",
                                              "disconnected",
                                              this,
                                              SLOT (onGamepadDisconnected()));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
}

double robotWorker::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void robotWorker::onTimeout()
{
    m_azimut += m_lastDirAzim;
    m_elev   += m_lastDirElev;

    if (m_azimut<10) {
        m_lastDirAzim=2;
        m_totalCameraRounds++;
    }
    if (m_azimut>175) {
        m_lastDirAzim=-2;
        m_totalCameraRounds++;
    }

    if (m_elev<5) {
        m_lastDirElev=1;
        m_totalCameraRounds++;
    }

    if (m_elev>110) {
        m_lastDirElev=-1;
        m_totalCameraRounds++;
    }

    if (m_totalCameraRounds>1) {
        m_totalCameraRounds=0;
        setDir(TSK_STEP_FORWARD);
    }

    m_pPositionThrd->setPossition(m_azimut,m_elev);
    m_pTimer->setInterval(60);
}

void robotWorker::onRandomTimeout()
{

}

void robotWorker::onPossitionChanged(QPoint position)
{
    Q_UNUSED (position);
//    int speed=0;
    m_ballLost=false;
    m_pTimer->stop();
    setDir(TSK_STOP);

    RO3DPoint pos;
    pos = getCenterDistance();
    double tempaz = map (pos.x(),0,320,0,180);
    double tempel = map (pos.y(),0,240,0,90);
    m_azimut      = static_cast<quint16>(m_azimut-(tempaz/15));
    m_elev        = static_cast<quint16>(m_elev+(tempel/15));
    m_pPositionThrd->setPossition(m_azimut,m_elev);

    if (pos.z()<40) {
        setDir(TSK_STEP_FORWARD);
    } else if (pos.z()>60) {
        setDir(TSK_STEP_BACKWARD);
    }

    m_lastDirElev = sign (m_elev - m_lastElev );
    m_lastDirAzim = sign (m_azimut - m_lastAzimut);
    if (m_lastDirAzim == 0)
        m_lastDirAzim = -1;
    m_lastElev    = m_elev;
    m_lastAzimut  = m_azimut;
}

RO3DPoint robotWorker::getCenterDistance()
{
    RO3DPoint pos;
    QDBusPendingReply<QPoint> qPointRet = m_pTrackingIface->call(QLatin1String("centerDistance"));
    if(qPointRet.isValid()) {
        QPoint point= qPointRet.value();
        pos.setX(point.x());
        pos.setY(point.y());
    }

    QDBusPendingReply<qint32> zRet = m_pTrackingIface->call(QLatin1String("zPossition"));
    if(zRet.isValid()) {
        pos.setZ(zRet.value());
    }
    return pos;
}

void robotWorker::setDir(tasks task)
{
    QList<QVariant> collisions = m_pWalkThread->getCollisions();
    switch (task) {
        case TSK_STEP_FORWARD:
           if (!collisions.contains (frontCenter) && !collisions.contains(frontLeft) && !collisions.contains(frontRight)) {
                m_pWalkThread->pushTask(task);
                qDebug() << "Forwarding";
           }
        break;

        case TSK_STEP_BACKWARD:
           if (!collisions.contains (rearCenter) && !collisions.contains(rearLeft) && !collisions.contains(rearRight)) {
                m_pWalkThread->pushTask(task);
                qDebug() << "Backwarding";
           }
        break;

        case TSK_TURN_LEFT:
           if (!collisions.contains (frontLeft) && !collisions.contains(frontCenter)) {
                m_pWalkThread->pushTask(task);
                qDebug() << "FRONT_LEFT";
           }
        break;

        case TSK_TURN_RIGHT:
           if (!collisions.contains (frontRight) && !collisions.contains(frontCenter)) {
                m_pWalkThread->pushTask(task);
                qDebug() << "FRONT_RIGHT";
           }
        break;

        default:
                m_pWalkThread->pushTask(task);
                qDebug() << "FRONT_STOP";
        break;
    }
}

void robotWorker::setAutonomous(bool bValue)
{
    if (bValue) {
        qDebug() << "Autonomous On";
        setGamepadColor(255,0,0);
        m_pPositionThrd->start();
        m_pWalkThread->start();
        m_pTimer->start(1000);
        m_pCameraThrd->terminate();
        m_pMotorsThrd->terminate();
        m_bAutonomous=true;
    } else {
        qDebug() << "Autonomous Off";
        setGamepadColor(0,255,0);
        m_pPositionThrd->terminate();
        m_pWalkThread->terminate();
        m_pTimer->stop();
        m_pCameraThrd->start();
        m_pMotorsThrd->start();
        m_bAutonomous=false;
    }
}

void robotWorker::setGamepadColor(int red, int blue, int green)
{
    m_pGamepadIface->call ("redLedValue",QVariant::fromValue(qint32(red)));
    m_pGamepadIface->call ("greenLedValue",QVariant::fromValue(qint32(blue)));
    m_pGamepadIface->call ("blueLedValue",QVariant::fromValue(qint32(green)));
}

void robotWorker::setConnectedStatus(bool value)
{
   if (value) {
       setGamepadColor(0,255,0);
   } else {
       setGamepadColor(0,0,0);
       if (m_bAutonomous) {
           setAutonomous(false);
       }
   }
}

void robotWorker::onBallLost()
{
    if (m_ballLost != true) {
        qDebug() << "Ball lost";
        setDir(TSK_STOP);
        m_ballLost=true;
        m_pTimer->start(1000);
    }
}

void robotWorker::onTurnTimeout()
{
    tasks lstTsk[] = {TSK_TURN_RIGHT, TSK_TURN_LEFT, TSK_STEP_FORWARD, TSK_STOP};

    int rnd = qrand() % (sizeof(lstTsk)/sizeof(int));
    qDebug() << "Dir = " << rnd;
    if (m_azimut<90) {
        setDir(lstTsk[rnd]);
    } else if (m_azimut>90) {
        setDir(lstTsk[rnd]);
    }
}

void robotWorker::onCollision(int sensor)
{
    int speed = m_pWalkThread->getSpeed();
    if (speed) {
        qDebug() << "Collision sensor: " << sensor;
        switch (sensor) {
            case frontCenter:
                if (speed>0)
                     setDir(TSK_STEP_BACKWARD);
            break;

            case rearCenter:
                if (speed<0)
                    setDir(TSK_STEP_FORWARD);
            break;

            case frontLeft:
                setDir(TSK_TURN_RIGHT);
            break;

            case frontRight:
                setDir(TSK_TURN_LEFT);
            break;
        }
    }
}

void robotWorker::onMotorsError(int err)
{
    setDir(TSK_STOP);
    qDebug() << "Error on motors: " << err;
}

void robotWorker::setSpeed()
{
    int speedL = (m_speed-m_valL)*-1;
    int speedR = (m_speed-m_valR)*-1;

    if (speedL<-15)
        speedL=-15;

    if (speedR<-15)
        speedR=-15;

//    qDebug() << m_valL << m_valR << speedL << speedR;
    m_pWalkThread->setDualSpeed(speedL, speedR);
}

void robotWorker::onAxisLeftX(double value)
{
    int speed = map (value, -1,1, -MAX_SPEED/2, MAX_SPEED/2);
    if (value<0)
        m_valL = qAbs(speed)*-1;
    else
        m_valR = qAbs(speed)*-1;

    if (value==0) {
        m_valL=0;
        m_valR=0;
    }

    setSpeed ();
}

void robotWorker::onAxisLeftY(double value)
{
    m_speed = map (value, -1,1, -MAX_SPEED/2, MAX_SPEED/2);
    setSpeed();
}

void robotWorker::onAxisRightX(double value)
{
    int angle = map (value, -1,1, 180, 0);
    m_pPositionThrd->setAzimuth(angle);
}

void robotWorker::onAxisRightY(double value)
{
    int angle = map (value, -1,1, 0, 120);
    m_pPositionThrd->setElevation(angle);
}

void robotWorker::onButtonPS(bool value)
{
    if (value) {
        setAutonomous( m_pPositionThrd->isRunning() ? false : true);
    }
}

void robotWorker::onGamepadConnected()
{
    qDebug() << "Connected!";
    setConnectedStatus(true);
}

void robotWorker::onGamepadDisconnected()
{
    setConnectedStatus(false);
}
