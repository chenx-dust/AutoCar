#include "patrol.h"
#include "const.h"

void Patrol_update(Patrol *patrol)
{
    int8_t error = IR_read(patrol->ir);
    double output = PID_update(patrol->pid, error);
    double speed_const = PATROL_SPEED_CONST * (error == 0 ? 1.0 : 0.5);
    // Output to Motor
    Motor_setSpeed(patrol->motor_l, PATROL_BASIC_SPEED + speed_const * output);
    Motor_setSpeed(patrol->motor_r, PATROL_BASIC_SPEED - speed_const * output);
}
