#ifndef _CONST_H_
#define _CONST_H_

#define ABS(X) ((X) >= 0 ? (X) : (-(X)))

#define TIMER_PERIOD 10

#define ENC_LA_PIN 18
#define ENC_LB_PIN 19
#define ENC_RA_PIN 20
#define ENC_RB_PIN 21

#define MOTOR_L_PIN 3
#define MOTOR_R_PIN 2
#define MOTOR_L_INA 34
#define MOTOR_L_INB 32
#define MOTOR_R_INA 35
#define MOTOR_R_INB 37

#define MOTOR_PID_KP 20.0
#define MOTOR_PID_KI 15.0
#define MOTOR_PID_KD 0.05

#define PATROL_PID_KP 1.0
#define PATROL_PID_KI 0.0
#define PATROL_PID_KD 0.01
#define PATROL_BASIC_SPEED 10
#define PATROL_TURN_SPEED 2.0
#define PATROL_STOP_THRESHOLD 8
#define PATROL_LAST 3
#define PATROL_TURN_TIME 400
#define PATROL_POS 1.0
#define PATROL_NEG 1.5
#define PATROL_SPEED_DIV 10.0

#define IR_SENSOR_TOTAL 9
#define IR_SENSOR_MEDIAN 4
#define IR_SENSOR_PIN_8 10
#define IR_SENSOR_PIN_7 9
#define IR_SENSOR_PIN_6 8
#define IR_SENSOR_PIN_5 7
#define IR_SENSOR_PIN_4 6
#define IR_SENSOR_PIN_3 5
#define IR_SENSOR_PIN_2 4
#define IR_SENSOR_PIN_1 PIN_A4
#define IR_SENSOR_PIN_0 PIN_A5

#define SERVO_A_PIN 11
#define SERVO_B_PIN 12
#define SERVO_C_PIN 13
#define SERVO_A_BASE 95
#define SERVO_B_BASE 85
#define SERVO_C_BASE 50
#define SERVO_A_UP 20
#define SERVO_C_PICK 40

#endif