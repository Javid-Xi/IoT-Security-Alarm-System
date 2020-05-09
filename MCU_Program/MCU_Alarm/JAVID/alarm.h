#ifndef __ALARM_H
#define __ALARM_H
#include "sys.h"

#define LED0 PBout(0)
#define LED1 PBout(1)
#define Alarm PBout(7)

void Alarm_Init(void);
void LED_model_1(void);
void LED_model_2(void);
void Beep_Alarm_ON(void);
void Beep_Alarm_OFF(void);
void Beep_Initialization(void);

#endif

