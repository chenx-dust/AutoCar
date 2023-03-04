#include "patrol.h"
#include "const.h"

volatile bool is_run = false;
int last_num[PATROL_LAST] = {0}, num_pt = 0;
bool slow_mode = false;
double now_speed = PATROL_BASIC_SPEED;

bool double_check(int num, int thres)
{
    if (num <= thres)
        return false;
    for (int i = 0; i < PATROL_LAST; ++i)
        if (last_num[i] <= thres)
            return false;
    return true;
}

void push_num(int num)
{
    last_num[num_pt] = num;
    num_pt = num_pt >= PATROL_LAST - 1 ? 0 : num_pt + 1;
}

double k_speed(double in_speed)
{
    if (in_speed >= 0)
        return PATROL_POS * in_speed;
    else
        return PATROL_NEG * in_speed;
}

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
    double output = PID_update(patrol->pid, error);
    // if (!slow_mode && )
    // {
    //     slow_mode = true;
    //     now_speed *= 0.7;
    // }
    double speed_l, speed_r;
    push_num(num);
    speed_l = now_speed + PATROL_TURN_SPEED * k_speed(output);
    speed_r = now_speed + PATROL_TURN_SPEED * k_speed(-output);
    Motor_setSpeed(patrol->motor_l, speed_l);
    Motor_setSpeed(patrol->motor_r, speed_r);
}

void Patrol_stop(Patrol *patrol)
{
    // Motor_setSpeed(patrol->motor_l, 0.5 * PATROL_BASIC_SPEED);
    // Motor_setSpeed(patrol->motor_r, 0.5 * PATROL_BASIC_SPEED);
    // delay(500);
    Motor_setSpeed(patrol->motor_l, 0.8 * PATROL_BASIC_SPEED);
    Motor_setSpeed(patrol->motor_r, -0.5 * PATROL_BASIC_SPEED);
    delay(PATROL_TURN_TIME);
    Motor_setSpeed(patrol->motor_l, 0);
    Motor_setSpeed(patrol->motor_r, 0);
}

void Patrol_start(Patrol *patrol)
{
    is_run = true;
}
