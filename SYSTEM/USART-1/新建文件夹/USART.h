/****************************************************************
 * Copyright (C) 2016, Yagro, all right reserved.
 * File name:    USART.h
 * Date:         2016.03.22
 * Description:  USART Driver
*****************************************************************/

#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <string.h>


#define USART1_BufferSize_Tx	2048
#define USART1_BufferSize_Rx	2048

#define USART2_BufferSize_Tx	2048
#define USART2_BufferSize_Rx	2048

#define USART6_BufferSize_Tx	2048
#define USART6_BufferSize_Rx	2048


extern uint8_t USART1_Buffer_Tx[USART1_BufferSize_Tx];
extern uint8_t USART1_Buffer_Rx[USART1_BufferSize_Rx];

extern uint8_t USART2_Buffer_Tx[USART2_BufferSize_Tx];
extern uint8_t USART2_Buffer_Rx[USART2_BufferSize_Rx];

extern uint8_t USART6_Buffer_Tx[USART6_BufferSize_Tx];
extern uint8_t USART6_Buffer_Rx[USART6_BufferSize_Rx];


#define USART_1 ((uint8_t)0x01)
#define USART_2 ((uint8_t)0x02)
#define USART_3 ((uint8_t)0x03)
#define USART_4 ((uint8_t)0x04)
#define USART_5 ((uint8_t)0x05)
#define USART_6 ((uint8_t)0x06)


#define BAUD_RATE_9600      ((uint32_t)9600)
#define BAUD_RATE_115200    ((uint32_t)115200)
#define BAUD_RATE_230400    ((uint32_t)230400)
#define BAUD_RATE_460800    ((uint32_t)460800)
#define BAUD_RATE_921600    ((uint32_t)921600)


void USART_Configuration(uint8_t USART_x, uint32_t BaudRate, uint16_t USART_Mode, uint16_t USART_IT, uint16_t USART_DMAReq);
void USART_DMA_TX_Configuration(uint8_t USART_x, uint32_t DMA_Memory0BaseAddr, uint32_t DMA_BufferSize);
void USART_DMA_RX_Configuration(uint8_t USART_x, uint32_t DMA_Memory0BaseAddr, uint32_t DMA_BufferSize);
void USART_DMA_TX(uint8_t USART_x, uint32_t DMA_BufferSize);
void USART_DMA_RX(uint8_t USART_x, uint32_t DMA_BufferSize);

#endif 	/* __USART_H */
