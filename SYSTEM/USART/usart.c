/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   USART.c                                                       */
/* Date:        2016.7.21                                                     */
/* Description: config USART                                                  */
/*============================================================================*/

/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/
#ifdef  USART_1
Usart usart1;
static DMA_InitTypeDef  RecDMA_InitStructure_USART1;
static DMA_InitTypeDef  SendDMA_InitStructure_USART1;
#endif
#ifdef  USART_2
Usart usart2;
static DMA_InitTypeDef  RecDMA_InitStructure_USART2;
static DMA_InitTypeDef  SendDMA_InitStructure_USART2;
#endif
#ifdef  USART_3
Usart usart3;
static DMA_InitTypeDef  RecDMA_InitStructure_USART3;
static DMA_InitTypeDef  SendDMA_InitStructure_USART3;
#endif
#ifdef  USART_4
Usart usart4;
static DMA_InitTypeDef  RecDMA_InitStructure_USART4;
static DMA_InitTypeDef  SendDMA_InitStructure_USART4;
#endif
#ifdef  USART_5
Usart usart5;
static DMA_InitTypeDef  RecDMA_InitStructure_USART5;
static DMA_InitTypeDef  SendDMA_InitStructure_USART5;
#endif
#ifdef  USART_6
Usart usart6;
static DMA_InitTypeDef  RecDMA_InitStructure_USART6;
static DMA_InitTypeDef  SendDMA_InitStructure_USART6;
#endif

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

TpVoid UsartConfig(Usart* pu,TpUchar index,TpUint32 baudrate)
{
  pu->index = index;
  pu->is_send = 0;
  UsartComBufConfig(pu);
  UsartGpioConfig(pu);
  UsartParaConfig(pu,baudrate);
  UsartDmaConfig(pu);
}

TpVoid UsartComBufConfig(Usart* pu)
{ 
	/* point init zero  */
	pu->cb.rec_pt    = 0;
	pu->cb.send_pt   = 0;
	pu->cb.send_lock = 0;
	pu->cb.main_pt   = 0;
	pu->cb.main_lock = 0;
	
	switch(pu->index)
	{
#ifdef USART_1
		case USART_1:
				{
					 pu->cb.rec_size  = BUFSIZE_USART1_REC;
					 pu->cb.send_size = BUFSIZE_USART1_SEND;
					 pu->cb.main_size = BUFSIZE_USART1_SEND;
				}
				break;
#endif				
#ifdef	USART_2
		case USART_2:
				{
					 pu->cb.rec_size  = BUFSIZE_USART2_REC;
					 pu->cb.send_size = BUFSIZE_USART2_SEND;
					 pu->cb.main_size = BUFSIZE_USART2_SEND;
				}
				break;
		
#endif				
#ifdef	USART_3
		case USART_3:
				{
					 pu->cb.rec_size  = BUFSIZE_USART3_REC;
					 pu->cb.send_size = BUFSIZE_USART3_SEND;
					 pu->cb.main_size = BUFSIZE_USART3_SEND;
				}
				break;
				
#endif				
#ifdef	USART_4
		case USART_4:
				{
					 pu->cb.rec_size  = BUFSIZE_USART4_REC;
					 pu->cb.send_size = BUFSIZE_USART4_SEND;
					 pu->cb.main_size = BUFSIZE_USART4_SEND;
				}
				break;
				
#endif				
#ifdef	USART_5
		case USART_5:
				{
					 pu->cb.rec_size  = BUFSIZE_USART5_REC;
					 pu->cb.send_size = BUFSIZE_USART5_SEND;
					 pu->cb.main_size = BUFSIZE_USART5_SEND;
				}
				break;
				
#endif				
#ifdef	USART_6
		case USART_6:
				{
					 pu->cb.rec_size  = BUFSIZE_USART6_REC;
					 pu->cb.send_size = BUFSIZE_USART6_SEND;
					 pu->cb.main_size = BUFSIZE_USART6_SEND;
				}
				break;
#endif
		}
	
	 pu->cb.rec_buf  = (uint8_t *)malloc((pu->cb.rec_size)*sizeof(uint8_t));
	 pu->cb.send_buf = (uint8_t *)malloc((pu->cb.send_size)*sizeof(uint8_t));
	 pu->cb.main_buf = (uint8_t *)malloc((pu->cb.send_size)*sizeof(uint8_t));
}

