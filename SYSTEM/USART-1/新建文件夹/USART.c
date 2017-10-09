/****************************************************************
 * Copyright (C) 2016, Yagro, all right reserved.
 * File name:    USART.c
 * Date:         2016.03.22
 * Description:  USART Driver
*****************************************************************/


#include "USART.h"


uint8_t USART1_Buffer_Tx[USART1_BufferSize_Tx];
uint8_t USART1_Buffer_Rx[USART1_BufferSize_Rx];

uint8_t USART2_Buffer_Tx[USART2_BufferSize_Tx];
uint8_t USART2_Buffer_Rx[USART2_BufferSize_Rx];

uint8_t USART6_Buffer_Tx[USART6_BufferSize_Tx];
uint8_t USART6_Buffer_Rx[USART6_BufferSize_Rx];


/****************************************************
 * Function:    USART_Configuration
 * Description: USART Configuration.
 * Input:       USART_x
 *              BaudRate
 *              USART_Mode
 *              USART_IT
 *              USART_DMAReq
 * Output:
 * Return:
*****************************************************/
void USART_Configuration(uint8_t USART_x, uint32_t BaudRate, uint16_t USART_Mode, uint16_t USART_IT, uint16_t USART_DMAReq)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  if(USART_x == USART_1)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);       /* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      /* Enable USART1 clock */

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);   /* Connect GPIOA9 to USART1_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);  /* Connect GPIOA10 to USART1_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }

  if(USART_x == USART_2)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);     /* Enable GPIOA clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);    /* Enable USART2 clock */

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);	/* Connect GPIOA2 to USART2_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);	/* Connect GPIOA3 to USART2_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }

  if(USART_x == USART_3)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);       /* Enable GPIOB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      /* Enable USART3 clock */

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);  /* Connect GPIOB10 to USART3_Tx */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);  /* Connect GPIOB11 to USART3_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  }

  if(USART_x == USART_4)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);     /* Enable GPIOC clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);     /* Enable USART4 clock */

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);	/* Connect GPIOC10 to USART4_Tx */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);	/* Connect GPIOC11 to USART4_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
  }
  
  if(USART_x == USART_5)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);     /* Enable GPIOC clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);     /* Enable GPIOD clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);     /* Enable USART5 clock */

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);	/* Connect GPIOC12 to USART2_Tx */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);	/* Connect GPIOD2 to USART2_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
  }
  
  if(USART_x == USART_6)
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);       /* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);      /* Enable USART6 clock */

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_USART6);  /* Connect GPIOA11 to USART6_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_USART6);  /* Connect GPIOA12 to USART6_Rx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }

  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode;

  if(USART_x == USART_1)
  {
    USART_Init(USART1, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART1 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART1 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART1 */
      USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART1 */
    }

    if(USART_IT)
      USART_ITConfig(USART1, USART_IT, ENABLE); /* Enabling interrupts specified USART1 */

    USART_Cmd(USART1, ENABLE);
  }

  if(USART_x == USART_2)
  {
    USART_Init(USART2, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART2 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART2 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART2 */
      USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART2 */
    }

    if(USART_IT)
      USART_ITConfig(USART2, USART_IT, ENABLE); /* Enabling interrupts specified USART2 */

    USART_Cmd(USART2, ENABLE);
  }

  if(USART_x == USART_3)
  {
    USART_Init(USART3, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART3 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART3 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART3 */
      USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART3 */
    }

    if(USART_IT)
      USART_ITConfig(USART3, USART_IT, ENABLE); /* Enabling interrupts specified USART3 */

    USART_Cmd(USART3, ENABLE);
  }

  if(USART_x == USART_4)
  {
    USART_Init(UART4, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); /* Enabling the DMA request specified USART4 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE); /* Enabling the DMA request specified USART4 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); /* Enabling the DMA request specified USART4 */
      USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE); /* Enabling the DMA request specified USART4 */
    }

    if(USART_IT)
      USART_ITConfig(UART4, USART_IT, ENABLE);  /* Enabling interrupts specified USART4 */

    USART_Cmd(UART4, ENABLE);
  }
  
  if(USART_x == USART_5)
  {
    USART_Init(UART5, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE); /* Enabling the DMA request specified USART5 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE); /* Enabling the DMA request specified USART5 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE); /* Enabling the DMA request specified USART5 */
      USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE); /* Enabling the DMA request specified USART5 */
    }

    if(USART_IT)
      USART_ITConfig(UART5, USART_IT, ENABLE);  /* Enabling interrupts specified USART5 */

    USART_Cmd(UART5, ENABLE);
  }
  
  if(USART_x == USART_6)
  {
    USART_Init(USART6, &USART_InitStructure);

    if(USART_DMAReq == USART_DMAReq_Tx)
      USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART6 */
    if(USART_DMAReq == USART_DMAReq_Rx)
      USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART6 */
    if(USART_DMAReq == (USART_DMAReq_Tx|USART_DMAReq_Rx))
    {
      USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);  /* Enabling the DMA request specified USART6 */
      USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);  /* Enabling the DMA request specified USART6 */
    }

    if(USART_IT)
      USART_ITConfig(USART6, USART_IT, ENABLE); /* Enabling interrupts specified USART6 */

    USART_Cmd(USART6, ENABLE);
  }
}

