#include "encoder.h"

void Encoder_setup(Encoder *encoder)
{
    pinMode(encoder->pinA, INPUT);
    pinMode(encoder->pinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder->pinA), encoder->intFunc, CHANGE);
}

void Encoder_interrupt(Encoder *encoder)
{
    if (digitalRead(encoder->pinA) == LOW)
        if (digitalRead(encoder->pinB) == LOW)
            encoder->cnt--;
        else
            encoder->cnt++;
    else
        if (digitalRead(encoder->pinB) == LOW)
            encoder->cnt++;
        else
            encoder->cnt--;
}

int32_t Encoder_count(Encoder *encoder)
{
    int32_t cnt = encoder->cnt;
    encoder->cnt = 0;
    return cnt;
}