TpVoid UsartGpioConfig(Usart* pu)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  
  switch(pu->index)
  {
#ifdef USART_1
    case USART_1:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_1_Tx, ENABLE);  /* Enable USART_1_Tx GPIO clock */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_1_Rx, ENABLE);  /* Enable USART_1_Rx GPIO clock */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      /* Enable USART1 clock */

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
    }
    break;
#endif				
#ifdef	USART_2
    case USART_2:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_2_Tx, ENABLE);  /* Enable USART_2_Tx GPIO clock */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_2_Rx, ENABLE);  /* Enable USART_2_Rx GPIO clock */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      /* Enable USART2 clock */

      GPIO_PinAFConfig(GPIO_USART_2_Tx, GPIO_PinSource_USART_2_Tx, GPIO_AF_USART2);	/* Connect GPIOxn to USART2_Tx */
      GPIO_PinAFConfig(GPIO_USART_2_Rx, GPIO_PinSource_USART_2_Rx, GPIO_AF_USART2);	/* Connect GPIOxn to USART2_Rx */

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_2_Tx;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_Init(GPIO_USART_2_Tx, &GPIO_InitStructure);
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_2_Rx;
      GPIO_Init(GPIO_USART_2_Rx, &GPIO_InitStructure);   
    }
    break;
		
#endif				
#ifdef	USART_3
    case USART_3:
				{
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_3_Tx, ENABLE);  /* Enable USART_2_Tx GPIO clock */
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_3_Rx, ENABLE);  /* Enable USART_2_Rx GPIO clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      /* Enable USART2 clock */

					GPIO_PinAFConfig(GPIO_USART_3_Tx, GPIO_PinSource_USART_3_Tx, GPIO_AF_USART3);	/* Connect GPIOxn to USART2_Tx */
					GPIO_PinAFConfig(GPIO_USART_3_Rx, GPIO_PinSource_USART_3_Rx, GPIO_AF_USART3);	/* Connect GPIOxn to USART2_Rx */

					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_3_Tx;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
					GPIO_Init(GPIO_USART_3_Tx, &GPIO_InitStructure);
					
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_3_Rx;
					GPIO_Init(GPIO_USART_3_Rx, &GPIO_InitStructure);  
				}
				break;
		
#endif				
#ifdef	USART_4
    case USART_4:
				{
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_4_Tx, ENABLE);  /* Enable USART_2_Tx GPIO clock */
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_4_Rx, ENABLE);  /* Enable USART_2_Rx GPIO clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);      /* Enable USART2 clock */

					GPIO_PinAFConfig(GPIO_USART_4_Tx, GPIO_PinSource_USART_4_Tx, GPIO_AF_UART4);	/* Connect GPIOxn to USART2_Tx */
					GPIO_PinAFConfig(GPIO_USART_4_Rx, GPIO_PinSource_USART_4_Rx, GPIO_AF_UART4);	/* Connect GPIOxn to USART2_Rx */

					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_4_Tx;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
					GPIO_Init(GPIO_USART_4_Tx, &GPIO_InitStructure);
					
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_4_Rx;
					GPIO_Init(GPIO_USART_4_Rx, &GPIO_InitStructure);  
				}
				break;
		
#endif				
#ifdef	USART_5
    case USART_5:
				{
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_5_Tx, ENABLE);  /* Enable USART_2_Tx GPIO clock */
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_5_Rx, ENABLE);  /* Enable USART_2_Rx GPIO clock */
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);      /* Enable USART2 clock */

					GPIO_PinAFConfig(GPIO_USART_5_Tx, GPIO_PinSource_USART_5_Tx, GPIO_AF_UART5);	/* Connect GPIOxn to USART2_Tx */
					GPIO_PinAFConfig(GPIO_USART_5_Rx, GPIO_PinSource_USART_5_Rx, GPIO_AF_UART5);	/* Connect GPIOxn to USART2_Rx */

					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_5_Tx;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
					GPIO_Init(GPIO_USART_5_Tx, &GPIO_InitStructure);
					
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_5_Rx;
					GPIO_Init(GPIO_USART_5_Rx, &GPIO_InitStructure); 
				}
				break;
		
