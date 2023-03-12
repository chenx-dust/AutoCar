#ifndef _SONAR_H_
#define _SONAR_H_

typedef struct
{
    uint8_t pin_trig;
    uint8_t pin_echo;
    volatile bool *detected_flag;
} Sonar;

void Sonar_setup(Sonar *sonar);
void Sonar_detect(Sonar *sonar);

#endif
