#ifndef _PID_CONTROLLER_H_
#define _PID_CONTROLLER_H_

typedef struct PID_controller
{
    double Kp;
    double Ki;
    double Kd;
    double dt;
    double error[3] = {0.0};
    double target;
    double output = 0.0;
};

double PID_update(PID_controller *pid, double input);

#endif
