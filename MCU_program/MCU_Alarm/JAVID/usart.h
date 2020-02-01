#ifndef __USART_H
#define __USART_H
#include "sys.h" 
#include <stdbool.h> 
#include "stdio.h"

#define Voice_Free 0x4F

/** User Area Device State Structure */
typedef struct {
  bool valueMODEL;
  uint8_t valueAlarm;
  bool valueMQ_2;
  bool valueMENCI_1;
  bool valueflame_1;
  bool valueMENCI_2;
} dataPoint_t;

void uart_1_init(u32 bound);
void uart_2_init(u32 bound);
void USART1_data_handle(u8 data);
void Send_stringdata(uint8_t *DAT,uint8_t len);

#endif


