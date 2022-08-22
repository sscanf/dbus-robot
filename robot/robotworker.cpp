#include "robotworker.h"

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

robotWorker::robotWorker(int &argc, char **argv)
    : QCoreApplication(argc, argv)
    , m_connection(QDBusConnection::systemBus()) {

    m_azimut      = 45;
    m_elev        = 60;
    m_lastDirAzim = -1;
    m_lastDirElev = 0;
    m_lastAzimut  = 0;
    m_lastElev    = 0;

    qsrand(QTime::currentTime().msec());
    // initTracker();
    initDistSensors();

    m_pPositionThrd = new positionThrd(m_connection, m_azimut, m_elev);

    m_pWalkThread = new walkThread(m_connection);
    connect(m_pWalkThread, SIGNAL(error(int)), this, SLOT(onMotorsError(int)));

    m_pCameraThrd = new manualCameraThrd(m_connection);
    m_pMotorsThrd = new manualMotorsThrd(m_connection);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    initGamepad();
    setAutonomous(true);
    //    m_pTurnTimer->start (1000);

    //    m_pRandomTimer = new QTimer();
    //    connect (m_pRandomTimer, SIGNAL (timeout()), this, SLOT (on_randomTimeout()));
    //    m_pRandomTimer->start (qrand()%(10*1000)+1000);
    //    m_pTimer->start (1000);

    //    m_pServosIRIface->call("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(45)));
    //    m_pServosIRIface->call("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(90)));
}

void robotWorker::initTracker() {
    qDebug() << "Initializing tracking system ...";

    m_pServosIRIface = new QDBusInterface(QStringLiteral("com.robot.pwm"), //
                                          QStringLiteral("/servos"),
                                          QStringLiteral("com.robot.servoscontroller"),
                                          m_connection,
                                          this);

    m_pTrackingIface = new QDBusInterface(QStringLiteral("com.robot.rotracking"), //
                                          QStringLiteral("/balltracker"),
                                          QStringLiteral("com.robot.rotracking"),
                                          m_connection,
                                          this);

    QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rotracking"), //
                                         QStringLiteral("/balltracker"),
                                         QStringLiteral("com.robot.rotracking"),
                                         QStringLiteral("possitionChanged"),
                                         this,
                                         SLOT(onPositionChanged(QPoint)));

    QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rotracking"), //
                                         QStringLiteral("/balltracker"),
                                         QStringLiteral("com.robot.rotracking"),
                                         QStringLiteral("ballLost"),
                                         this,
                                         SLOT(onBallLost()));

    QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rotracking"),
                                         QStringLiteral("/irtracker"),
                                         QStringLiteral("com.robot.rotracking"),
                                         QStringLiteral("positionChanged"),
                                         this,
                                         SLOT(onPositionChanged(QPoint, QPoint, QPoint, QPoint)));
}

void robotWorker::initDistSensors() {
    qDebug() << "Initializing collision sensors ...";

    for (int n = 0; n < 6; n++) {
        m_collisionSensors[n] = {16, false};
    }

    m_pDistanceIface = new QDBusInterface(QStringLiteral("com.robot.rosensors"), //
                                          QStringLiteral("/rosensors/distance"),
                                          QStringLiteral("com.robot.rosensors"),
                                          m_connection,
                                          this);

    bool ret = QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rosensors"), //
                                                    QStringLiteral("/rosensors/distance"),
                                                    QStringLiteral("com.robot.rosensors"),
                                                    QStringLiteral("distanceChanged"),
                                                    this,
                                                    SLOT(onDistanceChanged(int, int)));
    if (!ret) {
        qDebug() << "Can't catch signal Collision";
    }
}

