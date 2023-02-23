#include "patrol.h"
#include "const.h"

#define ABS(X) (((X) >= 0) ? (X) : -(X))

// bool is_run = false, is_corner = false, corner_side;
volatile bool is_run = false;
uint16_t stop_turn = 0;
int last_num = 0;

bool double_check(int num, int thres)
{
    if (num >= thres && last_num >= thres)
        return true;
    else
        return false;
}

double k_speed(double in_speed)
{
    if (in_speed >= 0)
        return 0.6 * in_speed;
    else
        return 1.0 * in_speed;
}

// double deal_speed_corner(double in_speed, bool side)
// {
//     if (side == PATROL_LEFT)
//         return PATROL_BASIC_SPEED + PATROL_TURN_SPEED * in_speed;
//     else
//         return PATROL_BASIC_SPEED + PATROL_TURN_SPEED * in_speed;
// }

void Patrol_update(Patrol *patrol)
{
    if (!is_run)
        return;
    int num;
    int8_t error = IR_read(patrol->ir, &num);
    if (double_check(num, PATROL_STOP_THRESHOLD))
    {
        is_run = false;
        *patrol->stop_flag = true;
        return;
    }
    // bool is_negative = error < 0;
    // int8_t error_abs = ABS(error);
    double output = PID_update(patrol->pid, error);
    double speed_l, speed_r;
    last_num = num;
    speed_l = PATROL_BASIC_SPEED + PATROL_TURN_SPEED * k_speed(output);
    speed_r = PATROL_BASIC_SPEED + PATROL_TURN_SPEED * k_speed(-output);
    Motor_setSpeed(patrol->motor_l, speed_l);
    Motor_setSpeed(patrol->motor_r, speed_r);
}

void Patrol_stop(Patrol *patrol)
{
    // Turn around
    // Motor_setSpeed(patrol->motor_l, 1.0 * PATROL_BASIC_SPEED);
    // Motor_setSpeed(patrol->motor_r, 1.0 * PATROL_BASIC_SPEED);
    // delay(500);
    Motor_setSpeed(patrol->motor_l, 0.5 * PATROL_BASIC_SPEED);
    Motor_setSpeed(patrol->motor_r, -0.7 * PATROL_BASIC_SPEED);
    delay(1800);
    Motor_setSpeed(patrol->motor_l, 0);
    Motor_setSpeed(patrol->motor_r, 0);
}

void Patrol_start(Patrol *patrol)
{
    is_run = true;
}
