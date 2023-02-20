#ifndef _ENCOUNTER_H_
#define _ENCOUNTER_H_

struct Encounter
{
    uint8_t pinA;
    uint8_t pinB;
    int16_t cnt;
    void (*intFunc)(void);
};

void Encounter_setup(Encounter *encounter);
void Encounter_interrupt(Encounter *encounter);

#endif