void robotWorker::initGamepad() {
    bool ret;
    qDebug() << "Initializing gamepad control ...";
    m_pGamepadIface = new QDBusInterface(QStringLiteral("com.robot.rogamepad"), //
                                         QStringLiteral("/rogamepad/dualshock4"),
                                         QStringLiteral("com.robot.rogamepad.dualshock4"),
                                         m_connection,
                                         this);

    ret = QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rogamepad"), //
                                               QStringLiteral("/rogamepad/dualshock4"),
                                               QStringLiteral("com.robot.rogamepad.dualshock4"),
                                               QStringLiteral("buttonPS"),
                                               this,
                                               SLOT(onButtonPS(bool)));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret = QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rogamepad"),
                                               QStringLiteral("/rogamepad/dualshock4"),
                                               QStringLiteral("com.robot.rogamepad.dualshock4"),
                                               QStringLiteral("connected"),
                                               this,
                                               SLOT(onGamepadConnected()));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
    ret = QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rogamepad"),
                                               QStringLiteral("/rogamepad/dualshock4"),
                                               QStringLiteral("com.robot.rogamepad.dualshock4"),
                                               QStringLiteral("disconnected"),
                                               this,
                                               SLOT(onGamepadDisconnected()));
    if (!ret) {
        qDebug() << "Error initialitzing gamepad";
    }
}

double robotWorker::map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void robotWorker::onTimeout() {
    m_azimut += m_lastDirAzim;
    m_elev += m_lastDirElev;

    if (m_azimut < MIN_AZIM) {
        m_lastDirAzim = 2;
        m_totalCameraRounds++;
    }
    if (m_azimut > MAX_AZIM) {
        m_lastDirAzim = -2;
        m_totalCameraRounds++;
    }

    if (m_elev < MIN_ELEV) {
        m_lastDirElev = 1;
        m_totalCameraRounds++;
    }
    if (m_elev > MAX_ELEV) {
        m_lastDirElev = -1;
        m_totalCameraRounds++;
    }
    if (m_totalCameraRounds > 1) {
        m_totalCameraRounds = 0;
        if (getDir() == walkThread::DIR_FORWARDING || getDir() == walkThread::DIR_STOPPED)
            m_pWalkThread->pushTask(TSK_STEP_FORWARD);
        else if (getDir() == walkThread::DIR_BACKWARDING)
            m_pWalkThread->pushTask(TSK_STEP_BACKWARD);


    }
    m_pPositionThrd->setPossition(m_azimut, m_elev);
    m_pTimer->setInterval(60);
}

void robotWorker::onPositionChanged(const QPoint &position) {
    Q_UNUSED(position);
    //    int speed=0;
    m_ballLost = false;
    m_pTimer->stop();
    // setDir(TSK_STOP);
    qDebug() << "Ball found or moving";

    RO3DPoint pos;
    pos           = getCenterDistance();
    double tempaz = map(pos.x(), 0, 720, MIN_AZIM, MAX_AZIM);
    double tempel = map(pos.y(), 0, 480, MIN_ELEV, MAX_ELEV);
    m_azimut      = static_cast<quint16>(m_azimut - (tempaz / 15));
    m_elev        = static_cast<quint16>(m_elev + (tempel / 15));
    m_pPositionThrd->setPossition(m_azimut, m_elev);

    if (pos.z() < 40) {
        m_pWalkThread->pushTask(TSK_STEP_FORWARD);
    } else if (pos.z() > 60) {
        m_pWalkThread->pushTask(TSK_STEP_BACKWARD);
    }

    m_lastDirElev = sign(m_elev - m_lastElev);
    m_lastDirAzim = sign(m_azimut - m_lastAzimut);
    if (m_lastDirAzim == 0)
        m_lastDirAzim = -1;
    m_lastElev   = m_elev;
    m_lastAzimut = m_azimut;
}

