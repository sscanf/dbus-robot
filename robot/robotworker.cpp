#include "robotworker.h"

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

robotWorker::robotWorker(int & argc, char ** argv) :
    QCoreApplication(argc, argv),
    m_connection (QDBusConnection::systemBus())

{
    m_azimut=90;
    m_elev=120;
    m_lastDirAzim=-1;
    m_lastDirElev=0;
    m_lastAzimut=0;
    m_lastElev=0;

    qsrand(QTime::currentTime().msec());
    initTracker();
    initDistSensors();

//    m_pPositionThrd = new positionThrd(m_connection, m_azimut, m_elev);

    m_pWalkThread = new walkThread(m_connection);
    connect (m_pWalkThread, SIGNAL (error(int)), this, SLOT (onMotorsError(int)));

   m_pCameraThrd = new manualCameraThrd(m_connection);
    m_pMotorsThrd = new manualMotorsThrd(m_connection);

    m_pTimer = new QTimer();
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));

    m_pTurnTimer = new QTimer();
    connect (m_pTurnTimer, SIGNAL (timeout()), this, SLOT (onTurnTimeout()));



    initGamepad();
    setAutonomous(true);
//    m_pTurnTimer->start (1000);


//    m_pRandomTimer = new QTimer();
//    connect (m_pRandomTimer, SIGNAL (timeout()), this, SLOT (on_randomTimeout()));
//    m_pRandomTimer->start (qrand()%(10*1000)+1000);
//    m_pTimer->start (1000);
}

void robotWorker::initTracker()
{

    m_pServosIRIface = new QDBusInterface ("com.robot.pwm",
                                           "/servos",
                                           "com.robot.servoscontroller",
                                           m_connection,
                                           this);

    m_pTrackingIface = new QDBusInterface ("com.robot.rotracking",
                                           "/balltracker",
                                           "com.robot.rotracking",
                                           m_connection,
                                           this);

    QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                          "/balltracker",
                                          "com.robot.rotracking",
                                          "possitionChanged",
                                          this,
                                          SLOT (onPositionChanged(QPoint)));

    QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                          "/balltracker",
                                          "com.robot.rotracking",
                                          "ballLost",
                                          this,
                                          SLOT (onBallLost()));

    QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                          "/irtracker",
                                          "com.robot.rotracking",
                                          "positionChanged",
                                          this,
                                          SLOT (onPositionChanged(QPoint, QPoint, QPoint, QPoint)));
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

//    m_pPositionThrd->setPossition(m_azimut,m_elev);
    m_pTimer->setInterval(60);
}

void robotWorker::onRandomTimeout()
{

}

void robotWorker::onPositionChanged(QPoint position)
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
//    m_pPositionThrd->setPossition(m_azimut,m_elev);

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

