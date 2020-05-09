#ifndef __GPIO_H
#define __GPIO_H	 
#include "sys.h"

#define Flame_1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define MQ_2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)

#define MQ_2_OFF 0x30
#define MQ_2_ON 0x31

#define Flame_1_OFF 0x40
#define Flame_1_ON 0x41

void INPUT_Init(void);//IO≥ı ºªØ
void MQ_2_Send(void);
void Flame_1_Send(void);
void LED_Update(void);

#endif
