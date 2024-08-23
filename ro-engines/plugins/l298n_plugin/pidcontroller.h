#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <QObject>

class PIDController : public QObject {
    Q_OBJECT
public:
public:
    explicit PIDController(double kp, double ki, double kd, QObject *parent = nullptr);
    int Compute(double setpoint, double measured_value);

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_prev_error;
    double m_integral;

signals:
};

#endif // PIDCONTROLLER_H
