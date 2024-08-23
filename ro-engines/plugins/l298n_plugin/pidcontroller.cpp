#include "pidcontroller.h"

#ifdef QT_DEBUG
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif

PIDController::PIDController(double kp, double ki, double kd, QObject *parent)
    : QObject(parent)
    , m_kp(kp)
    , m_ki(ki)
    , m_kd(kd)
    , m_prev_error(0)
    , m_integral(0) {}

int PIDController::Compute(double setpoint, double measured_value) {
    double ret   = 0;
    double error = setpoint - measured_value;
    m_integral += error;
    double derivative = error - m_prev_error;
    m_prev_error      = error;

    ret = m_kp * error + m_ki * m_integral + m_kd * derivative;
    return ret;
}

#ifdef QT_DEBUG
#pragma GCC pop_options
#endif
