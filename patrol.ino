#include "patrol.h"
#include "const.h"

volatile bool is_run = false;
int last_num[PATROL_LAST] = {0}, num_pt = 0;
// bool slow_mode = false;
double now_speed = PATROL_BASIC_SPEED;
double now_turn = PATROL_TURN_SPEED;

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
        *patrol->stop_flag = true;
        return;
    }
    double output = PID_update(patrol->pid, error);
    // Serial.print(error);
    // Serial.print(" ");
    // Serial.println(output);
    double speed_l, speed_r;
    push_num(num);
    speed_l = now_speed + now_turn * k_speed(output);
    speed_r = now_speed + now_turn * k_speed(-output);
    speed_l *= 1 - ABS(output) / PATROL_SPEED_DIV;
    speed_r *= 1 - ABS(output) / PATROL_SPEED_DIV;
    // bool is_neg = error < 0;
    // int abs_err = is_neg ? -error : error;
    // double sa, sb;
    // switch (error)
    // {
    // case 0:
    //     sa = 1.0 * now_speed;
    //     sb = 1.0 * now_speed;
    //     break;
    // case 1:
    //     sa = 1.1 * now_speed;
    //     sb = 0.7 * now_speed;
    //     break;
    // case 2:
    //     sa = 1.1 * now_speed;
    //     sb = 0.4 * now_speed;
    //     break;
    // case 3:
    //     sa = 0.9 * now_speed;
    //     sb = 0.2 * now_speed;
    //     break;
    // case 4:
    //     sa = 0.8 * now_speed;
    //     sb = -0.3 * now_speed;
    //     break;
    // case 5:
    //     sa = 0.5 * now_speed;
    //     sb = -0.5 * now_speed;
    //     break;
    // }
    // if (is_neg)
    //     speed_l = sa, speed_r = sb;
    // else
    //     speed_l = sb, speed_r = sa;
    Motor_setSpeed(patrol->motor_l, speed_l);
    Motor_setSpeed(patrol->motor_r, speed_r);
}

void Patrol_stop(Patrol *patrol)
{
    is_run = false;
    // Motor_setSpeed(patrol->motor_l, 0.5 * PATROL_BASIC_SPEED);
    // Motor_setSpeed(patrol->motor_r, 0.5 * PATROL_BASIC_SPEED);
    // delay(500);
    Motor_setSpeed(patrol->motor_l, 0.8 * now_speed);
    Motor_setSpeed(patrol->motor_r, -0.5 * now_speed);
    delay(PATROL_TURN_TIME);
    Motor_setSpeed(patrol->motor_l, -0.5 * now_speed);
    Motor_setSpeed(patrol->motor_r, -0.5 * now_speed);
    delay(600);
    Motor_setSpeed(patrol->motor_l, 0);
    Motor_setSpeed(patrol->motor_r, 0);
}

void Patrol_avoid(Patrol *patrol)
{
    is_run = false;
    Motor_setSpeed(patrol->motor_l, -0.8 * now_speed);
    Motor_setSpeed(patrol->motor_r, 0.8 * now_speed);
    delay(320);
    Motor_setSpeed(patrol->motor_l, 1.0 * now_speed);
    Motor_setSpeed(patrol->motor_r, 0.6 * now_speed);
    delay(600);

    int num = 0;
    while (num == 0)
        IR_read(patrol->ir, &num);

    is_run = true;
}

void Patrol_start(Patrol *patrol)
{
    is_run = true;
}