#endif				
#ifdef	USART_6
    case USART_6:
				{
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_6_Tx, ENABLE);  /* Enable USART_6_Tx GPIO clock */
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_USART_6_Rx, ENABLE);  /* Enable USART_6_Rx GPIO clock */
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);      /* Enable USART6 clock */

					GPIO_PinAFConfig(GPIO_USART_6_Tx, GPIO_PinSource_USART_6_Tx, GPIO_AF_USART6);  /* Connect GPIOxn to USART6_Tx */
					GPIO_PinAFConfig(GPIO_USART_6_Rx, GPIO_PinSource_USART_6_Rx, GPIO_AF_USART6);  /* Connect GPIOxn to USART6_Rx */

					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_6_Tx;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
					GPIO_Init(GPIO_USART_6_Tx, &GPIO_InitStructure);
					
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_USART_6_Rx;
					GPIO_Init(GPIO_USART_6_Rx, &GPIO_InitStructure);   
				}
				break;
#endif
  }
}

TpVoid UsartDmaConfig(Usart* pu)
{ 
  DMA_InitTypeDef SendDMA_InitStructure;
  DMA_InitTypeDef RecDMA_InitStructure;
    
  SendDMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                 /* Data Memory to Peripheral */
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
  
   
  RecDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                 /* Data Peripheral to Memory */
  RecDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        /* Peripheral address does not increase */
  RecDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 /* Memory address increment */
  RecDMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; /* Peripheral data width of 8 bit */
  RecDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         /* Memory data width of 8 bit */
  RecDMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         /* Use Circular mode */
  RecDMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   /* Medium priority */
  RecDMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  RecDMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  RecDMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;             /* A single transmission burst memory */
  RecDMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  

  switch(pu->index)
  {
#ifdef USART_1
    case USART_1:
				{
					memcpy(&RecDMA_InitStructure_USART1,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART1,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
					
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
					DMA_DeInit(DMA2_Stream7);
					while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);

					SendDMA_InitStructure_USART1.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					SendDMA_InitStructure_USART1.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; 
					SendDMA_InitStructure_USART1.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
					SendDMA_InitStructure_USART1.DMA_BufferSize = 0;//pu->cb.send_size;                      /* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA2_Stream7, &SendDMA_InitStructure_USART1);
					DMA_Cmd(DMA2_Stream7, DISABLE);

					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
					DMA_DeInit(DMA2_Stream2);
					while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);
					RecDMA_InitStructure_USART1.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					RecDMA_InitStructure_USART1.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; 
					
					RecDMA_InitStructure_USART1.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART1.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA2_Stream2, &RecDMA_InitStructure_USART1);
					DMA_Cmd(DMA2_Stream2, ENABLE);     
				}
				break;
#endif				
#ifdef	USART_2
    case USART_2:
				{
					memcpy(&RecDMA_InitStructure_USART2,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART2,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
					
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream6);
					while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);

					SendDMA_InitStructure_USART2.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					SendDMA_InitStructure_USART2.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; 
					SendDMA_InitStructure_USART2.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
					SendDMA_InitStructure_USART2.DMA_BufferSize = 0;//pu->cb.send_size;                      /* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA1_Stream6, &SendDMA_InitStructure_USART2);
					DMA_Cmd(DMA1_Stream6, DISABLE);

					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream5);
					while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);
					RecDMA_InitStructure_USART2.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					RecDMA_InitStructure_USART2.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; 
					
					RecDMA_InitStructure_USART2.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART2.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA1_Stream5, &RecDMA_InitStructure_USART2);
					DMA_Cmd(DMA1_Stream5, ENABLE);     
				}
				break;
				
