/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   USART.h                                                    */
/* Date:        2016.12.7                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __PROJECT_UMI_USART_H
#define __PROJECT_UMI_USART_H

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"
#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/
/* buf size */
#define BUFSIZE_USART_512    ((TpUint16)512)
#define BUFSIZE_USART_1024   ((TpUint16)1024)

#define BUFSIZE_USART1       BUFSIZE_USART_512
#define BUFSIZE_USART2       BUFSIZE_USART_512
#define BUFSIZE_USART3       BUFSIZE_USART_512
#define BUFSIZE_USART4       BUFSIZE_USART_512
#define BUFSIZE_USART5       BUFSIZE_USART_512
#define BUFSIZE_USART6       BUFSIZE_USART_512

/* baudrate */
#define BAUDRATE_9600        ((TpUint32)9600)
#define BAUDRATE_115200      ((TpUint32)115200)
#define BAUDRATE_230400      ((TpUint32)230400)
#define BAUDRATE_460800      ((TpUint32)460800)
#define BAUDRATE_921600      ((TpUint32)921600)

#define BAUD_USART1          BAUDRATE_115200
#define BAUD_USART2          BAUDRATE_460800
#define BAUD_USART3          BAUDRATE_115200
#define BAUD_USART4          BAUDRATE_115200
#define BAUD_USART5          BAUDRATE_115200
#define BAUD_USART6          BAUDRATE_921600

/* parity */
#define PARITY_USART1        USART_Parity_No
#define PARITY_USART2        USART_Parity_No
#define PARITY_USART3        USART_Parity_No
#define PARITY_USART4        USART_Parity_No
#define PARITY_USART5        USART_Parity_No
#define PARITY_USART6        USART_Parity_No

#define WORDLEN_USART1       USART_WordLength_8b
#define WORDLEN_USART2       USART_WordLength_8b
#define WORDLEN_USART3       USART_WordLength_8b
#define WORDLEN_USART4       USART_WordLength_8b
#define WORDLEN_USART5       USART_WordLength_8b
#define WORDLEN_USART6       USART_WordLength_8b

#define STOPBIT_USART1       USART_StopBits_1
#define STOPBIT_USART2       USART_StopBits_1
#define STOPBIT_USART3       USART_StopBits_1
#define STOPBIT_USART4       USART_StopBits_1
#define STOPBIT_USART5       USART_StopBits_1
#define STOPBIT_USART6       USART_StopBits_1


#define INDEX_USART1         ((uint8_t)0x01)
#define INDEX_USART2         ((uint8_t)0x02)
#define INDEX_USART3         ((uint8_t)0x03)
#define INDEX_USART4         ((uint8_t)0x04)
#define INDEX_USART5         ((uint8_t)0x05)
#define INDEX_USART6         ((uint8_t)0x06)

/***************** USART1 Configuration *********************/

#define RCC_AHB1Periph_USART_1_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_1_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_1_Tx               GPIOA
#define GPIO_USART_1_Rx               GPIOA

#define GPIO_Pin_USART_1_Tx           GPIO_Pin_9
#define GPIO_Pin_USART_1_Rx           GPIO_Pin_10

#define GPIO_PinSource_USART_1_Tx     GPIO_PinSource9
#define GPIO_PinSource_USART_1_Rx     GPIO_PinSource10

/*************************************************************/

/***************** USART2 Configuration *********************/

#define RCC_AHB1Periph_USART_2_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_2_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_2_Tx               GPIOA
#define GPIO_USART_2_Rx               GPIOA

#define GPIO_Pin_USART_2_Tx           GPIO_Pin_2
#define GPIO_Pin_USART_2_Rx           GPIO_Pin_3

#define GPIO_PinSource_USART_2_Tx     GPIO_PinSource2
#define GPIO_PinSource_USART_2_Rx     GPIO_PinSource3

/*************************************************************/

/***************** USART3 Configuration *********************/

#define RCC_AHB1Periph_USART_3_Tx     RCC_AHB1Periph_GPIOB
#define RCC_AHB1Periph_USART_3_Rx     RCC_AHB1Periph_GPIOB

