/**
************************************************************
* @file         hal_key.c
* @brief        串口3数据解析

* @author       Javid
* @date         2019-02-20
* @version      V03010101
* @copyright    Javid
* 
* @note        
*
***********************************************************/
#ifndef _HAL_USART_H
#define _HAL_USART_H
#include <stdio.h>
#include <string.h>
#include "hal_key.h"
#include "gizwits_product.h"
#include "common.h"
#include "delay.h"

#define Alarm_OFF          0x80
#define Alarm_model_1      0x81
#define Alarm_model_2      0x82
#define Alarm_model_3      0x83
#define Manual_alarm_mode        0x90
#define Automatic_alarm_mode     0x91

void Zigbee_data_handle(uint8_t Zigbee_data);
void Zigbee_send(uint8_t Zigbee_Alarm);

#endif



