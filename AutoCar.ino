#include <Servo.h>

#include "motor.h"
#include "encounter.h"
#include "const.h"
#include "ir_sensor.h"
#include "patrol.h"
#include "arm.h"

volatile bool is_stop = false;

void Eint_l();
void Eint_r();

Encounter enc_l = {ENC_LA_PIN, ENC_LB_PIN, 0, Eint_l};
Encounter enc_r = {ENC_RA_PIN, ENC_RB_PIN, 0, Eint_r};

void Eint_l() { Encounter_interrupt(&enc_l); }
void Eint_r() { Encounter_interrupt(&enc_r); }

PID_controller motor_pid_l = {MOTOR_PID_KP, MOTOR_PID_KI, MOTOR_PID_KD, TIMER_PERIOD / 1000.0, 0.0};
PID_controller motor_pid_r = {MOTOR_PID_KP, MOTOR_PID_KI, MOTOR_PID_KD, TIMER_PERIOD / 1000.0, 0.0};

Motor motor_l = {&enc_l, &motor_pid_l, MOTOR_L_PIN, MOTOR_L_INA, MOTOR_L_INB};
Motor motor_r = {&enc_r, &motor_pid_r, MOTOR_R_PIN, MOTOR_R_INA, MOTOR_R_INB};

PID_controller patrol_pid = {PATROL_PID_KP, PATROL_PID_KI, PATROL_PID_KD, TIMER_PERIOD / 1000.0};
IR_sensor ir_sensor = {{IR_SENSOR_PIN_0, IR_SENSOR_PIN_1, IR_SENSOR_PIN_2, IR_SENSOR_PIN_3, IR_SENSOR_PIN_4, IR_SENSOR_PIN_5, IR_SENSOR_PIN_6, IR_SENSOR_PIN_7, IR_SENSOR_PIN_8}};
Patrol patrol = {&motor_l, &motor_r, &patrol_pid, &ir_sensor, &is_stop};

Servo servoA, servoB, servoC;

void onTimer()
{
    Motor_update(&motor_l);
    Motor_update(&motor_r);
    Patrol_update(&patrol);
    // Serial.print("Left motor: ");
    // Serial.print(motor_l.speed);
    // Serial.print(" ");
    // Serial.println(motor_l.output);
    // Serial.print("Right motor: ");
    // Serial.print(motor_r.speed);
    // Serial.print(" ");
    // Serial.println(motor_r.output);
}

void onStop()
{
    Serial.println("STOP.");
    Patrol_stop(&patrol);
    Arm_drop(&servoA, &servoB, &servoC);
    is_stop = false;
}

void setup()
{
    Serial.begin(9600);
    Encounter_setup(&enc_l);
    Encounter_setup(&enc_r);
    IR_setup(&ir_sensor);
    Motor_setup(&motor_l);
    Motor_setup(&motor_r);
    Arm_setup(&servoA, &servoB, &servoC);
    MsTimer2::set(TIMER_PERIOD, onTimer);
    MsTimer2::start();
    Motor_setSpeed(&motor_l, 10);
    Motor_setSpeed(&motor_l, 10);
    delay(50);
    // Arm_pickup(&servoA, &servoB, &servoC);
    Patrol_start(&patrol);
    // delay(1000);
    // Arm_drop(&servoA, &servoB, &servoC);
}

int cnt=0;

void loop()
{
    if (is_stop)
        onStop();
    // if (Serial.available())
    // {
    // }
    // if(cnt==1000)
    //     Motor_setSpeed(&motor_l, 5);
    // else if(cnt==2000)
    //     Motor_setSpeed(&motor_l, 15);
    // else if (cnt==3000)
    // {
    //     Motor_setSpeed(&motor_l, 25);
    //     cnt=0;
    // }
    // ++cnt;
    // Serial.println(digitalRead(16));
    // delay(1000);
    // Arm_pickup(&servoA, &servoB, &servoC);
    // delay(1000);
    // Arm_drop(&servoA, &servoB, &servoC);
}
