#include "motor.h"
#include "const.h"

double Motor_updateSpeed(Motor *motor)
{
    motor->speed = Encounter_count(motor->encounter) / MOTOR_MAX_CNT;
    return motor->speed;
}

void Motor_setSpeed(Motor *motor, double speed)
{
    motor->pid->target = speed;
}

void Motor_output(Motor *motor, double output)
{
    int out = output;
    if (out > 255)
        out = 255;
    else if (out < 0)
        out = 0;
    analogWrite(motor->pin, out);
}

void Motor_update(Motor *motor)
{
    double output = PID_update(motor->pid, Motor_updateSpeed(motor));
    Motor_output(motor, output);
}
