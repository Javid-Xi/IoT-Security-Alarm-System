#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"


//外部中断服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

		//GPIOA.3 中断线以及中断初始化配置   下降沿触发 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY3所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}



////中断3服务函数
//void EXTI3_IRQHandler(void)
//{
//		EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
//	delay_ms(10);//消抖
//	if(KEY3==0)	 //按键KEY3
//	{
//		DJ2_ENA=0;
//		DJ1_ENA=0;
//		JDQ0=1;
//	}		 

//}
// 