void robotWorker::onPositionChanged(const QPoint &pos1, const QPoint &pos2, const QPoint &pos3, const QPoint &pos4) {
    QList<QPoint> positions{pos1, pos2, pos3, pos4};
    m_ballLost = false;
    m_pTimer->stop();
    qDebug() << "Ball found or moving";

    QDBusConnection::systemBus().disconnect(QStringLiteral("com.robot.rotracking"),
                                            QStringLiteral("/irtracker"),
                                            QStringLiteral("com.robot.rotracking"),
                                            QStringLiteral("positionChanged"),
                                            this,
                                            SLOT(onPositionChanged(QPoint, QPoint, QPoint, QPoint)));
    int nTarget = 0;
    foreach (QPoint pos, positions) {
        if (pos != QPoint(1023, 1023)) {
            qint16 centerX = 512 - pos.x();
            qint16 centerY = 384 - pos.y();
            qint16 tempaz  = static_cast<qint16>(map(centerX, 0, 1024, MIN_AZIM, MAX_AZIM));
            qint16 tempel  = static_cast<qint16>(map(centerY, 0, 768, MIN_ELEV, MAX_ELEV));
            //            m_elev += tempel/100;
            //            m_azimut += tempaz/100;

            m_azimut = static_cast<quint16>(m_azimut + (tempaz / 15));
            m_elev   = static_cast<quint16>(m_elev + (tempel / 15));
            //            m_pServosIRIface->call("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(m_azimut)));
            //            m_pServosIRIface->call("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(m_elev)));
            qDebug() << m_azimut << m_elev;
            m_pPositionThrd->setPossition(m_azimut, m_elev);
            break;
        } else
            nTarget++;
    }

    if (nTarget == 4) {
        onBallLost();
    }
}

RO3DPoint robotWorker::getCenterDistance() {
    RO3DPoint                 pos;
    QDBusPendingReply<QPoint> qPointRet = m_pTrackingIface->call(QLatin1String("centerDistance"));
    if (qPointRet.isValid()) {
        QPoint point = qPointRet.value();
        pos.setX(point.x());
        pos.setY(point.y());
    }

    QDBusPendingReply<qint32> zRet = m_pTrackingIface->call(QLatin1String("zPossition"));
    if (zRet.isValid()) {
        pos.setZ(zRet.value());
    } else
        pos.setZ(0);
    return pos;
}

void robotWorker::setDir(const tasks &task) {
    QList<QVariant> collisions = m_pWalkThread->getCollisions();
    switch (task) {
        case TSK_STEP_FORWARD:
            if (!collisions.contains(frontCenter)) {
                m_pWalkThread->pushTask(task);
            }
            break;

        case TSK_STEP_BACKWARD:
            if (!collisions.contains(rearCenter)) {
                m_pWalkThread->pushTask(task);
            }
            break;

        case TSK_TURN_LEFT:
            if (!collisions.contains(frontLeft)) {
                m_pWalkThread->pushTask(task);
            }
            break;

        case TSK_TURN_RIGHT:
            if (!collisions.contains(frontRight)) {
                m_pWalkThread->pushTask(task);
            }
            break;
        default:
            break;
    }
}

walkThread::direction robotWorker::getDir() {
    walkThread::direction dir = m_pWalkThread->getDirection();
    return dir;
}

void robotWorker::setAutonomous(bool bValue) {
    if (bValue) {
        qDebug() << "Autonomous On";
        setGamepadColor(255, 0, 0);
        m_pPositionThrd->start();
        m_pWalkThread->start();
        m_pTimer->start(1000);
        m_pCameraThrd->terminate();
        m_pMotorsThrd->terminate();
        m_bAutonomous = true;
    } else {
        qDebug() << "Autonomous Off";
        setGamepadColor(0, 255, 0);
        m_pPositionThrd->terminate();
        m_pWalkThread->terminate();
        m_pTimer->stop();
        m_pCameraThrd->start();
        m_pMotorsThrd->start();
        m_bAutonomous = false;
    }
}

void robotWorker::setGamepadColor(int red, int blue, int green) {
    m_pGamepadIface->call(QStringLiteral("redLedValue"), QVariant::fromValue(qint32(red)));
    m_pGamepadIface->call(QStringLiteral("greenLedValue"), QVariant::fromValue(qint32(blue)));
    m_pGamepadIface->call(QStringLiteral("blueLedValue"), QVariant::fromValue(qint32(green)));
}

void robotWorker::setConnectedStatus(bool value) {
    if (value) {
        setGamepadColor(0, 255, 0);
    } else {
        setGamepadColor(0, 0, 0);
        if (m_bAutonomous) {
            setAutonomous(false);
        }
    }
}

void robotWorker::onBallLost() {
    if (m_ballLost == false) {
        qDebug() << "Ball lost";
        // setDir(TSK_STOP);
        m_ballLost = true;
        m_pTimer->start(1000);
    }
}

