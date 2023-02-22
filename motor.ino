#include "motor.h"
#include "const.h"

void Motor_setup(Motor *motor)
{
    pinMode(motor->pin_en, OUTPUT);
    pinMode(motor->pin_ina, OUTPUT);
    pinMode(motor->pin_inb, OUTPUT);
    Motor_setTurn(motor, false);
}

double Motor_updateSpeed(Motor *motor)
{
    motor->speed = (Encounter_count(motor->encounter) / 780.0) * 3.1415 * 2.0 * (1000 / TIMER_PERIOD);
    return motor->speed;
}

void Motor_setSpeed(Motor *motor, double speed)
{
    motor->pid->target = speed;
}

void Motor_output(Motor *motor, double output)
{
    if (output < 0)
        Motor_setTurn(motor, true);
    else
        Motor_setTurn(motor, false);
    int out = output < 0 ? -output : output;
    if (out > 255)
        out = 255;
    else if (out < 0)
        out = 0;
    motor->output = out;
    analogWrite(motor->pin_en, out);
}

void Motor_update(Motor *motor)
{
    double output = PID_update(motor->pid, Motor_updateSpeed(motor));
    Motor_output(motor, output);
}

void Motor_setTurn(Motor *motor, bool is_reversed)
{
    if (is_reversed)
    {
        digitalWrite(motor->pin_ina, LOW);
        digitalWrite(motor->pin_inb, HIGH);
    }
    else
    {
        digitalWrite(motor->pin_ina, HIGH);
        digitalWrite(motor->pin_inb, LOW);
    }
}
