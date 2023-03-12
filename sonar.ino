#include "sonar.h"
#include "const.h"

double last_dis[SONAR_HISTORY];
size_t dis_pos = 0;
void push_dis(double dis)
{
    if (dis == 0.0)
        return;
    last_dis[dis_pos++] = dis;
    if (dis_pos >= SONAR_HISTORY)
        dis_pos = 0;
}

double average_dis()
{
    double sum = 0;
    for (size_t i = 0; i < SONAR_HISTORY; ++i)
        sum += last_dis[i];
    return sum / SONAR_HISTORY;
}

void Sonar_setup(Sonar *sonar)
{
    pinMode(sonar->pin_trig, OUTPUT);
    digitalWrite(sonar->pin_trig, LOW);
    pinMode(sonar->pin_echo, INPUT);

    for (size_t i = 0; i < SONAR_HISTORY; ++i)
        last_dis[i] = SONAR_INF;
}

void Sonar_detect(Sonar *sonar)
{
    if (*sonar->detected_flag)
        return;
    // Serial.println("Sonar_detect");
    double dis;
    digitalWrite(sonar->pin_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(sonar->pin_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(sonar->pin_trig, LOW);
    dis = pulseIn(sonar->pin_echo, HIGH) / 58.0;
    push_dis(dis);
    // Serial.println(dis);

    if (average_dis() <= SONAR_THRES)
        *sonar->detected_flag = true;
}
