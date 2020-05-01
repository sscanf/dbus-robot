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

    initTracker();
    initDistSensors();

    m_pPositionThrd = new positionThrd(m_azimut, m_elev);
    m_pPositionThrd->start();

    m_pWalkThread = new walkThread();
    m_pWalkThread->start();

    m_pTimer = new QTimer();
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (onTimeout()));

    m_pTurnTimer = new QTimer();
    connect (m_pTurnTimer, SIGNAL (timeout()), this, SLOT (onTurnTimeout()));
    m_pTurnTimer->start (1000);


//    m_pRandomTimer = new QTimer();
//    connect (m_pRandomTimer, SIGNAL (timeout()), this, SLOT (on_randomTimeout()));
//    m_pRandomTimer->start (qrand()%(10*1000)+1000);
    onBallLost();
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
                                                     SLOT (onPossitionChanged(QPoint )));
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
                                           "/rosensors/frontDistance",
                                           "com.robot.rosensors",
                                           m_connection,
                                           this);

    bool ret = QDBusConnection::systemBus().connect( "com.robot.rosensors",
                                                     "/rosensors/frontDistance",
                                                     "com.robot.rosensors",
                                                     "collision",
                                                     this,
                                                     SLOT (onFrontCollision()));
    if (!ret) {
        qDebug() << "Can't catch signal frontCollision";
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

    if (m_totalCameraRounds>2) {
        m_totalCameraRounds=0;
        m_pWalkThread->pushTask(TSK_STEP_FORWARD);
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
    int speed=0;


    m_ballLost=false;
    m_pTimer->stop();
    m_pWalkThread->pushTask(TSK_STOP);

    RO3DPoint pos;
    pos = getCenterDistance();
    double tempaz = map (pos.x(),0,320,0,180);
    double tempel = map (pos.y(),0,240,0,90);
    m_azimut      = static_cast<quint16>(m_azimut-(tempaz/15));
    m_elev        = static_cast<quint16>(m_elev+(tempel/15));
    m_pPositionThrd->setPossition(m_azimut,m_elev);

    if (pos.z()<40) {
        speed=LOW_SPEED;
    } else if (pos.z()>60) {
        speed=-LOW_SPEED;
    } else {
        speed=0;
    }
    m_pWalkThread->pushTask(TSK_STEP_FORWARD);
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

void robotWorker::onBallLost()
{
    if (m_ballLost != true) {
        qDebug() << "Ball lost";
        m_pWalkThread->pushTask(TSK_STOP);
        m_ballLost=true;
        m_pTimer->start(1000);
    }
}

void robotWorker::onTurnTimeout()
{
    if (m_azimut<90) {
        m_pWalkThread->pushTask(TSK_TURN_RIGHT);
    } else if (m_azimut>90) {
        m_pWalkThread->pushTask(TSK_TURN_LEFT);
    } else
        m_pWalkThread->pushTask(TSK_STOP);
}

void robotWorker::onFrontCollision()
{
    m_pWalkThread->pushTask(TSK_STEP_BACKWARD);
}