/****************************************************
 * Function:    USART_DMA_TX_Configuration
 * Description: USART DMA TX Configuration.
 * Input:       USART_x
 *              DMA_Memory0BaseAddr
 *              DMA_BufferSize
 * Output:
 * Return:
*****************************************************/
void USART_DMA_TX_Configuration(uint8_t USART_x, uint32_t DMA_Memory0BaseAddr, uint32_t DMA_BufferSize)
{
	DMA_InitTypeDef DMA_InitStructure;

	if(USART_x == USART_2 || USART_x == USART_3 || USART_x == USART_4 || USART_x == USART_5)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  /* Enable DMA1 clock */
	else
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  /* Enable DMA2 clock */

	if(USART_x == USART_1)
	{
		DMA_DeInit(DMA2_Stream7);
		while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; /* Set the DMA source: peripheral data register address */
	}

	if(USART_x == USART_2)
	{
		DMA_DeInit(DMA1_Stream6);
		while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; /* Set the DMA source: peripheral data register address */
	}

	if(USART_x == USART_3)
	{
		DMA_DeInit(DMA1_Stream3);
		while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR; /* Set the DMA source: peripheral data register address */
	}

	if(USART_x == USART_4)
	{
		DMA_DeInit(DMA1_Stream4);
		while(DMA_GetCmdStatus(DMA1_Stream4) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;  /* Set the DMA source: peripheral data register address */
	}
  
  if(USART_x == USART_5)
	{
		DMA_DeInit(DMA1_Stream4);
		while(DMA_GetCmdStatus(DMA1_Stream7) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;  /* Set the DMA source: peripheral data register address */
	}
  
  if(USART_x == USART_6)
	{
		DMA_DeInit(DMA2_Stream6);
		while(DMA_GetCmdStatus(DMA2_Stream6) != DISABLE);

		DMA_InitStructure.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;  /* Set the DMA source: peripheral data register address */
	}

	DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;            /* Memory address */
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                 /* Data Memory to Peripheral */
	DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;                      /* Specifies the DMA channel DMA buffer size */
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        /* Peripheral address does not increase */
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 /* Memory address increment */
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; /* Peripheral data width of 8 bit */
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         /* Memory data width of 8 bit */
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           /* Use Normal mode */
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   /* Medium priority */
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;             /* A single transmission burst memory */
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;     /* Peripherals single transmission burst */

	if(USART_x == USART_1)
	{
		DMA_Init(DMA2_Stream7, &DMA_InitStructure);
		DMA_Cmd(DMA2_Stream7, DISABLE);
	}

	if(USART_x == USART_2)
	{
		DMA_Init(DMA1_Stream6, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream6, DISABLE);
	}

	if(USART_x == USART_3)
	{
		DMA_Init(DMA1_Stream3, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream3, DISABLE);
	}

	if(USART_x == USART_4)
	{
		DMA_Init(DMA1_Stream4, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream4, DISABLE);
	}
  
  if(USART_x == USART_5)
	{
		DMA_Init(DMA1_Stream7, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream7, DISABLE);
	}
  
  if(USART_x == USART_6)
	{
		DMA_Init(DMA2_Stream6, &DMA_InitStructure);
		DMA_Cmd(DMA2_Stream6, DISABLE);
	}
}

/****************************************************
 * Function:    USART_DMA_RX_Configuration
 * Description: USART DMA RX Configuration.
 * Input:       USART_x
 *              DMA_Memory0BaseAddr
 *              DMA_BufferSize
 * Output:
 * Return:
*****************************************************/
void USART_DMA_RX_Configuration(uint8_t USART_x, uint32_t DMA_Memory0BaseAddr, uint32_t DMA_BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  if(USART_x == USART_2 || USART_x == USART_3 || USART_x == USART_4 || USART_x == USART_5)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  /* Enable DMA1 clock */
  else
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  /* Enable DMA2 clock */

  if(USART_x == USART_1)
  {
    DMA_DeInit(DMA2_Stream2);
    while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; /* Set the DMA source: peripheral data register address */
  }

  if(USART_x == USART_2)
  {
    DMA_DeInit(DMA1_Stream5);
    while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; /* Set the DMA source: peripheral data register address */
  }

  if(USART_x == USART_3)
  {
    DMA_DeInit(DMA1_Stream1);
    while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR; /* Set the DMA source: peripheral data register address */
  }

  if(USART_x == USART_4)
  {
    DMA_DeInit(DMA1_Stream2);
    while(DMA_GetCmdStatus(DMA1_Stream2) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;  /* Set the DMA source: peripheral data register address */
  }
  
  if(USART_x == USART_5)
  {
    DMA_DeInit(DMA1_Stream0);
    while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;  /* Set the DMA source: peripheral data register address */
  }
  
  if(USART_x == USART_6)
  {
    DMA_DeInit(DMA2_Stream1);
    while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);

    DMA_InitStructure.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;  /* Set the DMA source: peripheral data register address */
  }

  DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;            /* Memory address */
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                 /* Data Peripheral to Memory */
  DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;                      /* Specifies the DMA channel DMA buffer size */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        /* Peripheral address does not increase */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 /* Memory address increment */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; /* Peripheral data width of 8 bit */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         /* Memory data width of 8 bit */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         /* Use Circular mode */
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   /* Medium priority */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;             /* A single transmission burst memory */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;     /* Peripherals single transmission burst */

  if(USART_x == USART_1)
  {
    DMA_Init(DMA2_Stream2, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream2, ENABLE);
  }

  if(USART_x == USART_2)
  {
    DMA_Init(DMA1_Stream5, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream5, ENABLE);
  }

  if(USART_x == USART_3)
  {
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream1, ENABLE);
  }

  if(USART_x == USART_4)
  {
    DMA_Init(DMA1_Stream2, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream2, ENABLE);
  }
  
  if(USART_x == USART_5)
  {
    DMA_Init(DMA1_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream0, ENABLE);
  }
  
  if(USART_x == USART_6)
  {
    DMA_Init(DMA2_Stream1, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream1, ENABLE);
  }
}

/****************************************************
 * Function:    USART_DMA_TX
 * Description: Start USART DMA Send.
 * Input:       USART_x
 *              DMA_BufferSize
 * Output:
 * Return:
*****************************************************/
void USART_DMA_TX(uint8_t USART_x, uint32_t DMA_BufferSize)
{
  if(USART_x == USART_1)
  {
    DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);  /* Clear Pending DMA channel x flag (DMA2 Stream7 transfer completion flag) */
    DMA_Cmd(DMA2_Stream7, DISABLE);
    while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream7, DMA_BufferSize);
    DMA_Cmd(DMA2_Stream7, ENABLE);
  }

  if(USART_x == USART_2)
  {
    DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream6 transfer completion flag) */
 //   DMA_Cmd(DMA1_Stream6, DISABLE);
 //   while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream6, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream6, ENABLE);
  }

  if(USART_x == USART_3)
  {
    DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream3 transfer completion flag) */
    DMA_Cmd(DMA1_Stream3, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream3, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream3, ENABLE);
  }

  if(USART_x == USART_4)
  {
    DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream4 transfer completion flag) */
    DMA_Cmd(DMA1_Stream4, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream4) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream4, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream4, ENABLE);
  }
  
  if(USART_x == USART_5)
  {
    DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream7 transfer completion flag) */
    DMA_Cmd(DMA1_Stream7, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream7) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream7, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream7, ENABLE);
  }
  
  if(USART_x == USART_6)
  {
    DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_TCIF6);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream6 transfer completion flag) */
    DMA_Cmd(DMA2_Stream6, DISABLE);
    while(DMA_GetCmdStatus(DMA2_Stream6) != DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream6, DMA_BufferSize);
    DMA_Cmd(DMA2_Stream6, ENABLE);
  }
}

