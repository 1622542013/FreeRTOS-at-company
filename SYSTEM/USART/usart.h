/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   USART.h                                                    */
<<<<<<< HEAD
/* Date:        2016.8.4                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_USART_H__
#define __UMI_USART_H__
=======
/* Date:        2016.12.7                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __PROJECT_UMI_USART_H
#define __PROJECT_UMI_USART_H
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"
<<<<<<< HEAD
=======
#include "globals.h"
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/
<<<<<<< HEAD

#define USART_1 ((uint8_t)0x01)
#define USART_2 ((uint8_t)0x02)
//#define USART_3 ((uint8_t)0x03)
//#define USART_4 ((uint8_t)0x04)
//#define USART_5 ((uint8_t)0x05)
#define USART_6 ((uint8_t)0x06)


#define BUFSIZE_USART        (512)

/* usart 1 */
#define BUFSIZE_USART1_SEND  (256)
#define BUFSIZE_USART1_REC   (512)

/* usart 2 */
#define BUFSIZE_USART2_SEND  (1024)
#define BUFSIZE_USART2_REC   (512)

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
=======
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
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

#define RCC_AHB1Periph_USART_1_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_1_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_1_Tx               GPIOA
#define GPIO_USART_1_Rx               GPIOA

#define GPIO_Pin_USART_1_Tx           GPIO_Pin_9
#define GPIO_Pin_USART_1_Rx           GPIO_Pin_10

#define GPIO_PinSource_USART_1_Tx     GPIO_PinSource9
#define GPIO_PinSource_USART_1_Rx     GPIO_PinSource10

/*************************************************************/

<<<<<<< HEAD
/***************** USART_2 Configuration *********************/
=======
/***************** USART2 Configuration *********************/
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

#define RCC_AHB1Periph_USART_2_Tx     RCC_AHB1Periph_GPIOA
#define RCC_AHB1Periph_USART_2_Rx     RCC_AHB1Periph_GPIOA

#define GPIO_USART_2_Tx               GPIOA
#define GPIO_USART_2_Rx               GPIOA

#define GPIO_Pin_USART_2_Tx           GPIO_Pin_2
#define GPIO_Pin_USART_2_Rx           GPIO_Pin_3

#define GPIO_PinSource_USART_2_Tx     GPIO_PinSource2
#define GPIO_PinSource_USART_2_Rx     GPIO_PinSource3

/*************************************************************/

<<<<<<< HEAD
/***************** USART_3 Configuration *********************/
=======
/***************** USART3 Configuration *********************/
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

#define RCC_AHB1Periph_USART_3_Tx     RCC_AHB1Periph_GPIOB
#define RCC_AHB1Periph_USART_3_Rx     RCC_AHB1Periph_GPIOB

#define GPIO_USART_3_Tx               GPIOB
#define GPIO_USART_3_Rx               GPIOB

#define GPIO_Pin_USART_3_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_3_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_3_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_3_Rx     GPIO_PinSource11

/*************************************************************/

<<<<<<< HEAD
/***************** USART_4 Configuration *********************/
=======
/***************** USART4 Configuration *********************/
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

#define RCC_AHB1Periph_USART_4_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_4_Rx     RCC_AHB1Periph_GPIOC

#define GPIO_USART_4_Tx               GPIOC
#define GPIO_USART_4_Rx               GPIOC

#define GPIO_Pin_USART_4_Tx           GPIO_Pin_10
#define GPIO_Pin_USART_4_Rx           GPIO_Pin_11

#define GPIO_PinSource_USART_4_Tx     GPIO_PinSource10
#define GPIO_PinSource_USART_4_Rx     GPIO_PinSource11

/*************************************************************/

<<<<<<< HEAD
/***************** USART_5 Configuration *********************/
=======
/***************** USART5 Configuration *********************/
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

#define RCC_AHB1Periph_USART_5_Tx     RCC_AHB1Periph_GPIOC
#define RCC_AHB1Periph_USART_5_Rx     RCC_AHB1Periph_GPIOD

#define GPIO_USART_5_Tx               GPIOC
#define GPIO_USART_5_Rx               GPIOD

#define GPIO_Pin_USART_5_Tx           GPIO_Pin_12
#define GPIO_Pin_USART_5_Rx           GPIO_Pin_2

#define GPIO_PinSource_USART_5_Tx     GPIO_PinSource12
#define GPIO_PinSource_USART_5_Rx     GPIO_PinSource2

/*************************************************************/

<<<<<<< HEAD
/***************** USART_6 Configuration *********************/
=======
/***************** USART6 Configuration *********************/
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

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
<<<<<<< HEAD
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
	
=======
  TpUchar  rec_buf[BUFSIZE_USART_512];
  TpUint16 rec_size; 
  TpUint16 rec_pt;
	TpUchar  rec_flag;
  
  TpUchar  send_buf[BUFSIZE_USART_512];
  TpUint16 send_size;
  TpUint16 send_pt;  
	TpUchar  send_flag;
	
  TpUchar  flag_block;	
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
}ComBuf;

typedef struct tagComPara
{
  TpUint16 baud;
  TpUchar  parity;
  TpUchar  databit;
  TpUchar  stopbit;
}ComPara;

<<<<<<< HEAD
typedef struct tagDmaPara
{
	DMA_InitTypeDef  RecDMA_InitStructure;
	DMA_InitTypeDef  SentDMA_InitStructure;
}DmaPara;	
=======
typedef struct tagMainBuf
{
	TpUchar  send_buf[BUFSIZE_USART_512];
	TpUint16 bufsize_main;
	TpUint16 send_pt;
  TpUint16 num_lock;
}MainBuf;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

typedef struct tagUsart
{
  TpUchar  index;
  ComBuf   cb;
<<<<<<< HEAD
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
=======
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
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
