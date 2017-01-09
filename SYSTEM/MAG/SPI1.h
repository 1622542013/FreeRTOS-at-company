/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   SPI1.h                                                     */
/* Date:        2016.8.4                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_SPI1_H_
#define __UMI_SPI1_H_

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define SPI1_CS1_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI1_CS1_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define SPI1_RX_LEN          (5)


/*============================================================================*/
/*                           declarations                                     */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
  
extern TpUint16 SPI1_Buffer_Tx[5];
extern TpUint16 SPI1_Buffer_Rx[5];

TpBool SPI1_Init(TpVoid);
TpBool SPI1_DMA_TX_Init(TpVoid);
TpBool SPI1_DMA_RX_Init(TpVoid);
TpBool SPI1_DMA_TX(TpVoid);
TpBool SPI1_DMA_RX(TpVoid);
TpUint16 SPI1_SendHalfWord(uint16_t halfword);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