/****************************************************
 * Function:    USART_DMA_RX
 * Description: Start USART DMA Receive.
 * Input:       USART_x
 *              DMA_BufferSize
 * Output:
 * Return:
*****************************************************/
void USART_DMA_RX(uint8_t USART_x, uint32_t DMA_BufferSize)
{
  if(USART_x == USART_1)
  {
    DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream2 transfer completion flag) */
    DMA_Cmd(DMA2_Stream2, DISABLE);
    while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream2, DMA_BufferSize);
    DMA_Cmd(DMA2_Stream2, ENABLE);
  }

  if(USART_x == USART_2)
  {
    DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream5 transfer completion flag) */
    DMA_Cmd(DMA1_Stream5, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream5, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream5, ENABLE);
  }

  if(USART_x == USART_3)
  {
    DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream1 transfer completion flag) */
    DMA_Cmd(DMA1_Stream1, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream1, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream1, ENABLE);
  }

  if(USART_x == USART_4)
  {
    DMA_ClearFlag(DMA1_Stream2, DMA_FLAG_TCIF2);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream2 transfer completion flag) */
    DMA_Cmd(DMA1_Stream2, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream2) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream2, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream2, ENABLE);
  }
  
  if(USART_x == USART_5)
  {
    DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream0 transfer completion flag) */
    DMA_Cmd(DMA1_Stream0, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream0, DMA_BufferSize);
    DMA_Cmd(DMA1_Stream0, ENABLE);
  }
  
  if(USART_x == USART_6)
  {
    DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream1 transfer completion flag) */
    DMA_Cmd(DMA2_Stream1, DISABLE);
    while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream1, DMA_BufferSize);
    DMA_Cmd(DMA2_Stream1, ENABLE);
  }
}
