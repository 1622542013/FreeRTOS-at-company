/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   USART.h                                                    */
/* Date:        2016.8.4                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_USART_H__
#define __UMI_USART_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

//#define USART_1 ((uint8_t)0x01)
#define USART_2 ((uint8_t)0x02)
//#define USART_3 ((uint8_t)0x03)
//#define USART_4 ((uint8_t)0x04)
//#define USART_5 ((uint8_t)0x05)
//#define USART_6 ((uint8_t)0x06)


#define BUFSIZE_USART        (512)

/* usart 1 */
#define BUFSIZE_USART1_SEND  (256)
#define BUFSIZE_USART1_REC   (512)

/* usart 2 */
#define BUFSIZE_USART2_SEND  (2048)
#define BUFSIZE_USART2_REC   (2048)

/* usart 3 */
#define BUFSIZE_USART3_SEND  (256)
#define BUFSIZE_USART3_REC   (256)

/* usart 4 */
#define BUFSIZE_USART4_SEND  (256)
#define BUFSIZE_USART4_REC   (256)

/* usart 5 */
#define BUFSIZE_USART5_SEND  (256)
#define BUFSIZE_USART5_REC   (256)

/* usart 6 */
#define BUFSIZE_USART6_SEND  (512)
#define BUFSIZE_USART6_REC   (1024)



#define BAUD_9600       (9600)
#define BAUD_115200     (115200)

#define BAUD_USART1     ((TpUint32)115200)
#define BAUD_USART2     ((TpUint32)460800)
#define BAUD_USART3     ((TpUint32)115200)
#define BAUD_USART4     ((TpUint32)115200)
#define BAUD_USART5     ((TpUint32)115200)
#define BAUD_USART6     ((TpUint32)921600)

#define PARITY_USART1   USART_Parity_No
#define PARITY_USART2   USART_Parity_No
#define PARITY_USART3   USART_Parity_No
#define PARITY_USART4   USART_Parity_No
#define PARITY_USART5   USART_Parity_No
#define PARITY_USART6   USART_Parity_No

#define WORDLEN_USART1  USART_WordLength_8b
#define WORDLEN_USART2  USART_WordLength_8b
#define WORDLEN_USART3  USART_WordLength_8b
#define WORDLEN_USART4  USART_WordLength_8b
#define WORDLEN_USART5  USART_WordLength_8b
#define WORDLEN_USART6  USART_WordLength_8b

#define STOPBIT_USART1  USART_StopBits_1
#define STOPBIT_USART2  USART_StopBits_1
#define STOPBIT_USART3  USART_StopBits_1
#define STOPBIT_USART4  USART_StopBits_1
#define STOPBIT_USART5  USART_StopBits_1
#define STOPBIT_USART6  USART_StopBits_1


/***************** USART_1 Configuration *********************/

#define RCC_AHB1Periph_USART_1_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_1_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_1_Tx               GPIOA
#define GPIO_USART_1_Rx               GPIOA

#define GPIO_Pin_USART_1_Tx           GPIO_Pin_9
#define GPIO_Pin_USART_1_Rx           GPIO_Pin_10

#define GPIO_PinSource_USART_1_Tx     GPIO_PinSource9
#define GPIO_PinSource_USART_1_Rx     GPIO_PinSource10

/*************************************************************/

/***************** USART_2 Configuration *********************/

#define RCC_AHB1Periph_USART_2_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_2_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_2_Tx               GPIOA
#define GPIO_USART_2_Rx               GPIOA

#define GPIO_Pin_USART_2_Tx           GPIO_Pin_2
#define GPIO_Pin_USART_2_Rx           GPIO_Pin_3

#define GPIO_PinSource_USART_2_Tx     GPIO_PinSource2
#define GPIO_PinSource_USART_2_Rx     GPIO_PinSource3

/*************************************************************/

/***************** USART_3 Configuration *********************/

#define RCC_AHB1Periph_USART_3_Tx     RCC_AHB1Periph_GPIOB
#define RCC_AHB1Periph_USART_3_Rx     RCC_AHB1Periph_GPIOB

#define GPIO_USART_3_Tx               GPIOB
#define GPIO_USART_3_Rx               GPIOB

#define GPIO_Pin_USART_3_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_3_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_3_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_3_Rx     GPIO_PinSource11

/*************************************************************/

/***************** USART_4 Configuration *********************/

#define RCC_AHB1Periph_USART_4_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_4_Rx     RCC_AHB1Periph_GPIOC

#define GPIO_USART_4_Tx               GPIOC
#define GPIO_USART_4_Rx               GPIOC

#define GPIO_Pin_USART_4_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_4_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_4_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_4_Rx     GPIO_PinSource11

/*************************************************************/

/***************** USART_5 Configuration *********************/

#define RCC_AHB1Periph_USART_5_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_5_Rx     RCC_AHB1Periph_GPIOD

#define GPIO_USART_5_Tx               GPIOC
#define GPIO_USART_5_Rx               GPIOD

#define GPIO_Pin_USART_5_Tx           GPIO_Pin_12
#define GPIO_Pin_USART_5_Rx           GPIO_Pin_2

#define GPIO_PinSource_USART_5_Tx     GPIO_PinSource12
#define GPIO_PinSource_USART_5_Rx     GPIO_PinSource2

/*************************************************************/

/***************** USART_6 Configuration *********************/

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
  TpUchar* rec_buf;
  TpUint16 rec_size; 
  TpUint16 rec_pt;
  
  TpUchar* send_buf;
  TpUint16 send_size;
  TpUint16 send_pt;
	TpUint16 send_lock;
	
	
	TpUchar* main_buf;
	TpUint16 main_size;
	TpUint16 main_pt;
	TpUint16 main_lock;
	
}ComBuf;

typedef struct tagComPara
{
  TpUint16 baud;
  TpUchar  parity;
  TpUchar  databit;
  TpUchar  stopbit;
}ComPara;

typedef struct tagDmaPara
{
	DMA_InitTypeDef  RecDMA_InitStructure;
	DMA_InitTypeDef  SentDMA_InitStructure;
}DmaPara;	

typedef struct tagUsart
{
  TpUchar  index;
  ComBuf   cb;
  ComPara  cp;
	TpUchar  is_send;
//  DmaPara  dp;  
}Usart;
#pragma pack(pop)



/* config usart */
TpVoid UsartConfig(Usart* pu,TpUchar index,TpUint32 baudrate);
TpVoid UsartComBufConfig(Usart* pu);
TpVoid UsartGpioConfig(Usart* pu);
TpVoid UsartDmaConfig(Usart* pu);

TpVoid UsartParaConfig(Usart* pu,TpUint32 buadrate);

/* send data */
TpVoid UsartPushSendBuf(Usart* pu,TpUchar* pbuf,TpUint16 len);
TpVoid UsartPushMainBuf(Usart* pu,TpUchar* pbuf,TpUint16 len);
TpBool UsartSend(Usart* pu);
TpVoid SendCom(Usart* pu);

/* start rec  */
TpVoid UsartRecEnable(Usart* pu);
Usart* GetUsartAddress(TpUchar index);

/* get rec num */
TpUint32 GetUsartRxNum(TpUchar index);
TpVoid UsartSendImmediately(Usart* pu,TpUchar* buff,TpUint16 length);

#endif 	/* __USART_H */
