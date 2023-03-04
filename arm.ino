#include "arm.h"
#include "const.h"

void Arm_setup(Servo *servoA, Servo *servoB, Servo *servoC)
{
    servoA->attach(SERVO_A_PIN);
    servoB->attach(SERVO_B_PIN);
    servoC->attach(SERVO_C_PIN);
    servoA->write(SERVO_A_BASE);
    servoB->write(SERVO_B_BASE);
    servoC->write(SERVO_C_BASE);
}

void Arm_pickup(Servo *servoA, Servo *servoB, Servo *servoC)
{
    servoA->write(SERVO_A_BASE);
    servoB->write(SERVO_B_BASE);
    servoC->write(SERVO_C_BASE);
    delay(200);
    servoC->write(SERVO_C_BASE + SERVO_C_PICK);
    delay(400);
    servoA->write(SERVO_A_BASE + SERVO_A_UP);
}

void Arm_drop(Servo *servoA, Servo *servoB, Servo *servoC)
{
    servoA->write(SERVO_A_BASE);
    servoB->write(SERVO_B_BASE);
    servoC->write(SERVO_C_BASE + SERVO_C_PICK);
    delay(400);
    servoC->write(SERVO_C_BASE);
}
