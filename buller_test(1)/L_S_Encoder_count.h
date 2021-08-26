#ifndef L_S_Encoder_count_H_
#define L_S_Encoder_count_H_
#include "Arduino.h"

#include "Timer1.h"

#define FORWARD  0x09
#define STOP     0

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
}
#endif

void Motor_mode(int da);
void Motor_Control();
void Encoder_count();
void Timer1_ISR();

#endif