#endif				
#ifdef	USART_3
    case USART_3:
				{
					memcpy(&RecDMA_InitStructure_USART3,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART3,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
					
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream3);
					while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);

					SendDMA_InitStructure_USART3.DMA_Channel = DMA_Channel_4; /* Channel selection */
					SendDMA_InitStructure_USART3.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR; 
					SendDMA_InitStructure_USART3.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;
					SendDMA_InitStructure_USART3.DMA_BufferSize = 0;//pu->cb.send_size;/* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA1_Stream3, &SendDMA_InitStructure_USART3);
					DMA_Cmd(DMA1_Stream3, DISABLE);

					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream1);
					while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);
					RecDMA_InitStructure_USART3.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					RecDMA_InitStructure_USART3.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR; 
					
					RecDMA_InitStructure_USART3.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART3.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA1_Stream1, &RecDMA_InitStructure_USART3);
					DMA_Cmd(DMA1_Stream1, ENABLE);     
				}
				break;
				
#endif				
#ifdef	USART_4
    case USART_4:
				{
					memcpy(&RecDMA_InitStructure_USART4,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART4,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
					
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream4);
					while(DMA_GetCmdStatus(DMA1_Stream4) != DISABLE);

					SendDMA_InitStructure_USART4.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					SendDMA_InitStructure_USART4.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR; 
					SendDMA_InitStructure_USART4.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
					SendDMA_InitStructure_USART4.DMA_BufferSize = 0;//pu->cb.send_size;/* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA1_Stream4, &SendDMA_InitStructure_USART4);
					DMA_Cmd(DMA1_Stream4, DISABLE);

					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream2);
					while(DMA_GetCmdStatus(DMA1_Stream2) != DISABLE);
					RecDMA_InitStructure_USART4.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					RecDMA_InitStructure_USART4.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR; 
					
					RecDMA_InitStructure_USART4.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART4.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA1_Stream2, &RecDMA_InitStructure_USART4);
					DMA_Cmd(DMA1_Stream2, ENABLE);     
				}
				break;
				
#endif				
#ifdef	USART_5
    case USART_5:
				{
					memcpy(&RecDMA_InitStructure_USART5,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART5,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
					
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream7);
					while(DMA_GetCmdStatus(DMA1_Stream7) != DISABLE);

					SendDMA_InitStructure_USART5.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					SendDMA_InitStructure_USART5.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR; 
					SendDMA_InitStructure_USART5.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
					SendDMA_InitStructure_USART5.DMA_BufferSize = 0;//pu->cb.send_size;                      /* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA1_Stream7, &SendDMA_InitStructure_USART5);
					DMA_Cmd(DMA1_Stream7, DISABLE);

					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
					DMA_DeInit(DMA1_Stream0);
					while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);
					RecDMA_InitStructure_USART5.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
					RecDMA_InitStructure_USART5.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR; 
					
					RecDMA_InitStructure_USART5.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART5.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA1_Stream0, &RecDMA_InitStructure_USART5);
					DMA_Cmd(DMA1_Stream0, ENABLE);     
				}
				break;
#endif				
#ifdef	USART_6
    case USART_6:
				{		
					memcpy(&RecDMA_InitStructure_USART6,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
					memcpy(&SendDMA_InitStructure_USART6,&SendDMA_InitStructure,sizeof(RecDMA_InitStructure));
				
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
					DMA_DeInit(DMA2_Stream6);
					while(DMA_GetCmdStatus(DMA2_Stream6) != DISABLE);
					
					SendDMA_InitStructure_USART6.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
					SendDMA_InitStructure_USART6.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR; 
					SendDMA_InitStructure_USART6.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
					SendDMA_InitStructure_USART6.DMA_BufferSize = 0;//pu->cb.send_size;                      /* Specifies the DMA channel DMA buffer size */
								 
					DMA_Init(DMA2_Stream6, &SendDMA_InitStructure_USART6);
					DMA_Cmd(DMA2_Stream6, DISABLE);
				
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
					DMA_DeInit(DMA2_Stream1);
					while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
					RecDMA_InitStructure_USART6.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
					RecDMA_InitStructure_USART6.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR; 
					
					RecDMA_InitStructure_USART6.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
					RecDMA_InitStructure_USART6.DMA_BufferSize = pu->cb.rec_size;                      /* Specifies the DMA channel DMA buffer size */
			
					DMA_Init(DMA2_Stream1, &RecDMA_InitStructure_USART6);
					DMA_Cmd(DMA2_Stream1, ENABLE);  
				}
				break;
#endif 
  }

}