void robotWorker::onPositionChanged(QPoint pos1, QPoint pos2, QPoint pos3, QPoint pos4)
{

    QList<QPoint> positions{pos1,pos2,pos3,pos4};
//    m_ballLost=false;
//    m_pTimer->stop();
//    setDir(TSK_STOP);

    foreach (QPoint pos, positions) {
        if (pos != QPoint(1023,1023)) {
            qint16 centerX = 512-pos.x();
            qint16 centerY = 384-pos.y();
            qint16 tempaz = static_cast<qint16>(map (centerX,0,1024,0,180));
            qint16 tempel = static_cast<qint16>(map (centerY,0,768,0,90));
//            m_elev += tempel/100;
//            m_azimut += tempaz/100;

            m_azimut = static_cast<quint16>(m_azimut-(tempaz/15));
            m_elev   = static_cast<quint16>(m_elev+(tempel/15));
            qDebug() << m_azimut;
            m_pServosIRIface->call ("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(m_azimut)));
            m_pServosIRIface->call ("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(m_elev)));
//            m_pPositionThrd->setPossition(m_azimut,m_elev);
            break;
        }
//        else
//            onBallLost();
    }
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
    } else
        pos.setZ(0);
    return pos;
}

void robotWorker::setDir(tasks task)
{
    QList<QVariant> collisions = m_pWalkThread->getCollisions();
    switch (task) {
        case TSK_STEP_FORWARD:
           if (!collisions.contains (frontCenter)) {
                m_pWalkThread->pushTask(task);
           }
        break;

        case TSK_STEP_BACKWARD:
           if (!collisions.contains (rearCenter)){
                m_pWalkThread->pushTask(task);
           }
        break;

        case TSK_TURN_LEFT:
           if (!collisions.contains (frontLeft)) {
                m_pWalkThread->pushTask(task);
           }
        break;

        case TSK_TURN_RIGHT:
           if (!collisions.contains (frontRight)) {
                m_pWalkThread->pushTask(task);
           }
        break;

        default:
                m_pWalkThread->pushTask(task);
        break;
    }
}

void robotWorker::setAutonomous(bool bValue)
{
    if (bValue) {
        qDebug() << "Autonomous On";
        setGamepadColor(255,0,0);
//        m_pPositionThrd->start();
        m_pWalkThread->start();
        m_pTimer->start(1000);
        m_pCameraThrd->terminate();
        m_pMotorsThrd->terminate();
        m_bAutonomous=true;
    } else {
        qDebug() << "Autonomous Off";
        setGamepadColor(0,255,0);
//        m_pPositionThrd->terminate();
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
    if (m_azimut<90) {
        setDir(lstTsk[rnd]);
    } else if (m_azimut>90) {
        setDir(lstTsk[rnd]);
    }
}

void robotWorker::onCollision(int sensor)
{
    qDebug() << "onCollisions";
    int speed = m_pWalkThread->getSpeed();
    tasks lstTskRight  [] = {TSK_TURN_RIGHT, TSK_STEP_FORWARD,TSK_STOP};
    tasks lstTskLeft   [] = {TSK_TURN_LEFT, TSK_STEP_FORWARD,TSK_STOP};
    tasks lstTskFCenter[] = {TSK_TURN_LEFT, TSK_TURN_RIGHT,TSK_STEP_BACKWARD};
    tasks lstTskRCenter[] = {TSK_TURN_LEFT, TSK_TURN_RIGHT,TSK_STEP_FORWARD};
    tasks lstTskFLeft  [] = {TSK_TURN_RIGHT, TSK_STEP_FORWARD,TSK_STEP_FORWARD};
    tasks lstTskFRight [] = {TSK_TURN_LEFT, TSK_STEP_FORWARD,TSK_STEP_FORWARD};
    int rnd;

    speed=1;
    qDebug() << sensor;
    if (speed) {
        switch (sensor) {
            case frontCenter:
                qDebug() << "Front Center";
                if (speed>0) {
                     rnd = qrand() % (sizeof(lstTskFCenter)/sizeof(int));
                     setDir(lstTskFCenter[rnd]);
                }
            break;

            case rearCenter:
                qDebug() << "Rear Center";
                if (speed<0) {
                     rnd = qrand() % (sizeof(lstTskRCenter)/sizeof(int));
                     setDir(lstTskRCenter[rnd]);
                }
            break;

            case frontLeft:
                qDebug() << "Front Left";
                rnd = qrand() % (sizeof(lstTskFLeft)/sizeof(int));
                setDir(lstTskFLeft[rnd]);
            break;

            case frontRight:
                qDebug() << "Front Right";
                rnd = qrand() % (sizeof(lstTskFRight)/sizeof(int));
                setDir(lstTskFRight[rnd]);
            break;

           case rearRight:
                qDebug() << "Rear Right";
                rnd = qrand() % (sizeof(lstTskRight)/sizeof(int));
                if (speed<0)
                    setDir(lstTskRight[rnd]);
                else if (m_pWalkThread->getDirection()==walkThread::DIR_TURNING_RIGHT)
                    setDir(lstTskRight[rnd]);
           break;

           case rearLeft:
                qDebug() << "Rear Left";
                rnd = qrand() % (sizeof(lstTskLeft)/sizeof(int));
                if (speed<0)
                    setDir(lstTskLeft[rnd]);
                else if (m_pWalkThread->getDirection()==walkThread::DIR_TURNING_RIGHT)
                    setDir(lstTskLeft[rnd]);
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

void robotWorker::onButtonPS(bool value)
{
    if (value) {
//        setAutonomous( m_pPositionThrd->isRunning() ? false : true);
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
