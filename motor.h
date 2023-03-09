#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <MsTimer2.h>

#include "encoder.h"
#include "pid_controller.h"

typedef struct
{
    Encoder *encoder;
    PID_controller *pid;
    uint8_t pin_en;
    uint8_t pin_ina;
    uint8_t pin_inb;
    double speed;
    int16_t output;
} Motor;

void Motor_setup(Motor *motor);
double Motor_updateSpeed(Motor *motor);
void Motor_setSpeed(Motor *motor, double speed);
void Motor_setTurn(Motor *motor, bool is_reversed);
void Motor_output(Motor *motor, double output);
void Motor_update(Motor *motor);

#endif
