/**
 * @file        main.c
 * @brief
 */

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "config.h"
#include "gnss.h"
#include "RM3100.h"
#include "stm32f4xx_it.h"
//#include "command.h"
#include "SPI1.h"
#include "Decode_Ublox.h"
#include "flash.h"
#include "USART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "usr_FreeRTOS.h"

#define  ADDR_APP_DEVIATION    ((TpUint32)0x10000)


static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);


static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
char buff[100];
char len;

Usart* out_usart;
TpInt32 main(TpVoid)
{
	/* Application Programme Deviation */
 //SCB->VTOR = FLASH_BASE|ADDR_APP_DEVIATION;

	/* Tim,Usart.. config*/ 
  __set_PRIMASK(1);
  /* 创建任务*/
  AppTaskCreate();
    
  HardWareInit(); 
  
  out_usart = GetUsartAddress(USART_2);  
  
  /* 启动调度，开始执行任务 */
  vTaskStartScheduler();
   /*
     系统不会运行到这里，
     如果运行到这里，有可能是堆空间不够使用导致
     #define configTOTAL_HEAP_SIZE        ( ( size_t ) ( 17 * 1024 ) )
   */
   while(1);		
}

char send_buff2[100];
static void vTaskTaskUserIF(void *pvParameters)
{
  int len2 = 0;
    while(1)
    {
      memset(send_buff2, 0, 100);	//清空内存
     
      if(xHandleTaskLED != NULL)
      {
       vTaskDelete(xHandleTaskLED);
        xHandleTaskLED = NULL;
       
      len2 = snprintf((char*)send_buff2,100,
"\r\n\r\n||||||==删除任务啦==|||||||\r\n\r\n"); 

      UsartPushSendBuf(out_usart,(unsigned char*)send_buff2,len2);	       
      }
      else
      {
             xTaskCreate( vTaskLED,           /* 任务函数 */
                 "vTaskLED",         /* 任务名    */
                 500,                 /* 任务栈大小，单位：4字节 */
                 NULL,               /* 任务参数  */
                 1,                  /* 任务优先级*/
                 &xHandleTaskLED ); /* 任务句柄  */
       
          len2 = snprintf((char*)send_buff2,100,"\r\n\r\n||||||==创建任务啦==|||||||\r\n\r\n"); 
        
          vTaskSuspend(0);
        
        len2 += snprintf((char*)send_buff2,100,"\r\n\r\n||||||==挂起（删除，创建任务）==|||||||\r\n\r\n"); 

          UsartPushSendBuf(out_usart,(unsigned char*)send_buff2,len2);	
      }
      
         /* 任务所在位置 */
         vTaskDelay(2000);
    }
}

static void vTaskLED(void *pvParameters)
{
  static int count = 0;
    while(1)
    {       
      len = snprintf((char*)buff,100,"test for vTaskLED work number : %d\r\n",count);
      
      UsartPushSendBuf(out_usart,(unsigned char*)buff,len);	
    //  UsartSend(out_usart);
      count++;

      vTaskDelay(100);
    }
}

char send_buff[500];
char TaskList_buff[200];
char TaskRunTimebuff[200];

static void vTaskMsgPro(void *pvParameters)
{
    int len2 = 0;
  
    while(1)
    {
      vTaskList((char *)TaskList_buff);  
      vTaskGetRunTimeStats((char *)TaskRunTimebuff);      
    
      memset(send_buff, 0, 500);	//清空内存
      len2 = snprintf((char*)send_buff,500,
"\r\n=================================================\r\ntask         status   priority   no_use_Stack_Size    ID \r\n%s\r\n\r\ntask_name       work_time         useful_rate\r\n%s\r\n",
      TaskList_buff,TaskRunTimebuff); 

      UsartPushSendBuf(out_usart,(unsigned char*)send_buff,len2);	
      UsartSend(out_usart);
      
      vTaskDelay(1000);
    }
}

static void vTaskStart(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(400);
    }
}

static void AppTaskCreate (void)
{
    xTaskCreate( vTaskTaskUserIF,   /* 任务函数 */
                 "vTaskUserIF",     /* 任务名    */
                 800,               /* 任务栈大小，单位：4字节 */
                 NULL,              /* 任务参数  */
                 1,                  /* 任务优先级*/
                 &xHandleTaskUserIF );  /* 任务句柄  */
    
    
     xTaskCreate( vTaskLED,           /* 任务函数 */
                 "vTaskLED",         /* 任务名    */
                 500,                 /* 任务栈大小，单位：4字节 */
                 NULL,               /* 任务参数  */
                 1,                  /* 任务优先级*/
                 &xHandleTaskLED ); /* 任务句柄  */
    
     xTaskCreate( vTaskMsgPro,            /* 任务函数 */
                 "vTaskMsgPro",          /* 任务名    */
                 500,                    /* 任务栈大小，单位：4字节 */
                 NULL,                     /* 任务参数  */
                 1,                       /* 任务优先级*/
                 &xHandleTaskMsgPro );  /* 任务句柄  */
    
    
     xTaskCreate( vTaskStart,             /* 任务函数 */
                 "vTaskStart",            /* 任务名    */
                 100,                     /* 任务栈大小，单位：4字节 */
                 NULL,                    /* 任务参数  */
                 1,                       /* 任务优先级*/
                 &xHandleTaskStart );     /* 任务句柄  */
}