void robotWorker::onDistanceChanged(int sensor, int distance) {
    int   speed           = m_pWalkThread->getSpeed();
    tasks lstTskRight[]   = {TSK_TURN_RIGHT, TSK_STEP_FORWARD, TSK_STOP};
    tasks lstTskLeft[]    = {TSK_TURN_LEFT, TSK_STEP_FORWARD, TSK_STOP};
    tasks lstTskFCenter[] = {TSK_STEP_BACKWARD};
    tasks lstTskRCenter[] = {TSK_STEP_FORWARD};
    tasks lstTskFLeft[]   = {TSK_TURN_RIGHT, TSK_STEP_FORWARD, TSK_STEP_FORWARD};
    tasks lstTskFRight[]  = {TSK_TURN_LEFT, TSK_STEP_FORWARD, TSK_STEP_FORWARD};
    int   rnd;

    minDistances *sensorDistance = &m_collisionSensors[sensor];

    speed = 1;
    if (speed) {
        if ((distance < sensorDistance->minDistance)) {
            if (sensorDistance->bAlarm == false) {
                sensorDistance->bAlarm = true;
                switch (sensor) {
                    case frontCenter:
                        qDebug() << "Collision on Front Center " << distance;
                        m_pWalkThread->pushTask(TSK_STOP);
                        if (speed > 0) {
                            rnd = qrand() % (sizeof(lstTskFCenter) / sizeof(int));
                            m_pWalkThread->pushTask(lstTskFCenter[rnd]);
                        }
                        break;

                    case rearCenter:
                        m_pWalkThread->pushTask(TSK_STOP);
                        qDebug() << "Collision on Rear Center " << distance;
                        if (speed < 0) {
                            rnd = qrand() % (sizeof(lstTskRCenter) / sizeof(int));
                            m_pWalkThread->pushTask(lstTskRCenter[rnd]);
                        }
                        break;

                    case frontLeft:
                        m_pWalkThread->pushTask(TSK_STOP);
                        qDebug() << "Collision on Front Left " << distance;
                        rnd = qrand() % (sizeof(lstTskFLeft) / sizeof(int));
                        m_pWalkThread->pushTask(lstTskFLeft[rnd]);
                        break;

                    case frontRight:
                        m_pWalkThread->pushTask(TSK_STOP);
                        qDebug() << "Collision on Front Right " << distance;
                        rnd = qrand() % (sizeof(lstTskFRight) / sizeof(int));
                        m_pWalkThread->pushTask(lstTskFRight[rnd]);
                        break;

                    case rearRight:
                        m_pWalkThread->pushTask(TSK_STOP);
                        qDebug() << "Collision on Rear Right " << distance;
                        rnd = qrand() % (sizeof(lstTskRight) / sizeof(int));
                        m_pWalkThread->pushTask(lstTskRight[rnd]);
                        break;

                    case rearLeft:
                        m_pWalkThread->pushTask(TSK_STOP);
                        qDebug() << "Rear Left " << distance;
                        rnd = qrand() % (sizeof(lstTskLeft) / sizeof(int));
                        m_pWalkThread->pushTask(lstTskLeft[rnd]);
                        break;
                }
            }
        } else {
            sensorDistance->bAlarm = false;
        }
    }
}

void robotWorker::onMotorsError(int err) {
    m_pWalkThread->pushTask(TSK_STOP);
    qDebug() << "Error in motoros: " << err;
}

void robotWorker::setSpeed() {
    int speedL = (m_speed - m_valL) * -1;
    int speedR = (m_speed - m_valR) * -1;

    if (speedL < -150)
        speedL = -150;

    if (speedR < -150)
        speedR = -150;

    qDebug() << m_valL << m_valR << speedL << speedR;
    m_pWalkThread->setDualSpeed(speedL, speedR);
}

void robotWorker::onButtonPS(bool value) {
    if (value) {
        setAutonomous(m_pPositionThrd->isRunning() ? false : true);
    }
}

void robotWorker::onGamepadConnected() {
    qDebug() << "Connected!";
    setConnectedStatus(true);
}

void robotWorker::onGamepadDisconnected() {
    setConnectedStatus(false);
}
