#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <MsTimer2.h>

#include "encounter.h"
#include "pid_controller.h"

typedef struct
{
    Encounter encounter;
    PID_controller pid;
} Motor;

typedef struct
{
    Motor left;
    Motor right;
    uint32_t dt;
    void (*intFunc)(void);
} CarMotor;

void Motor_setup(Motor* motor)
{
    Encounter_setup(&motor->encounter);
}

void CarMotor_setup(CarMotor* carMotor)
{
    Motor_setup(&carMotor->left);
    Motor_setup(&carMotor->right);
    MsTimer2::set(carMotor->dt, carMotor->intFunc);
    MsTimer2::start();
}

#endif
