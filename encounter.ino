#include "encounter.h"

void Encounter_setup(Encounter *encounter)
{
    pinMode(encounter->pinA, INPUT);
    pinMode(encounter->pinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encounter->pinA), encounter->intFunc, CHANGE);
}

void Encounter_interrupt(Encounter *encounter)
{
    if (digitalRead(encounter->pinA) == LOW)
        if (digitalRead(encounter->pinB) == LOW)
            encounter->cnt--;
        else
            encounter->cnt++;
    else
        if (digitalRead(encounter->pinB) == LOW)
            encounter->cnt++;
        else
            encounter->cnt--;
}

int32_t Encounter_cnt(Encounter *encounter)
{
    int32_t cnt = encounter->cnt;
    encounter->cnt = 0;
    return cnt;
}
