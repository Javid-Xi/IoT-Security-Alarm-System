/**
************************************************************
* @file         main.c
* @brief        Control Function of Smoke Flame Alarm
* @author       Javid Xi
* @date         2019-02-22
* @version      1.0
* @copyright    LElink
* 
* @note         Flame_1 KEY£º0100
								MQ_2 KEY£º0011
*
***********************************************************/

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "gpio.h"
#include "usart.h"	  

int main()
{
	delay_init();
	INPUT_Init();
	LED_Init();
	uart_init(115200);
  while(1)
	{
		MQ_2_Send();
		delay_ms(100);
		Flame_1_Send();
		LED_Update();
		delay_ms(500);
	}
}
