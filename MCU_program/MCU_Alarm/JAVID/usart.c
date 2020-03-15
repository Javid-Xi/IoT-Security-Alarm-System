#include "sys.h"
#include "usart.h"	
#include "stdio.h"

dataPoint_t currentDataPoint;
//u8 Voice_work=Voice_Free;
//////////////////////////////////////////////////////////////////

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch;      
	return ch;
}
#endif 


 

//接收状态
  
void uart_1_init(u32 bound)
	{
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
		
		//USART1_TX   GPIOA.9
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
		 
		//USART1_RX	  GPIOA.10初始化
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

		//Usart1 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		
		 //USART 初始化设置

		USART_InitStructure.USART_BaudRate = bound;//串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

		USART_Init(USART1, &USART_InitStructure); //初始化串口1
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
		USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void uart_2_init(u32 bound)
	{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //使能USART2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
  
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART1_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3 
				
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2

	}

void uart_3_init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //使能USART3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
  
	//USART3_TX   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11 

   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_Cmd(USART3, ENABLE);                    //使能串口3
}
	
void USART1_IRQHandler(void)  //串口1中断服务程序
	{
	u8 Zigbee_data=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
		{
		Zigbee_data=USART_ReceiveData(USART1);//读取接收到的数据
		USART1_data_handle(Zigbee_data);
		}   		 
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  } 
	

void USART1_data_handle(u8 data)//串口1接收数据处理函数
{
	if((data&0xF0)==0x80)
	{	
		if((data&0x0F)==0x00)
		{
			currentDataPoint.valueAlarm=0;
		//报警关
		}
		else if((data&0x0F)==0x01)
		{
			currentDataPoint.valueAlarm=1;
		//报警模式1
		}
		else if((data&0x0F)==0x02)
		{
			currentDataPoint.valueAlarm=2;
		//报警模式2
		}
		else if((data&0x0F)==0x03)
		{
			currentDataPoint.valueAlarm=3;
		//报警模式3
		}
	}
	else if((data&0xF0)==0x90)
	{
		if((data&0x0F)==0x00)
		{
			currentDataPoint.valueMODEL=0;
		//模式0
		}
		else if((data&0x0F)==0x01)
		{
			currentDataPoint.valueMODEL=1;
		//模式1
		}
	}
	else if((data&0xF0)==0x10)//无线门磁1
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMENCI_1=1;
		//门磁1 on
		}
		else currentDataPoint.valueMENCI_1=0;//menci off
	}
	else if((data&0xF0)==0x20)//无线门磁2
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMENCI_2 =1;
		//门磁2 on
		}
		else currentDataPoint.valueMENCI_2 =0;//menci off
	}
	else if((data&0xF0)==0x30)//烟雾
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMQ_2=1;
		//yanwu on
		}
		else currentDataPoint.valueMQ_2=0;//yanwu off
	}
	else if((data&0xF0)==0x40)//火焰
	{
		if(data&0x0F)
		{
			currentDataPoint.valueflame_1=1;
		//huoyan on
		}
		else currentDataPoint.valueflame_1=0;//huoyan off
	}
}

/************************************************************************
功能描述： 串口发送字符串数据
入口参数： 	*DAT：字符串指针
返 回 值： none
其他说明： API 供外部使用，直观！
**************************************************************************/
void Send_stringdata(uint8_t *DAT,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET) 	;
	USART_SendData(USART2,*DAT++);
	USART_ClearFlag(USART2,USART_FLAG_TXE);
	}	
}
