#include "motor.h"

CarMotor carMotor;

void Eint_l() { Encounter_interrupt(&carMotor.left.encounter); }
void Eint_r() { Encounter_interrupt(&carMotor.right.encounter); }

// carMotor.left.encounter = Encounter {2, 3, 0, Eint_l};

void setup()
{
	
}

void loop()
{
	
}
