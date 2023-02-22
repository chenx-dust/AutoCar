#ifndef _ARM_H_
#define _ARM_H_

#include <Servo.h>

void Arm_setup(Servo *servoA, Servo *servoB, Servo *servoC);
void Arm_pickup(Servo *servoA, Servo *servoB, Servo *servoC);
void Arm_drop(Servo *servoA, Servo *servoB, Servo *servoC);

#endif
