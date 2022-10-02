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

    m_pPositionThrd = new positionThrd(m_connection, m_azimut, m_elev);
    m_pCameraThrd   = new manualCameraThrd(m_connection);
    m_pMotorsThrd   = new manualMotorsThrd(m_connection);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    //    initTracker();
    initGamepad();
    initDistSensors();
    initMotors();

    setAutonomous(true);
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

    m_pDistanceIface = new QDBusInterface(QStringLiteral("com.robot.rosensors"), //
                                          QStringLiteral("/rosensors/distance"),
                                          QStringLiteral("com.robot.rosensors"),
                                          m_connection,
                                          this);

    bool ret = QDBusConnection::systemBus().connect(QStringLiteral("com.robot.rosensors"), //
                                                    QStringLiteral("/rosensors/distance"),
                                                    QStringLiteral("com.robot.rosensors"),
                                                    QStringLiteral("collision"),
                                                    this,
                                                    SLOT(onCollision(int)));
    if (!ret) {
        qDebug() << "Can't catch signal Collision";
    } else {
        int totalSensors = getTotalSensors();
        for (int n = 0; n < totalSensors; n++)
            m_minDistanceSensors.append(20);
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

void robotWorker::initMotors() {
    qDebug() << "Initializing engine control system ...";
    m_pMotorsIface = new QDBusInterface("com.robot.roengines", //
                                        "/engines",
                                        "com.robot.roengines",
                                        m_connection,
                                        this);
    if (!m_pMotorsIface->isValid()) {
        qDebug() << "Motors interface is not valid";
    } else {
        QDBusConnection::systemBus().connect("com.robot.roengines", //
                                             "/engines",
                                             "com.robot.roengines",
                                             "error",
                                             this,
                                             SLOT(onMotorsError(int)));

        m_pMotorsIface->call("setMaxSpeed", QVariant::fromValue(qint32(50)));
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
    m_pPositionThrd->setPossition(m_azimut, m_elev);
    m_pTimer->setInterval(60);
}

void robotWorker::onPositionChanged(const QPoint &position) {
    Q_UNUSED(position);
    //    int speed=0;
    m_ballLost = false;
    m_pTimer->stop();
    setDir(DIR_STOP);
    qDebug() << "Ball found or moving";

    RO3DPoint pos;
    pos           = getCenterDistance();
    double tempaz = map(pos.x(), 0, 720, MIN_AZIM, MAX_AZIM);
    double tempel = map(pos.y(), 0, 480, MIN_ELEV, MAX_ELEV);
    m_azimut      = static_cast<quint16>(m_azimut - (tempaz / 15));
    m_elev        = static_cast<quint16>(m_elev + (tempel / 15));
    m_pPositionThrd->setPossition(m_azimut, m_elev);

    if (pos.z() < 40) {
        //        m_pWalkThread->pushTask(TSK_STEP_FORWARD);
    } else if (pos.z() > 60) {
        //       m_pWalkThread->pushTask(TSK_STEP_BACKWARD);
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

void robotWorker::setDir(dirs dir) {
    m_direction = dir;

    switch (dir) {
        case DIR_FORWARD:
            pushTask(TSK_STEP_FORWARD, 2);
            break;

        case DIR_BACKWARD:
            pushTask(TSK_STEP_BACKWARD, 2);
            break;

        case DIR_TURN_LEFT:
            pushTask(TSK_TURN_LEFT, 2);
            break;

        case DIR_TURN_RIGHT:
            pushTask(TSK_TURN_RIGHT, 2);
            break;

        case DIR_STOP:
            pushTask(TSK_STOP, 2);
            break;

        default:
            break;
    }
}

void robotWorker::setAutonomous(bool bValue) {
    if (bValue) {
        qDebug() << "Autonomous On";
        setGamepadColor(255, 0, 0);
        m_pPositionThrd->start();
        m_pTimer->start(1000);
        m_pCameraThrd->terminate();
        m_pMotorsThrd->terminate();
        m_bAutonomous = true;
        setDir(DIR_FORWARD);
    } else {
        qDebug() << "Autonomous Off";
        setGamepadColor(0, 255, 0);
        m_pPositionThrd->terminate();
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
        setDir(DIR_FORWARD);
        m_ballLost = true;
        m_pTimer->start(1000);
    }
}

void robotWorker::onCollision(int sensor) {

    qDebug() << "onCollision " << sensor;
    if (m_direction == TSK_STEP_BACKWARD && (sensor == frontCenter || sensor == frontLeft || sensor == frontRight)) {
        return;
    }

    if (m_direction == TSK_STEP_FORWARD && (sensor == rearCenter || sensor == rearLeft || sensor == rearRight)) {
        return;
    }

    //    int totalSensors = getTotalSensors();

    //    QDBusPendingReply<QList<int>> intRet = m_pDistanceIface->call(QLatin1String("getAllDistances"));
    //    if (intRet.isValid()) {
    //        int maxDistance = 0;
    //        int sensorNum   = 0;
    //        for (int n = 0; n < totalSensors; n++) {
    //            if (maxDistance < intRet.value()[n]) {
    //                maxDistance = intRet.value()[n];
    //                sensorNum   = n;
    //            }
    //        }

    switch (sensor) {
        case frontCenter:
            pushTask(TSK_STEP_BACKWARD, 5);
            pushTask(TSK_TURN_LEFT, 5);
            pushTask(TSK_STEP_FORWARD, 2);
            break;

            //            case rearCenter:
            //                setDir(DIR_BACKWARD);
            //                break;

            //            case frontLeft:
            //                setDir(DIR_TURN_LEFT);
            //                break;

            //            case frontRight:
            //                setDir(DIR_TURN_RIGHT);
            //                break;

            //            case rearLeft:
            //                setDir(DIR_TURN_RIGHT);
            //                break;

            //            case rearRight:
            //                setDir(DIR_TURN_LEFT);
            //                break
    }
    //}
}

void robotWorker::onMotorsError(int err) {
    switch (m_direction) {
        case frontCenter:
            setDir(DIR_TURN_LEFT);
            break;

        case rearCenter:
            setDir(DIR_TURN_RIGHT);
            break;

        case frontLeft:
            setDir(DIR_TURN_LEFT);
            break;

        case frontRight:
            setDir(DIR_TURN_RIGHT);
            break;

        case rearLeft:
            setDir(DIR_TURN_RIGHT);
            break;

        case rearRight:
            setDir(DIR_TURN_LEFT);
            break;
    }
    qDebug() << "Error in motoros: " << err;
}

int robotWorker::getTotalSensors() {
    int                    ret    = 0;
    QDBusPendingReply<int> intRet = m_pDistanceIface->call(QLatin1String("getSensorsCount"));
    if (intRet.isValid()) {
        ret = intRet.value();
    }
    return ret;
}

void robotWorker::pushTask(tasks task, int tSecs) {
    QByteArray  block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);
    stTask      stask;

    stask.m_task  = task;
    stask.m_tSecs = tSecs;
    stask.m_speed = m_speed;
    sendStream.writeRawData((const char *)&stask, sizeof(stTask));
    m_pMotorsIface->call("pushTask", block);
    qDebug() << QDBusMessage::ErrorMessage;
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
