#include "ir_sensor.h"
#include "const.h"
#define ABS(X) ((X) >= 0 ? (X) : (-(X)))

void IR_setup(IR_sensor *ir)
{
    for (int8_t i = 0; i < IR_SENSOR_TOTAL; i++)
        pinMode(ir->pin[i], INPUT);
}

int8_t IR_read(IR_sensor *ir, int *ret_num)
{
    int now = 0, num = 0;
    for (int8_t i = IR_SENSOR_MEDIAN, j = IR_SENSOR_MEDIAN; i >= 0 && j < IR_SENSOR_TOTAL ; i--, j++)
    {
        if (digitalRead(ir->pin[i]) == HIGH)
            now = i - IR_SENSOR_MEDIAN, num++;
        if (digitalRead(ir->pin[j]) == HIGH)
            now = j - IR_SENSOR_MEDIAN, num++;
    }
    // for (int8_t i = 0; i < IR_SENSOR_TOTAL ; i++)
    // {
    //     Serial.print(digitalRead(ir->pin[i]));
    //     Serial.print(" ");
    // }
    // Serial.print("\r\n");
    *ret_num = num;
    // return double(total)/ num + 0.5;
    if (num == 0)
    {
        if (ir->last_error > 0)
            return ir->last_error + 1;
        else if (ir->last_error < 0)
            return ir->last_error - 1;
        else
            return 0;
    }
    if (ABS(ir->last_error - now) > 5)
        return ir->last_error;
    ir->last_error = now;
    return now;
}
