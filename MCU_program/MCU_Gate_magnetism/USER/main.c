/**
************************************************************
* @file         main.c
* @brief        Magnetic Control Function of Wireless Gate
* @author       Javid Xi
* @date         2019-02-22
* @version      1.0
* @copyright    LElink
* 
* @note         MENCI_1√‹‘ø£∫0001
								MENCI_2√‹‘ø£∫0010
*
***********************************************************/


#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "menci.h"
#include "usart.h"	  

int main()
 {
	delay_init();
	MENCI_Init();
	LED_Init();
	uart_init(115200);
  while(1)
	{
		MENCI_Send();
		LED_Update();
		delay_ms(100);
	}
}