TpBool UsartSend(Usart* pu)
{
	TpBool result = INLIB_ERROR;
	TpUint16 tmp16 = 0;
	
	SendCom(pu);
	
	 switch(pu->index)
	 {
#ifdef USART_1
		 case USART_1:
     {
			 tmp16 = DMA_GetCurrDataCounter(DMA2_Stream7);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 }
			 if(pu->cb.send_pt)
			 {
			 	 DMA_DeInit(DMA2_Stream7);	
				 SendDMA_InitStructure_USART1.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA2_Stream7, &SendDMA_InitStructure_USART1);
				 DMA_Cmd(DMA2_Stream7, ENABLE);
			   pu->cb.send_pt = 0;				
			 }
		 
		 }
		 break;
#endif				
#ifdef	USART_2
		 case USART_2:
     {
			 tmp16 = DMA_GetCurrDataCounter(DMA1_Stream6);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 }
			 
			 if(pu->cb.send_pt)
			 {
				 
			 	 DMA_DeInit(DMA1_Stream6);	
				 SendDMA_InitStructure_USART2.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA1_Stream6, &SendDMA_InitStructure_USART2);
				 DMA_Cmd(DMA1_Stream6, ENABLE);
			   pu->cb.send_pt = 0;				
			 }
		 }
		 break;
#endif				
#ifdef	USART_3
		 case USART_3:
     {
			 tmp16 = DMA_GetCurrDataCounter(DMA1_Stream3);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 }
			 
			 if(pu->cb.send_pt)
			 {
			 	 DMA_DeInit(DMA1_Stream3);	
				 SendDMA_InitStructure_USART3.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA1_Stream3, &SendDMA_InitStructure_USART3);
				 DMA_Cmd(DMA1_Stream3, ENABLE);
			   pu->cb.send_pt = 0;				
			 }
		 }
		 break;
#endif				
#ifdef	USART_4
		 case USART_4:
     {
			 tmp16 = DMA_GetCurrDataCounter(DMA1_Stream4);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 }
			 
			 if(pu->cb.send_pt)
			 {
			 	 DMA_DeInit(DMA1_Stream4);	
				 SendDMA_InitStructure_USART4.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA1_Stream4, &SendDMA_InitStructure_USART4);
				 DMA_Cmd(DMA1_Stream4, ENABLE);
			   pu->cb.send_pt = 0;				
			 }
		 }
		 break;
#endif				
#ifdef	USART_5
		 case USART_5:
     {
			 tmp16 = DMA_GetCurrDataCounter(DMA1_Stream7);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 } 
			 if(pu->cb.send_pt)
			 {
			 	 DMA_DeInit(DMA1_Stream7);	
				 SendDMA_InitStructure_USART5.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA1_Stream7, &SendDMA_InitStructure_USART5);
				 DMA_Cmd(DMA1_Stream7, ENABLE);
			   pu->cb.send_pt = 0;				
			 }
		 }
		 break;
#endif				
#ifdef	USART_6
		 case USART_6:
     { 
			 tmp16 = DMA_GetCurrDataCounter(DMA2_Stream6);
			 if(tmp16)
			 {
			    pu->cb.send_lock = 1;
				  return result;
			 }
			 
			 if(pu->cb.send_pt)
			 {
			 	 DMA_DeInit(DMA2_Stream6);				 
				 SendDMA_InitStructure_USART6.DMA_BufferSize = pu->cb.send_pt;
				 DMA_Init(DMA2_Stream6, &SendDMA_InitStructure_USART6);
				 DMA_Cmd(DMA2_Stream6, ENABLE);
			   pu->cb.send_pt = 0;				
			 } 
		 }
		 break;
