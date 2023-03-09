#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#include "const.h"

typedef struct
{
    uint8_t pin[IR_SENSOR_TOTAL];
    int last_error;
    bool right_first;
} IR_sensor;

void IR_setup(IR_sensor *ir);
int8_t IR_read(IR_sensor *ir, int *ret_num);

#endif
