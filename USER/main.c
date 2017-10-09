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
  /* ��������*/
  AppTaskCreate();
    
  HardWareInit(); 
  
  out_usart = GetUsartAddress(USART_2);  
  
  /* �������ȣ���ʼִ������ */
  vTaskStartScheduler();
   /*
     ϵͳ�������е����
     ������е�����п����Ƕѿռ䲻��ʹ�õ���
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
      memset(send_buff2, 0, 100);	//����ڴ�
     
      if(xHandleTaskLED != NULL)
      {
       vTaskDelete(xHandleTaskLED);
        xHandleTaskLED = NULL;
       
      len2 = snprintf((char*)send_buff2,100,
"\r\n\r\n||||||==ɾ��������==|||||||\r\n\r\n"); 

      UsartPushSendBuf(out_usart,(unsigned char*)send_buff2,len2);	       
      }
      else
      {
             xTaskCreate( vTaskLED,           /* ������ */
                 "vTaskLED",         /* ������    */
                 500,                 /* ����ջ��С����λ��4�ֽ� */
                 NULL,               /* �������  */
                 1,                  /* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
       
          len2 = snprintf((char*)send_buff2,100,"\r\n\r\n||||||==����������==|||||||\r\n\r\n"); 
        
          vTaskSuspend(0);
        
        len2 += snprintf((char*)send_buff2,100,"\r\n\r\n||||||==����ɾ������������==|||||||\r\n\r\n"); 

          UsartPushSendBuf(out_usart,(unsigned char*)send_buff2,len2);	
      }
      
         /* ��������λ�� */
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
    
      memset(send_buff, 0, 500);	//����ڴ�
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
    xTaskCreate( vTaskTaskUserIF,   /* ������ */
                 "vTaskUserIF",     /* ������    */
                 800,               /* ����ջ��С����λ��4�ֽ� */
                 NULL,              /* �������  */
                 1,                  /* �������ȼ�*/
                 &xHandleTaskUserIF );  /* ������  */
    
    
     xTaskCreate( vTaskLED,           /* ������ */
                 "vTaskLED",         /* ������    */
                 500,                 /* ����ջ��С����λ��4�ֽ� */
                 NULL,               /* �������  */
                 1,                  /* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
    
     xTaskCreate( vTaskMsgPro,            /* ������ */
                 "vTaskMsgPro",          /* ������    */
                 500,                    /* ����ջ��С����λ��4�ֽ� */
                 NULL,                     /* �������  */
                 1,                       /* �������ȼ�*/
                 &xHandleTaskMsgPro );  /* ������  */
    
    
     xTaskCreate( vTaskStart,             /* ������ */
                 "vTaskStart",            /* ������    */
                 100,                     /* ����ջ��С����λ��4�ֽ� */
                 NULL,                    /* �������  */
                 1,                       /* �������ȼ�*/
                 &xHandleTaskStart );     /* ������  */
}
