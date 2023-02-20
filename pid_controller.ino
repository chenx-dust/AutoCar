#include "pid_controller.h"

double PID_update(PID_controller *pid, double input)
{
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->error[0] = pid->target - input;
    pid->output += pid->Kp * (pid->error[0] - pid->error[1]) + pid->Ki * pid->error[0] * pid->dt + pid->Kd * (pid->error[0] - 2 * pid->error[1] + pid->error[2]) / pid->dt;
    return pid->output;
}
