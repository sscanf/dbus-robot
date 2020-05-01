#include <QDebug>
#include "walkthread.h"

walkThread::walkThread(QObject *parent) :
    QThread (parent)
{
    QDBusConnection connection (QDBusConnection::systemBus());
    m_pEnginesIface = new QDBusInterface ("com.robot.roengines",
                                         "/engines",
                                         "com.robot.roengines",
                                         connection,
                                         this);

    if (!m_pEnginesIface->isValid()){
        qDebug() << "Engines interface is not valid";
    }
}

void walkThread::setSpeed(int speed)
{
    m_speed= speed;
}

void walkThread::pushTask(tasks task)
{
    m_tasks.enqueue(task);
    qDebug() << "Task queing " << task << " empty = " << m_tasks.isEmpty();
}

void walkThread::stepForward()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(m_speed)));
    msleep(4000);
    stop();
}

void walkThread::stepBackward()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setSpeed", QVariant::fromValue(qint32(-m_speed)));
    msleep(4000);
    stop();
}

void walkThread::turnLeft()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setTurn", QVariant::fromValue(qint32(m_speed)));
    msleep(4000);
    stop();
}

void walkThread::turnRight()
{
    stop();
    QDBusMessage msg = m_pEnginesIface->call ("setTurn", QVariant::fromValue(qint32(-m_speed)));
    msleep(4000);
    stop();
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
            qDebug() << "Dequeing Task = " << task;
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
