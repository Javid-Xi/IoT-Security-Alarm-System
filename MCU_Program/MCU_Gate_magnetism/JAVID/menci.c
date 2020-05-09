/**
************************************************************
* @file         menci.c
* @brief        无线门磁数据处理

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/
#include "stm32f10x.h"
#include "menci.h"
#include "delay.h"
#include "led.h"

/*****************IO初始化函数******************/
void MENCI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4; //门磁
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
}

/*****************无线门磁数据处理函数******************/
void MENCI_Send(void)
{
    static u8 menci_up = 1, menci_down = 1;
    if(menci_up && MENCI)
    {
        menci_up = 0; //标记这次门磁已经分开
        menci_down = 1;
        USART_SendData(USART1, MENCI_ON);
    }
    else if(menci_down && MENCI == 0)
    {
        menci_down = 0; //标记这次门磁已经吸合
        menci_up = 1;
        USART_SendData(USART1, MENCI_OFF); //已吸合
    }
}

/*****************LED状态更新函数******************/
void LED_Update(void)
{
    if(MENCI)//门磁分开
    {
        LED_safe = OFF;
        LED_danger = ON;
    }
    else
    {
        LED_safe = ON;
        LED_danger = OFF;
    }
}




