/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   config.c                                                      */
<<<<<<< HEAD
/* Date:        2017.4.24                                                     */
/* Description: config systick,TIM and Usart                                   */
=======
/* Date:        2016.8.4                                                     */
/* Description: config systick,TIM and GPIO                                   */
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "config.h"
#include "flash.h"
#include "usart.h"
<<<<<<< HEAD
#include "delay.h"
#if (RM3100_OPEN)
#include "RM3100.h"
#endif


/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/
=======

#ifdef RM3100_ON
#include "RM3100.h"
#endif

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/
TpUint16 fac_ms;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

<<<<<<< HEAD
TpBool HardWareInit(TpVoid)
{
  TpBool  result = INLIB_ERROR;
	
	TpUint32 baud_usart1;
  TpUint32 baud_usart2;
  TpUint32 baud_usart6;	

	/* systick init */
  SystickInit();
	
	/* flash init */
	if(FlashRead()!=FLAG_FLASH)
	{
		FlashInit();
		FlashWrite();	
	}
	
	/* init RM3100 and SPI  */
  if(RM3100_OPEN)
	{
    RM3100Config(GetMagRegisterRate());	
	}
	
		/* init UBLOX */
	if(UBLOX_OPEN)
	{
    UbloxInit();
	}

	baud_usart2 = GetUserUsartBaudrate();
  UsartConfig(GetUsartAddress(USART_2),USART_2,baud_usart2);
 
	baud_usart6 = GetDataUsartBaudrate();
  UsartConfig(GetUsartAddress(USART_6),USART_6,baud_usart6);
  
  EXTI_Config();
  NVIC_Config();
	

  
  result = INLIB_OK;
  return result;
=======
TpBool SystickInit(TpVoid)
{
  TpBool resutlt = INLIB_ERROR;
  
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disability SysTick counter */
  fac_ms = SystemCoreClock/SYSTICK_MS;

  resutlt = INLIB_OK;
  return resutlt;
}

TpBool Delay_ms(u16 nms)
{
  TpBool resutlt = INLIB_ERROR;
  TpUint32 temp;

  SysTick->LOAD = (uint32_t)nms * fac_ms;   /* Time load (SysTick-> LOAD is 24bit) */
  SysTick->VAL = 0x00;                      /* Empty counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; /* Start the countdown */

  do
  {
    temp = SysTick->CTRL;
  }
  while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
  SysTick->VAL = 0x00;                        /* Empty counter */
  
  resutlt = INLIB_OK;
  return resutlt;
}

TpBool HardWareInit(TpVoid)
{
  TpBool resutlt = INLIB_ERROR;

  SystickInit();
  
  if(FlashRead(&syspara) != FLAG_FLASH )
	{
		FlashInit(&syspara);
		FlashWrite(&syspara);
	}
	
#ifdef RM3100_ON
  RM3100Config();
#endif

#ifdef UBLOX_ON
  UbloxConfig();
#endif
 
  UsartConfig(&usart1,1,syspara.baud_usart1);
  UsartConfig(&usart2,2,syspara.baud_usart2);
  UsartConfig(&usart6,6,syspara.baud_usart6);
  
  resutlt = INLIB_OK;
  return resutlt;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
}


TpVoid NVIC_Config(TpVoid)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0 );
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
<<<<<<< HEAD
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  	
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
=======
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
  
//  NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);  	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
<<<<<<< HEAD
	
=======
//	
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

<<<<<<< HEAD

=======
#ifdef UBLOX_ON

#endif
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

TpVoid EXTI_Config(TpVoid)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  
<<<<<<< HEAD
#if (EXTI_LINE0_OPEN)
=======
#ifdef EXTI_LINE0_ON
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  EXTI_ClearITPendingBit(EXTI_Line0);
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
#endif

<<<<<<< HEAD
#if (EXTI_LINE1_OPEN)
=======
#ifdef EXTI_LINE1_ON
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
   /* GPIOs Configuration */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Configure PA1 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* LINE1 Configuration */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);

  /* Clear pending flags */
  EXTI_ClearITPendingBit(EXTI_Line1);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
#endif
<<<<<<< HEAD
}
=======
}

#ifdef UBLOX_ON
TpVoid UbloxConfig(TpVoid)
{  
  UsartUblox();
	//UsartConfig(&usart1,1,9600);
	UsartPushSendBuf(&usart1,(TpUchar*)"a",1,0);
	UsartSend(&usart1);
	Delay_ms(150);
	Ublox_Init(&syspara.ub);
	Delay_ms(100);
}
TpVoid UsartUblox(TpVoid)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  DMA_InitTypeDef   SendDMA_InitStructure;
  
  usart1.index = 1;
  UsartComBufConfig(&usart1,INDEX_USART1);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_1_Tx, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_1_Rx, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  GPIO_PinAFConfig(GPIO_USART_1_Tx, GPIO_PinSource_USART_1_Tx, GPIO_AF_USART1); /* Connect GPIOxn to USART1_Tx */
  GPIO_PinAFConfig(GPIO_USART_1_Rx, GPIO_PinSource_USART_1_Rx, GPIO_AF_USART1); /* Connect GPIOxn to USART1_Rx */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_1_Tx;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_USART_1_Tx, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_1_Rx;
  GPIO_Init(GPIO_USART_1_Rx, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = BAUDRATE_9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
  
  USART_Init(USART1, &USART_InitStructure);
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  USART_Cmd(USART1, ENABLE);
    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
	
	
  DMA_DeInit(DMA2_Stream7);
  while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);

  SendDMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
  SendDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; 
	SendDMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)usart1.cb.send_buf ;//(uint32_t)USART1_Buffer_Tx;            /* Memory address */
	SendDMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                 /* Data Memory to Peripheral */
	SendDMA_InitStructure.DMA_BufferSize = 0;                      /* Specifies the DMA channel DMA buffer size */
	SendDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        /* Peripheral address does not increase */
	SendDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 /* Memory address increment */
	SendDMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; /* Peripheral data width of 8 bit */
	SendDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         /* Memory data width of 8 bit */
	SendDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           /* Use Normal mode */
	SendDMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   /* Medium priority */
	SendDMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	SendDMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	SendDMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;             /* A single transmission burst memory */
	SendDMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  

  SentDMA_InitStructure1 = SendDMA_InitStructure;
  DMA_Init(DMA2_Stream7, &SendDMA_InitStructure);
  DMA_Cmd(DMA2_Stream7, DISABLE);
}
#endif
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
