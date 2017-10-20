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
static void AppObjCreate (void);
static void AppMsgCreate (void);

static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

static EventGroupHandle_t test_group = NULL;/*创建事件标志组 */ 

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
  test_group = xEventGroupCreate();/*创建事件组*/
//  AppObjCreate ();/*软件定时器组*/
  AppMsgCreate();
  /* 启动调度，开始执行任务 */
  vTaskStartScheduler();
   /*
     系统不会运行到这里，
     如果运行到这里，有可能是堆空间不够使用导致
     #define configTOTAL_HEAP_SIZE        ( ( size_t ) ( 17 * 1024 ) )
   */
   while(1);		
}

/*
*********************************************************************************************************
* 函 数 名: AppObjCreate
* 功能说明: 创建任务通信机制
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
QueueHandle_t xQueue1;
QueueHandle_t xQueue2;
static void AppMsgCreate (void)
{
    /* 创建 10 个 uint8_t 型消息队列 */
    xQueue1 = xQueueCreate(1, sizeof(TpInt32));
    if( xQueue1 == 0 )
    {
    /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
    
    /* 创建 10 个存储指针变量的消息队列，由于 CM3/CM4 内核是 32 位机，一个指针变量占用 4 个字节 */
    xQueue2 = xQueueCreate(10, sizeof(struct Msg *));
    if( xQueue2 == 0 )
    {
    /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
}

TpInt32 ucCount = 0;
void TimerCallback(xTimerHandle pxTimer)
{
  
ucCount++;
  
//  
//    if(xQueueSend(xQueue1,(void *) &ucCount,0) == pdPASS )
//    {
////      len = snprintf((char*)buff,100,"\r\n******************定时器函数来了，哈哈哈哈******************\r\n \r\n=======消息队列发送成功=====\r\n");
////    
////      UsartPushSendBuf(out_usart,(unsigned char*)buff,len);	
////      UsartSend(out_usart);
//    }
//    else
//    {
//       ucCount = 0;
//    }
}

static TimerHandle_t xTimers = NULL;
static void AppObjCreate (void)
{
  const TickType_t xTimerPer = 1;
    /*
    创建定时器，如果在 RTOS 调度开始前初始化定时器，那么系统启动后才会执行。
    */
//    xTimers = xTimerCreate("Timer", /* 定时器名字 */
//                           1, /* 定时器周期,单位时钟节拍 */
//                           pdTRUE, /* 周期性 */
//                          (void *) 1, /* 定时器 ID */
//                          TimerCallback); /* 定时器回调函数 */
//    if(xTimers == NULL)
//    {
//      /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
//    }
//    else
//    {
//      /* 启动定时器，系统启动后才开始工作 */
//      if(xTimerStart(xTimers, 1) != pdPASS)
//      {
//      /* 定时器还没有进入激活状态 */
//      }
//    }
}


#define one_bit   (1<<1)
#define two_bit   (1<<2)
TpInt32 oo;
char send_buff2[100];
static void vTaskTaskUserIF(void *pvParameters)
{
  int len2 = 0;
  static int count = 0;
  EventBits_t test_bit;
  int i,j,k;
    while(1)
    {
      memset(send_buff2, 0, 100);	//清空内存

      test_bit = xEventGroupSetBits(test_group, one_bit);

      
      

        count++;
        len2 += snprintf((char*)send_buff2,100,"TaskIF : %d\r\n",count); 
   
        
        if(len2 > 0)
        {
          UsartPushSendBuf(out_usart,(unsigned char*)send_buff2,len2);
          UsartSend(out_usart); 
        }
          
      
       vTaskDelay(1000);
    }
      
}

TpInt32 rev;
TpInt32 xx;
TpInt32 rev2[1000];
static void vTaskLED(void *pvParameters)
{
  int len2 = 0;
  static int count = 0;
  
  int i,j,k;
  
  BaseType_t xResult;
  
    while(1)
    {   

//      xResult = xQueueReceive(xQueue1, /* 消息队列句柄 */
//                             &rev, /* 存储接收到的数据到变量 ucQueueMsgValue 中 */
//                             portMAX_DELAY);/* 设置阻塞时间 */
//      
//      rev2[count] = rev;
//     
      for(i = 99999;i>0;i--)
      {
        count++;
        len = snprintf((char*)buff,100,"vTaskLED : %d\r\n",count);
        
        UsartPushSendBuf(out_usart,(unsigned char*)buff,len);	
        UsartSend(out_usart);
        
        for(j=999;j>0;j--)
          for(k=999;k>0;k--);
      }
    }
}

char send_buff[500];
char TaskList_buff[200];
char TaskRunTimebuff[200];
TpInt32 msg;
static void vTaskMsgPro(void *pvParameters)
{
    int len2 = 0;
  
    while(1)
    {
//      vTaskList((char *)TaskList_buff);  
//      vTaskGetRunTimeStats((char *)TaskRunTimebuff);      
//    
//      memset(send_buff, 0, 500);	//清空内存
//      len2 = snprintf((char*)send_buff,500,
//"\r\n=================================================\r\ntask         status   priority   no_use_Stack_Size    ID \r\n%s\r\n\r\ntask_name       work_time         useful_rate\r\n%s\r\n",
//      TaskList_buff,TaskRunTimebuff); 

//      UsartPushSendBuf(out_usart,(unsigned char*)send_buff,len2);	
//      UsartSend(out_usart);
//      msg++;
      vTaskDelay(1000);
    }
}
int test;
static void vTaskStart(void *pvParameters)
{
    EventBits_t test_bit;
  
    while(1)
    {
      test++;
       test_bit = xEventGroupWaitBits(test_group,      /* 事件标志组句柄 */
                                      one_bit|two_bit,            /* 等待 bit0 和 bit1 被设置 */
                                      pdTRUE,            /* 退出前 bit0 和 bit1 被清除，这里是 bit0 和 bit1都被设置才表示“退出” */
                                      pdTRUE,         /* 设置为 pdTRUE 表示等待 bit1 和 bit0 都被设置*/
                                      portMAX_DELAY);
      
      if(test_bit & one_bit)
      {
          len = snprintf((char*)buff,100," \r\n标志位1 被置1了了了了了，然后清0了 \r\n");
      
          UsartPushSendBuf(out_usart,(unsigned char*)buff,len);	
          UsartSend(out_usart);
      }
    }
}

static void AppTaskCreate (void)
{
    xTaskCreate( vTaskTaskUserIF,   /* 任务函数 */
                 "vTaskUserIF",     /* 任务名    */
                 800,               /* 任务栈大小，单位：4字节 */
                 NULL,              /* 任务参数  */
                 2,                  /* 任务优先级*/
                 &xHandleTaskUserIF );  /* 任务句柄  */
    
    
     xTaskCreate( vTaskLED,           /* 任务函数 */
                 "vTaskLED",         /* 任务名    */
                 800,                 /* 任务栈大小，单位：4字节 */
                 NULL,               /* 任务参数  */
                 2,                  /* 任务优先级*/
                 &xHandleTaskLED ); /* 任务句柄  */
    
     xTaskCreate( vTaskMsgPro,            /* 任务函数 */
                 "vTaskMsgPro",          /* 任务名    */
                 500,                    /* 任务栈大小，单位：4字节 */
                 NULL,                     /* 任务参数  */
                 3,                       /* 任务优先级*/
                 &xHandleTaskMsgPro );  /* 任务句柄  */
    
    
     xTaskCreate( vTaskStart,             /* 任务函数 */
                 "vTaskStart",            /* 任务名    */
                 100,                     /* 任务栈大小，单位：4字节 */
                 NULL,                    /* 任务参数  */
                 4,                       /* 任务优先级*/
                 &xHandleTaskStart );     /* 任务句柄  */
}
