#include "patrol.h"
#include "const.h"

#define ABS(X) (((X) >= 0) ? (X) : -(X))

// bool is_run = false, is_corner = false, corner_side;
bool is_run = false;
uint16_t stop_turn = 0;
int last_num = 0;

bool double_check(int num, int thres)
{
    if (num >= thres && last_num >= thres)
        return true;
    else
        return false;
}

// double deal_speed(double in_speed, bool side)
// {
//     if (side == PATROL_LEFT)
//         return PATROL_BASIC_SPEED + PATROL_TURN_SPEED * in_speed;
//     else
//         return PATROL_BASIC_SPEED + PATROL_TURN_SPEED * in_speed;
// }

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
        patrol->on_stop();
        return;
    }
    // bool is_negative = error < 0;
    // int8_t error_abs = ABS(error);
    double output = PID_update(patrol->pid, error);
    double speed_l, speed_r;
    if (stop_turn > 0)
    {
        Serial.println("Pass.");
        stop_turn--;
        last_num = num;
        return;
    }
    /// 控制方案A
    // Output to Motor
    // if (num >= PATROL_CORNER_THRESHOLD)
    //     is_corner = true, corner_side = error < 0 ? PATROL_LEFT : PATROL_RIGHT;
    // if (error == 0)
    //     is_corner = false;
    if (double_check(num, PATROL_CORNER_THRESHOLD))
    {
        Serial.println("Corner Mode.");
        if (error > 0)
        {
            Motor_setSpeed(patrol->motor_l, PATROL_CORNER_NEG * PATROL_BASIC_SPEED);
            Motor_setSpeed(patrol->motor_r, PATROL_CORNER_POS * PATROL_BASIC_SPEED);
        }
        else
        {
            Motor_setSpeed(patrol->motor_l, PATROL_CORNER_POS * PATROL_BASIC_SPEED);
            Motor_setSpeed(patrol->motor_r, PATROL_CORNER_NEG * PATROL_BASIC_SPEED);
        }
        stop_turn = PATROL_CORNER_TIME / TIMER_PERIOD;
        return;
    }
    last_num = num;
    speed_l = PATROL_BASIC_SPEED + PATROL_TURN_SPEED * output;
    speed_r = PATROL_BASIC_SPEED - PATROL_TURN_SPEED * output;
    Motor_setSpeed(patrol->motor_l, speed_l);
    Motor_setSpeed(patrol->motor_r, speed_r);
    Serial.print(error);
    Serial.print(" ");
    Serial.print(speed_l);
    Serial.print(" ");
    Serial.println(speed_r);
    /// 控制方案B
    // double speed_a = PATROL_BASIC_SPEED, speed_b = PATROL_BASIC_SPEED;
    // switch (error_abs)
    // {
    // case 1:
    //     speed_a *= 0.75;
    //     speed_b *= 1.25;
    //     break;
    // case 2:
    //     speed_a *= 0.5;
    //     speed_b *= 1.25;
    //     break;
    // case 3:
    //     speed_a *= -0.1;
    //     speed_b *= 1.0;
    //     break;
    // case 4:
    //     speed_a *= -0.25;
    //     speed_b *= 0.75;
    //     break;
    // }
    // if (is_negative)
    // {
    //     Motor_setSpeed(patrol->motor_l, speed_b);
    //     Motor_setSpeed(patrol->motor_r, speed_a);
    // }
    // else
    // {
    //     Motor_setSpeed(patrol->motor_l, speed_a);
    //     Motor_setSpeed(patrol->motor_r, speed_b);
    // }
}

void Patrol_stop(Patrol *patrol)
{
    is_run = false;
    Motor_setSpeed(patrol->motor_l, 0);
    Motor_setSpeed(patrol->motor_r, 0);
}

void Patrol_start(Patrol *patrol)
{
    is_run = true;
}
