/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   main.c                                                        */
/* Date:        2016.11.29                                                    */
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/
#include "stm32f4xx.h"
#include "config.h"
#include "gnss.h"
#include "protocol.h"

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

TpInt32 main(TpVoid)
{
  SCB->VTOR = FLASH_BASE|0x10000;
	
  HardWareInit();
  PackageInit(&package);
  ProtocolInit(&protocol);

	StartPrint();
	Delay_ms(100);	
  
  EXTI_Config();
  NVIC_Config();
	
	for(;;)
	{
		 UsartSend(&usart2);
	}

}
