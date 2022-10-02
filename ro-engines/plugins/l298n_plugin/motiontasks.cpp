#include <QDebug>
#include "motiontasks.h"

motionTasks::motionTasks(QObject *parent)
    : QObject{parent} {}

void motionTasks::push(const stTask &task) {
    stTask *pTask = new stTask;
    memcpy(pTask, &task, sizeof(stTask));
    m_tasks.enqueue(pTask);
}

stTask motionTasks::pop() {
    stTask task;
    if (m_tasks.count()) {
        stTask *pTask = m_tasks.dequeue();
        memcpy(&task, pTask, sizeof(stTask));
        delete pTask;
    }
    return task;
}

int motionTasks::count() {
    return m_tasks.count();
}
