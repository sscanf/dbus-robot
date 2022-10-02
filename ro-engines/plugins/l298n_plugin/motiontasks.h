#ifndef MOTIONTASKS_H
#define MOTIONTASKS_H

#include <QObject>
#include <QQueue>
#include <motiontasks_defs.h>

class motionTasks : public QObject {

    Q_OBJECT
    Q_ENUM(tasks)

public:
    explicit motionTasks(QObject *parent = nullptr);
    void   push(const stTask &task);
    stTask pop();
    int    count();

private:
    QQueue<stTask *> m_tasks;

signals:
};

#endif // MOTIONTASKS_H
