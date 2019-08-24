#include "robotworker.h"


robotWorker::robotWorker(int & argc, char ** argv) :
    QCoreApplication(argc, argv),
    m_connection (QDBusConnection::systemBus())

{
    m_azimut=90;
    m_elev=70;
    m_lastDirAzim=0;
    m_lastDirElev=0;

    initTracker();
    initCamera();
//    setAngle (m_azimut,m_elev);

    m_pThrd = new positionThrd(m_azimut, m_elev, this);
    m_pThrd->start();

    m_pTimer = new QTimer();
    connect (m_pTimer, SIGNAL (timeout()), this, SLOT (on_timeout()));
    m_pTimer->start (1000);
}

void robotWorker::initTracker()
{
    m_pTrackingIface = new QDBusInterface ("com.robot.rotracking",
                                           "/tracker",
                                           "com.robot.tracker",
                                           m_connection,
                                           this);

    bool ret = QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                                     "/tracker",
                                                     "com.robot.tracker",
                                                     "possitionChanged",
                                                     this,
                                                     SLOT (on_possitionChanged(const QPoint &)));
    if (!ret) {
        qDebug() << "Can't catch signal possitionChanged";
    }

        ret = QDBusConnection::systemBus().connect( "com.robot.rotracking",
                                                     "/tracker",
                                                     "com.robot.tracker",
                                                     "ballLost",
                                                     this,
                                                     SLOT (on_ballLost()));
    if (!ret) {
        qDebug() << "Can't catch signal ballLost";
    }
}

void robotWorker::initCamera()
{
    m_pCameraIface = new QDBusInterface ("com.robot.rocamera",
                                         "/servos",
                                         "com.robot.servoscontroller",
                                         m_connection,
                                         this);

}

void robotWorker::setAngle(quint16 azim, quint16 elev)
{
    m_pCameraIface->call ("setAngle", QVariant::fromValue(uchar(0)), QVariant::fromValue(quint16(azim)));
    m_pCameraIface->call ("setAngle", QVariant::fromValue(uchar(1)), QVariant::fromValue(quint16(elev)));
}

bool robotWorker::isBallDetected()
{
    QDBusPendingReply<bool>  bDetected = m_pTrackingIface->call ("isBallDetected");
    return bDetected.value();
}

double robotWorker::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void robotWorker::on_timeout()
{
    static int lostCount=0;
//    bool bDetected = false;
//   bool bDetected = isBallDetected();
   if (m_ballLost)
       lostCount++;
   else {
       lostCount=0;
   }
   if (lostCount>2) {
       lostCount=0;
//       m_elev -= m_lastDirElev;
       m_azimut += m_lastDirAzim;

       if (m_azimut<10)
           m_lastDirAzim=2;
       if (m_azimut>175)
           m_lastDirAzim=-2;

       if (m_elev<20)
           m_lastDirElev=-2;
       if (m_elev>90)
           m_lastDirElev=2;

       m_pThrd->setPossition(m_azimut,m_elev);
       qDebug() << m_azimut << m_elev;
   }
   m_pTimer->setInterval(20);
}


void robotWorker::on_possitionChanged(const QPoint &position)
{
    Q_UNUSED (position);
    m_ballLost=false;
    QDBusPendingReply <QPoint> ret = m_pTrackingIface->call(QLatin1String("centerDistance"));
    if(ret.isValid()) {
        QPoint pos = ret.value();
        double tempaz = map (pos.x(),0,320,0,180);
        double tempel = map (pos.y(),0,240,0,45);
        m_azimut = static_cast<quint16>(m_azimut-(tempaz/15));
        m_elev = static_cast<quint16>(m_elev+(tempel/15));
        m_pThrd->setPossition(m_azimut,m_elev);
        m_lastDirElev = m_elev < 0 ? -2 : 2;
        m_lastDirAzim = m_azimut < 0 ? -2 : 2;
        m_pTimer->setInterval(1000);

    }
}

void robotWorker::on_ballLost()
{
    m_ballLost=true;
}
