#ifndef MOTIONTASKS_DEFS_H
#define MOTIONTASKS_DEFS_H

enum tasks {
    TSK_NONE, // 0
    TSK_STEP_FORWARD,
    TSK_STEP_BACKWARD,
    TSK_TURN_LEFT,
    TSK_TURN_RIGHT,
    TSK_STOP
};

struct stTask {
    tasks m_task  = TSK_STOP;
    int   m_tSecs = 0;
    int   m_speed = 0;
};

#endif // MOTIONTASKS_DEFS_H
