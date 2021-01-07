#include <QDebug>
#include <QDBusReply>
#include "walkthread.h"

walkThread::walkThread(QDBusConnection connection, QObject *parent) :
    QThread (parent),
    m_connection (connection)
{
    m_pEnginesIface = new QDBusInterface ("com.robot.roengines",
                                         "/engines",
                                         "com.robot.roengines",
                                         m_connection,
                                         this);
    if (!m_pEnginesIface->isValid()){
        qDebug() << "Engines interface is not valid";
    }

     QDBusConnection::systemBus().connect( "com.robot.roengines",
                                           "/engines",
                                           "com.robot.roengines",
                                           "error",
                                           this,
                                           SLOT (onEnginesError(int)));

    m_pSensorsIface = new QDBusInterface("com.robot.rosensors",
                                         "/rosensors/distance",
                                         "com.robot.rosensors",
                                         m_connection,
                                         this);

    QDBusMessage msg = m_pEnginesIface->call ("setMaximumSpeed", QVariant::fromValue(qint32(50)));
    stop();
}

void walkThread::setDualSpeed(int left, int right)
{
    QDBusMessage msg = m_pEnginesIface->call ("setDualSpeed", QVariant::fromValue(qint32(left)), QVariant::fromValue(qint32(right)));
}

void walkThread::setSpeed(int speed)
{
    m_speed= speed;
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(m_speed)));
}

int walkThread::getSpeed()
{
    int ret=0;
    QDBusPendingReply<int> r = m_pEnginesIface->call(QLatin1String("getSpeed"));
    if(r.isValid()) {
         ret= r.value();
    }
    return ret;
}

QList<QVariant> walkThread::getCollisions()
{
    QList<QVariant> arr;
    QDBusPendingReply<QList<QVariant>> r = m_pSensorsIface->call(QLatin1String("getCollisions"));
    if(r.isValid()) {
         arr= r.value();
    }
    return arr;
}

void walkThread::terminate()
{
    stop();
}

void walkThread::turn(int speed)
{
    m_pEnginesIface->call ("setTurn", QVariant::fromValue(qint32(speed)));
}

void walkThread::pushTask(tasks task)
{
    m_tasks.enqueue(task);
}

walkThread::direction walkThread::getDirection()
{
    direction ret=DIR_ERROR;
    QDBusPendingReply<int> r = m_pEnginesIface->call(QLatin1String("getDirection"));
    if(r.isValid()) {
         ret= static_cast<direction>(r.value());
    }
    return ret;
}

void walkThread::stepForward()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(m_speed)));
}

void walkThread::stepBackward()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(-m_speed)));
}

void walkThread::turnLeft()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setTurn", QVariant::fromValue(qint32(m_speed)));
}

void walkThread::turnRight()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setTurn", QVariant::fromValue(qint32(-m_speed)));
}

void walkThread::stop()
{
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(0)));
}

void walkThread::run()
{
    forever {
        if (!m_tasks.isEmpty()) {
            tasks task = m_tasks.dequeue();
            switch (task){

                case TSK_STEP_FORWARD:
                    stepForward();
                break;

                case TSK_STEP_BACKWARD:
                    stepBackward();
                break;

                case TSK_TURN_LEFT:
                    turnLeft();
                break;

                case TSK_TURN_RIGHT:
                    turnRight();
                break;

                case TSK_STOP:
                    stop();
                break;
            }
        }
        QThread::msleep(1);
    }
}

void walkThread::onEnginesError(int err)
{
    emit error(err);
}
