/**
************************************************************
* @file         hal_usart.c
* @brief        串口3数据处理

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/
#include "hal_usart.h"

dataPoint_t Zigbee_dataPoint_t;
extern UART_HandleTypeDef huart3;

/*****************串口数据处理******************/ 
void Zigbee_data_handle(uint8_t Zigbee_data)
{
    if((Zigbee_data & 0xF0) == 0x10) //无线门磁1
    {

        Zigbee_dataPoint_t.valueMENCI_1 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MENCI_1 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x20) //无线门磁2
    {
        Zigbee_dataPoint_t.valueMENCI_2 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MENCI_2 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x30) //烟雾
    {
        Zigbee_dataPoint_t.valueMQ_2 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MQ_2 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x40) //火焰
    {
        Zigbee_dataPoint_t.valueflame_1 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice Flame_1 data \n");
    }

}

/*****************串口数据发送******************/ 
void Zigbee_send(uint8_t Zigbee_Alarm)
{
    HAL_UART_Transmit(&huart3, &Zigbee_Alarm, 1, 10);
}



