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
    volatile bool *stop_flag;
} Patrol;

void Patrol_update(Patrol *patrol);
void Patrol_stop(Patrol *Patrol);
void Patrol_start(Patrol *Patrol);
void Patrol_avoid(Patrol *patrol);
void Patrol_turn(Patrol *patrol, bool is_right);

#endif
