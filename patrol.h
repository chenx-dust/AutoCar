#ifndef _PATROL_H_
#define _PATROL_H_

#include "motor.h"
#include "pid_controller.h"
#include "ir_sensor.h"

typedef struct
{
    Motor *motor_l;
    Motor *motor_r;
    PID_controller *pid;
    IR_sensor *ir;
    void (*on_stop)();
} Patrol;

void Patrol_update(Patrol *patrol);
void Patrol_stop(Patrol *Patrol);
void Patrol_start(Patrol *Patrol);

#endif
