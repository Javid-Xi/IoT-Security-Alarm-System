#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 



//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键2 
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键3 模式一
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键4 
#define KEY5  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//读取按键5 模式二
#define KEY6  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键6 模式后归位



#define KEY0_PRES 1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define KEY3_PRES 4	//KEY3按下
#define KEY4_PRES	5	//KEY4按下
#define KEY5_PRES	6	//KEY5按下
#define KEY6_PRES 7	//KEY6按下


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
