#include "patrol.h"
#include "const.h"

#define ABS(X) (((X) >= 0) ? (X) : -(X))

bool is_run = false;

double deal_speed(double in_speed)
{
    if (in_speed >= 0)
        return PATROL_TURN_SPEED * 0.5 * in_speed;
    else
        return PATROL_TURN_SPEED * 3.0 * in_speed;
}

void Patrol_update(Patrol *patrol)
{
    if (!is_run)
        return;
    int num;
    int8_t error = IR_read(patrol->ir, &num);
    // bool is_negative = error < 0;
    // int8_t error_abs = ABS(error);
    double output = PID_update(patrol->pid, error);
    /// 控制方案A
    // double speed_const = 1.0 - ABS(error) * PATROL_TURN_CONST;
    double speed_const = 1.0;
    // // Output to Motor
    Motor_setSpeed(patrol->motor_l, (PATROL_BASIC_SPEED + deal_speed(output)) * speed_const);
    Motor_setSpeed(patrol->motor_r, (PATROL_BASIC_SPEED + deal_speed(-output)) * speed_const);
    Serial.print(speed_const);
    Serial.print(" ");
    Serial.print(error);
    Serial.print(" ");
    Serial.print((PATROL_BASIC_SPEED + PATROL_TURN_SPEED * output) * speed_const);
    Serial.print(" ");
    Serial.println((PATROL_BASIC_SPEED - PATROL_TURN_SPEED * output) * speed_const);
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
    if (num >= PATROL_STOP_THERS)
        patrol->on_stop();
}

void Patrol_stop(Patrol *patrol)
{
    Motor_setSpeed(patrol->motor_l, 0);
    Motor_setSpeed(patrol->motor_r, 0);
    is_run = false;
}

void Patrol_start(Patrol *patrol)
{
    is_run = true;
}
