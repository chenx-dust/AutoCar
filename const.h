#ifndef _CONST_H_
#define _CONST_H_

#define TIMER_PERIOD 10

#define ENC_LA_PIN 2
#define ENC_LB_PIN 4
#define ENC_RA_PIN 3
#define ENC_RB_PIN 5

#define MOTOR_L_PIN 6
#define MOTOR_R_PIN 7
#define MOTOR_L_INA 44
#define MOTOR_L_INB 45
#define MOTOR_R_INA 46
#define MOTOR_R_INB 47

#define MOTOR_PID_KP 15.0
#define MOTOR_PID_KI 20.0
#define MOTOR_PID_KD 0.05

#define PATROL_PID_KP 1.5
#define PATROL_PID_KI 0.1
#define PATROL_PID_KD 0.0
#define PATROL_BASIC_SPEED 10.0
#define PATROL_TURN_SPEED 1.75
// #define PATROL_TURN_CONST 0.1
#define PATROL_STOP_THRESHOLD 8
#define PATROL_CORNER_THRESHOLD 5
#define PATROL_CORNER_POS 1.0
#define PATROL_CORNER_NEG -0.5
#define PATROL_CORNER_TIME 500
#define PATROL_LEFT false
#define PATROL_RIGHT true

#define IR_SENSOR_TOTAL 9
#define IR_SENSOR_MEDIAN 4
#define IR_SENSOR_PIN_0 22
#define IR_SENSOR_PIN_1 23
#define IR_SENSOR_PIN_2 24
#define IR_SENSOR_PIN_3 25
#define IR_SENSOR_PIN_4 26
#define IR_SENSOR_PIN_5 27
#define IR_SENSOR_PIN_6 28
#define IR_SENSOR_PIN_7 29
#define IR_SENSOR_PIN_8 30 

#define SERVO_A_PIN 8
#define SERVO_B_PIN 9
#define SERVO_C_PIN 10
#define SERVO_A_BASE 95
#define SERVO_B_BASE 85
#define SERVO_C_BASE 50
#define SERVO_A_UP 30
#define SERVO_C_PICK 45

#endif