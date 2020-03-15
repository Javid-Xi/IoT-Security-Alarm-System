/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值?|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "hal_key.h"
#include "gizwits_product.h"
#include "common.h"
#include "hal_temp_hum.h"
#include "delay.h"
#include "hal_usart.h"

static uint32_t timerMsCount;
uint8_t aRxBuffer;
uint8_t Zigbee_data=0;

/** User area the current device state structure*/
dataPoint_t currentDataPoint;
extern keysTypedef_t keys;
extern dataPoint_t Zigbee_dataPoint_t;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_MODEL:
        currentDataPoint.valueMODEL = dataPointPtr->valueMODEL;
        GIZWITS_LOG("Evt: EVENT_MODEL %d \n", currentDataPoint.valueMODEL);
        if(0x01 == currentDataPoint.valueMODEL)
        {
          //user handle
					Zigbee_send(Automatic_alarm_mode);
					GIZWITS_LOG("Evt: Open automatic alarm mode \n");
        }
        else
        {
          //user handle    
					Zigbee_send(Manual_alarm_mode);
					GIZWITS_LOG("Evt: Open manual alarm mode \n");
        }
        break;

      case EVENT_Alarm:
        currentDataPoint.valueAlarm = dataPointPtr->valueAlarm;
        GIZWITS_LOG("Evt: EVENT_Alarm %d\n", currentDataPoint.valueAlarm);
        switch(currentDataPoint.valueAlarm)
        {
          case Alarm_VALUE0:
            //user handle
					Zigbee_send(Alarm_OFF);
					GIZWITS_LOG("Evt: Alarm OFF \n");
            break;
          case Alarm_VALUE1:
            //user handle
					Zigbee_send(Alarm_model_1);
					GIZWITS_LOG("Evt: Alarm model 1 \n");
            break;
          case Alarm_VALUE2:
            //user handle
					Zigbee_send(Alarm_model_2);
					GIZWITS_LOG("Evt: Alarm model 2 \n");
            break;
          case Alarm_VALUE3:
            //user handle
					Zigbee_send(Alarm_model_3);
					GIZWITS_LOG("Evt: Alarm model 3 \n");
            break;
          default:
            break;
        }
        break;



      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
	  uint8_t ret = 0;
    static uint32_t thLastTimer_1 = 0 , thLastTimer_2 = 0;
	
				//门磁烟雾火焰传感器数据获取
	    if((gizGetTimerCount() - thLastTimer_1) > 1000)      //上报间隔1S
    {
				currentDataPoint.valueMQ_2 =Zigbee_dataPoint_t.valueMQ_2;
				currentDataPoint.valueMENCI_1 =Zigbee_dataPoint_t.valueMENCI_1;
				currentDataPoint.valueflame_1 =Zigbee_dataPoint_t.valueflame_1;
				currentDataPoint.valueMENCI_2 =Zigbee_dataPoint_t.valueMENCI_2;
        thLastTimer_1 = gizGetTimerCount();
    }
        //温湿度传感器数据获取
    if((gizGetTimerCount() - thLastTimer_2) > 2000)      //上报间隔2S
    {	
        ret = dht11Read((uint8_t *)&currentDataPoint.valueTemperature, 
												(uint8_t *)&currentDataPoint.valueHumidity);
        if(ret != 0)
        {
            printf("Failed to read DHT11 [%d] \n", ret);
        }

        thLastTimer_2 = gizGetTimerCount();
    }
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    delay_init(72);     // 延时 初始化
	  dht11Init();        // 温湿度初始化
}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
}

/**@} */

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim2)
	{
			keyHandle((keysTypedef_t *)&keys);
			gizTimerMs();
	}
}

/**
* @brief Timer TIM3 init function

* @param none
* @return none
*/
void timerInit(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  This function handles USART IDLE interrupt.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)  
{  
		if(UartHandle->Instance == USART2)  
		{  
				gizPutData((uint8_t *)&aRxBuffer, 1);

				HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
		}  
		else if(UartHandle->Instance == USART3)  
		{  
			GIZWITS_LOG("recevice zigbee data \n ");
			Zigbee_data_handle(Zigbee_data);
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&Zigbee_data, 1);//开启下一次接收中断 
		}
}  

/**
* @brief USART init function

* Serial communication between WiFi modules and device MCU
* @param none
* @return none
*/
void uartInit(void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&Zigbee_data, 1);//开启下一次接收中断  
}

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
		uint8_t crc[1] = {0x55};
    uint32_t i = 0;
	
    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)&buf[i], 1);
				while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission

        if(i >=2 && buf[i] == 0xFF)
        {
						HAL_UART_Transmit_IT(&huart2, (uint8_t *)&crc, 1);
						while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif
		
		return len;
}  