#define GPIO_USART_3_Tx               GPIOB
#define GPIO_USART_3_Rx               GPIOB

#define GPIO_Pin_USART_3_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_3_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_3_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_3_Rx     GPIO_PinSource11

/*************************************************************/

/***************** USART4 Configuration *********************/

#define RCC_AHB1Periph_USART_4_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_4_Rx     RCC_AHB1Periph_GPIOC

#define GPIO_USART_4_Tx               GPIOC
#define GPIO_USART_4_Rx               GPIOC

#define GPIO_Pin_USART_4_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_4_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_4_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_4_Rx     GPIO_PinSource11

/*************************************************************/

/***************** USART5 Configuration *********************/

#define RCC_AHB1Periph_USART_5_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_5_Rx     RCC_AHB1Periph_GPIOD

#define GPIO_USART_5_Tx               GPIOC
#define GPIO_USART_5_Rx               GPIOD

#define GPIO_Pin_USART_5_Tx           GPIO_Pin_12
#define GPIO_Pin_USART_5_Rx           GPIO_Pin_2

#define GPIO_PinSource_USART_5_Tx     GPIO_PinSource12
#define GPIO_PinSource_USART_5_Rx     GPIO_PinSource2

/*************************************************************/

/***************** USART6 Configuration *********************/

#define RCC_AHB1Periph_USART_6_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_6_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_6_Tx               GPIOA
#define GPIO_USART_6_Rx               GPIOA

#define GPIO_Pin_USART_6_Tx           GPIO_Pin_11
#define GPIO_Pin_USART_6_Rx           GPIO_Pin_12

#define GPIO_PinSource_USART_6_Tx     GPIO_PinSource11
#define GPIO_PinSource_USART_6_Rx     GPIO_PinSource12

/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct tagComBuf
{
  TpUchar  rec_buf[BUFSIZE_USART_512];
  TpUint16 rec_size; 
  TpUint16 rec_pt;
	TpUchar  rec_flag;
  
  TpUchar  send_buf[BUFSIZE_USART_512];
  TpUint16 send_size;
  TpUint16 send_pt;  
	TpUchar  send_flag;
	
  TpUchar  flag_block;	
}ComBuf;

typedef struct tagComPara
{
  TpUint16 baud;
  TpUchar  parity;
  TpUchar  databit;
  TpUchar  stopbit;
}ComPara;

typedef struct tagMainBuf
{
	TpUchar  send_buf[BUFSIZE_USART_512];
	TpUint16 bufsize_main;
	TpUint16 send_pt;
  TpUint16 num_lock;
}MainBuf;

typedef struct tagUsart
{
  TpUchar  index;
  ComBuf   cb;
  ComPara  cp;  
	MainBuf  mb;
}Usart;

#pragma pack(pop)

/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
extern Usart usart1;
extern Usart usart2;
extern Usart usart6;

#ifdef UBLOX_ON
extern DMA_InitTypeDef SentDMA_InitStructure1;
#endif

/* config usart api*/
TpBool UsartConfig(Usart* pu,TpUchar index,TpUint32 baudrate);

TpBool UsartComBufConfig(Usart* pu,TpUchar index);                  /* config rec and send buf */
TpBool UsartGpioConfig(Usart* pu,TpUchar index);                    /* config gpio */
TpBool UsartDmaConfig(Usart* pu,TpUchar index);                     /* config dma */
TpBool UsartParaConfig(Usart* pu,TpUchar index,TpUint32 buadrate);  /* config param */

/* push data to send buf*/
TpBool UsartPushSendBuf(Usart* pu,TpUchar* pbuf,TpUint16 num,TpUint16 index);
/* push data to main buf  */	
TpBool UsartPushMainBuf(Usart* pu,TpUchar* pbuf,TpUint16 num);

/* send data  */
TpUint16 UsartDmaGetCurrentDataCnt(Usart* pu);
TpBool UsartSendMainBuf(Usart* pu);
TpBool UsartSend(Usart* pu);
TpBool UsartDmaSend(Usart* pu);
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 	/* __PROJECT_UMI_USART_H */
