#ifndef _ENCODER_H_
#define _ENCODER_H_

typedef struct
{
    uint8_t pinA;
    uint8_t pinB;
    int16_t cnt;
    void (*intFunc)(void);
} Encoder;

void Encoder_setup(Encoder *encoder);
void Encoder_interrupt(Encoder *encoder);
int32_t Encoder_count(Encoder *encoder);

#endif
