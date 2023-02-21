#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <MsTimer2.h>

#include "encounter.h"
#include "pid_controller.h"

typedef struct
{
    Encounter *encounter;
    PID_controller *pid;
    uint8_t pin;
    double speed;
    int16_t output;
} Motor;

double Motor_updateSpeed(Motor *motor);
void Motor_setSpeed(Motor *motor, double speed);
void Motor_output(Motor *motor, double output);
void Motor_update(Motor *motor);

#endif