#endif
	 }
  result = INLIB_OK;
  return result;
}



TpVoid UsartParaConfig(Usart* pu,TpUint32 buadrate)
{	
	pu->cp.baud = buadrate;
	USART_InitTypeDef USART_InitStructure;	
	
	USART_InitStructure.USART_BaudRate = buadrate;// pu->cp.baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;	
  
  switch(pu->index)
  {
#ifdef USART_1
    case USART_1:
    {  
     	USART_Init(USART1, &USART_InitStructure); 
			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART1, ENABLE);   
    }
    break;
#endif				
#ifdef	USART_2
    case USART_2:
    {		
      USART_Init(USART2, &USART_InitStructure);
    
      USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART2, ENABLE);      
    }
    break;
#endif				
#ifdef	USART_3
    case USART_3:
    {		
      USART_Init(USART3, &USART_InitStructure);
    
      USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART3, ENABLE);      
    }
    break;
#endif				
#ifdef	USART_4
    case USART_4:
    {		
      USART_Init(UART4, &USART_InitStructure);
    
      USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);

      USART_Cmd(UART4, ENABLE);      
    }
    break;
#endif				
#ifdef	USART_5
    case USART_5:
    {		
      USART_Init(UART5, &USART_InitStructure);
    
      USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);

      USART_Cmd(UART5, ENABLE);      
    }
    break;
#endif				
#ifdef	USART_6
    case USART_6:
    {		
			USART_Init(USART6, &USART_InitStructure);
      USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART6, ENABLE);    
    }
    break; 
#endif
  }
}

TpVoid UsartRecEnable(Usart* pu)
{
	switch(pu->index)
	{
#ifdef USART_1
		case USART_1:			
				DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream2 transfer completion flag) */
				DMA_Cmd(DMA2_Stream2, DISABLE);
				while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);
				DMA_SetCurrDataCounter(DMA2_Stream2, pu->cb.rec_size);
				DMA_Cmd(DMA2_Stream2, ENABLE);			
				break;
#endif				
#ifdef	USART_2
		case USART_2:
				DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream6 transfer completion flag) */
				DMA_Cmd(DMA1_Stream5, DISABLE);
				while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);
				DMA_SetCurrDataCounter(DMA1_Stream5, pu->cb.rec_size);
				DMA_Cmd(DMA1_Stream5, ENABLE);
				break;
#endif				
#ifdef	USART_3
		case USART_3:
				DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream3 transfer completion flag) */
				DMA_Cmd(DMA1_Stream1, DISABLE);
				while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);
				DMA_SetCurrDataCounter(DMA1_Stream1, pu->cb.rec_size);
				DMA_Cmd(DMA1_Stream1, ENABLE);
				break;
#endif				
#ifdef	USART_4
		case USART_4:
				DMA_ClearFlag(DMA1_Stream2, DMA_FLAG_TCIF2);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream4 transfer completion flag) */
				DMA_Cmd(DMA1_Stream2, DISABLE);
				while(DMA_GetCmdStatus(DMA1_Stream2) != DISABLE);
				DMA_SetCurrDataCounter(DMA1_Stream2, pu->cb.rec_size);
				DMA_Cmd(DMA1_Stream2, ENABLE);
				break;	
#endif				
#ifdef	USART_5		
		case USART_5:
				DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream7 transfer completion flag) */
				DMA_Cmd(DMA1_Stream0, DISABLE);
				while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);
				DMA_SetCurrDataCounter(DMA1_Stream0, pu->cb.rec_size);
				DMA_Cmd(DMA1_Stream0, ENABLE);
				break;	
