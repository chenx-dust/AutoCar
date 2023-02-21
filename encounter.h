#ifndef _ENCOUNTER_H_
#define _ENCOUNTER_H_

typedef struct
{
    uint8_t pinA;
    uint8_t pinB;
    int16_t cnt;
    void (*intFunc)(void);
} Encounter;

void Encounter_setup(Encounter *encounter);
void Encounter_interrupt(Encounter *encounter);
int32_t Encounter_count(Encounter *encounter);

#endif
