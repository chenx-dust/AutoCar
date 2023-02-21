#ifndef _PID_CONTROLLER_H_
#define _PID_CONTROLLER_H_

typedef struct
{
    double Kp;
    double Ki;
    double Kd;
    double dt;
    double target;
    double error[3];
} PID_controller;

double PID_update(PID_controller *pid, double input);

#endif