#endif				
#ifdef	USART_6		
		case USART_6:
				DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream6 transfer completion flag) */
				DMA_Cmd(DMA2_Stream1, DISABLE);
				while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
				DMA_SetCurrDataCounter(DMA2_Stream1, pu->cb.rec_size);
				DMA_Cmd(DMA2_Stream1, ENABLE);
				break;
#endif
	}
}

Usart* GetUsartAddress(TpUchar index)
{
    switch(index)
		{
#ifdef USART_1
			case USART_1:
			{
				return &usart1;
			}
#endif
#ifdef USART_2
			case USART_2:
			{
				return &usart2;
			}
#endif
#ifdef USART_3
			case USART_3:
			{
				return &usart3;
			}
#endif
#ifdef USART_4
			case USART_4:
			{
				return &usart4;
			}
#endif
#ifdef USART_5
			case USART_5:
			{
				return &usart5;
			}
#endif
#ifdef USART_6
			case USART_6:
			{
				return &usart6;
			}
#endif		
		}	
		return NULL;
}


TpUint32 GetUsartRxNum(TpUchar index)
{
	TpUint32 num = 0;
	
    switch(index)
		{
#ifdef USART_1
			case USART_1:
			{
				num = BUFSIZE_USART1_REC - DMA_GetCurrDataCounter(DMA2_Stream2);
				return num;
			}
#endif
#ifdef USART_2
			case USART_2:
			{
				num = BUFSIZE_USART2_REC - DMA_GetCurrDataCounter(DMA1_Stream5);
				return num;
			}
#endif
#ifdef USART_3
			case USART_3:
			{
				num = BUFSIZE_USART3_REC - DMA_GetCurrDataCounter(DMA1_Stream1);
				return num;
			}
#endif
#ifdef USART_4
			case USART_4:
			{
				num = BUFSIZE_USART4_REC - DMA_GetCurrDataCounter(DMA1_Stream2);
				return num;
			}
#endif
#ifdef USART_5
			case USART_5:
			{
				num = BUFSIZE_USART5_REC - DMA_GetCurrDataCounter(DMA1_Stream0);
				return num;
			}
#endif
#ifdef USART_6
			case USART_6:
			{
				num = BUFSIZE_USART6_REC - DMA_GetCurrDataCounter(DMA2_Stream1);
				return num;
			}
#endif		
		}	
		return NULL;
}


TpVoid UsartPushSendBuf(Usart* pu,TpUchar* pbuf,TpUint16 len)
{
  TpUint16 i;
	
  for(i=0;i<len;i++)
  {
    pu->cb.send_buf[pu->cb.send_pt] = pbuf[i];
		pu->cb.send_pt = (pu->cb.send_pt+1)%pu->cb.send_size;
  }
}


TpVoid UsartPushMainBuf(Usart* pu,TpUchar* pbuf,TpUint16 len)
{
  TpUint16 i;
	
  for(i=0;i<len;i++)
  {
    pu->cb.main_buf[pu->cb.main_pt] = pbuf[i];
		pu->cb.main_pt = (pu->cb.main_pt+1)%pu->cb.main_size;
  }

	pu->cb.main_lock = pu->cb.main_pt;
}

TpVoid SendCom(Usart* pu)
{
  TpUint16 j=0;

	if(pu->cb.main_lock)
	{
		for(j = 0;j<pu->cb.main_lock;j++)
		{
		   pu->cb.send_buf[pu->cb.send_pt] = pu->cb.main_buf[j];
			 pu->cb.send_pt = (pu->cb.send_pt+1)%pu->cb.send_size;
		}
		for(j=0;j<pu->cb.main_pt-pu->cb.main_lock;j++)
		{
			pu->cb.main_buf[j] = pu->cb.main_buf[pu->cb.main_lock+j];
		}
		pu->cb.main_pt = pu->cb.main_pt - pu->cb.main_lock;
		pu->cb.main_lock = 0;
	
	}
}

TpVoid UsartSendImmediately(Usart* pu,TpUchar* buff,TpUint16 length)
{
		UsartPushSendBuf(pu,buff,length);
		UsartSend(pu);	
}
