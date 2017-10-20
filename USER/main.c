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

static EventGroupHandle_t test_group = NULL;/*�����¼���־�� */ 

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
  test_group = xEventGroupCreate();/*�����¼���*/
//  AppObjCreate ();/*�����ʱ����*/
  AppMsgCreate();
  /* �������ȣ���ʼִ������ */
  vTaskStartScheduler();
   /*
     ϵͳ�������е����
     ������е�����п����Ƕѿռ䲻��ʹ�õ���
     #define configTOTAL_HEAP_SIZE        ( ( size_t ) ( 17 * 1024 ) )
   */
   while(1);		
}

/*
*********************************************************************************************************
* �� �� ��: AppObjCreate
* ����˵��: ��������ͨ�Ż���
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
QueueHandle_t xQueue1;
QueueHandle_t xQueue2;
static void AppMsgCreate (void)
{
    /* ���� 10 �� uint8_t ����Ϣ���� */
    xQueue1 = xQueueCreate(1, sizeof(TpInt32));
    if( xQueue1 == 0 )
    {
    /* û�д����ɹ����û�������������봴��ʧ�ܵĴ������ */
    }
    
    /* ���� 10 ���洢ָ���������Ϣ���У����� CM3/CM4 �ں��� 32 λ����һ��ָ�����ռ�� 4 ���ֽ� */
    xQueue2 = xQueueCreate(10, sizeof(struct Msg *));
    if( xQueue2 == 0 )
    {
    /* û�д����ɹ����û�������������봴��ʧ�ܵĴ������ */
    }
}

TpInt32 ucCount = 0;
void TimerCallback(xTimerHandle pxTimer)
{
  
ucCount++;
  
//  
//    if(xQueueSend(xQueue1,(void *) &ucCount,0) == pdPASS )
//    {
////      len = snprintf((char*)buff,100,"\r\n******************��ʱ���������ˣ���������******************\r\n \r\n=======��Ϣ���з��ͳɹ�=====\r\n");
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
    ������ʱ��������� RTOS ���ȿ�ʼǰ��ʼ����ʱ������ôϵͳ������Ż�ִ�С�
    */
//    xTimers = xTimerCreate("Timer", /* ��ʱ������ */
//                           1, /* ��ʱ������,��λʱ�ӽ��� */
//                           pdTRUE, /* ������ */
//                          (void *) 1, /* ��ʱ�� ID */
//                          TimerCallback); /* ��ʱ���ص����� */
//    if(xTimers == NULL)
//    {
//      /* û�д����ɹ����û�������������봴��ʧ�ܵĴ������ */
//    }
//    else
//    {
//      /* ������ʱ����ϵͳ������ſ�ʼ���� */
//      if(xTimerStart(xTimers, 1) != pdPASS)
//      {
//      /* ��ʱ����û�н��뼤��״̬ */
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
      memset(send_buff2, 0, 100);	//����ڴ�

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

//      xResult = xQueueReceive(xQueue1, /* ��Ϣ���о�� */
//                             &rev, /* �洢���յ������ݵ����� ucQueueMsgValue �� */
//                             portMAX_DELAY);/* ��������ʱ�� */
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
//      memset(send_buff, 0, 500);	//����ڴ�
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
       test_bit = xEventGroupWaitBits(test_group,      /* �¼���־���� */
                                      one_bit|two_bit,            /* �ȴ� bit0 �� bit1 ������ */
                                      pdTRUE,            /* �˳�ǰ bit0 �� bit1 ������������� bit0 �� bit1�������òű�ʾ���˳��� */
                                      pdTRUE,         /* ����Ϊ pdTRUE ��ʾ�ȴ� bit1 �� bit0 ��������*/
                                      portMAX_DELAY);
      
      if(test_bit & one_bit)
      {
          len = snprintf((char*)buff,100," \r\n��־λ1 ����1���������ˣ�Ȼ����0�� \r\n");
      
          UsartPushSendBuf(out_usart,(unsigned char*)buff,len);	
          UsartSend(out_usart);
      }
    }
}

static void AppTaskCreate (void)
{
    xTaskCreate( vTaskTaskUserIF,   /* ������ */
                 "vTaskUserIF",     /* ������    */
                 800,               /* ����ջ��С����λ��4�ֽ� */
                 NULL,              /* �������  */
                 2,                  /* �������ȼ�*/
                 &xHandleTaskUserIF );  /* ������  */
    
    
     xTaskCreate( vTaskLED,           /* ������ */
                 "vTaskLED",         /* ������    */
                 800,                 /* ����ջ��С����λ��4�ֽ� */
                 NULL,               /* �������  */
                 2,                  /* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
    
     xTaskCreate( vTaskMsgPro,            /* ������ */
                 "vTaskMsgPro",          /* ������    */
                 500,                    /* ����ջ��С����λ��4�ֽ� */
                 NULL,                     /* �������  */
                 3,                       /* �������ȼ�*/
                 &xHandleTaskMsgPro );  /* ������  */
    
    
     xTaskCreate( vTaskStart,             /* ������ */
                 "vTaskStart",            /* ������    */
                 100,                     /* ����ջ��С����λ��4�ֽ� */
                 NULL,                    /* �������  */
                 4,                       /* �������ȼ�*/
                 &xHandleTaskStart );     /* ������  */
}
