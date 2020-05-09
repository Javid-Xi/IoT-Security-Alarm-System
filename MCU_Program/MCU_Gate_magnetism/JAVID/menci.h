#ifndef __MENCI_H
#define __MENCI_H	 
#include "sys.h"


#define MENCI  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//∂¡»°√≈¥≈

#define MENCI_1	0
#define MENCI_2 1

#if MENCI_1
#define MENCI_OFF 0x10
#define MENCI_ON 0x11

#elif MENCI_2
#define MENCI_OFF 0x20
#define MENCI_ON 0x21

#endif


void MENCI_Init(void);
void MENCI_Send(void);
void LED_Update(void);

			    
#endif
