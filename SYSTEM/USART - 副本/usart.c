/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   USART.c                                                       */
/* Date:        2016.12.07                                                    */
/* Description: config USART                                                  */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/
#include <string.h>
#include <stdlib.h>
#include "usart.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

Usart usart1;
Usart usart2;
Usart usart6;

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

TpBool UsartConfig(Usart* pu,TpUchar index,TpUint32 baudrate)
{
  TpBool resutlt = INLIB_ERROR;
  
  pu->index = index;
 
  UsartComBufConfig(pu);
  UsartGpioConfig(pu);
  UsartParaConfig(pu,baudrate);
  UsartDmaConfig(pu);
  
  resutlt = INLIB_OK;
  return resutlt;
}

TpBool UsartComBufConfig(Usart* pu)
{
  TpBool resutlt = INLIB_ERROR;
  
	switch(pu->index)
	{  
		case INDEX_USART1:
		default:
		{
			pu->cb.rec_size  = BUFSIZE_USART1;
		 	pu->cb.send_size = BUFSIZE_USART1;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			memset(pu->cb.send_buf,0,BUFSIZE_USART1);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART1);
      pu->cb.flag_block = 1;			
			
			pu->mb.num_lock = 0;
			pu->mb.bufsize_main = BUFSIZE_USART1;
			memset(pu->mb.send_buf,0,BUFSIZE_USART1);
			pu->mb.send_pt = 0;			
		}
		break;
		case INDEX_USART2:
		{	
			pu->cb.rec_size  = BUFSIZE_USART2;
		 	pu->cb.send_size = BUFSIZE_USART2;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			pu->cb.flag_block = 1;	
			memset(pu->cb.send_buf,0,BUFSIZE_USART2);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART2);		
				
			pu->mb.num_lock = 0;
			pu->mb.bufsize_main = BUFSIZE_USART2;
			memset(pu->mb.send_buf,0,BUFSIZE_USART2);
			pu->mb.send_pt = 0;			
		}
		break;
		case INDEX_USART3:
		{	
			pu->cb.rec_size  = BUFSIZE_USART3;
		 	pu->cb.send_size = BUFSIZE_USART3;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			memset(pu->cb.send_buf,0,BUFSIZE_USART3);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART3);			
		}
		break;
		case INDEX_USART4:
		{	
			pu->cb.rec_size  = BUFSIZE_USART4;
		 	pu->cb.send_size = BUFSIZE_USART4;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			memset(pu->cb.send_buf,0,BUFSIZE_USART4);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART4);			
		}
		break;
		case INDEX_USART5:
		{	
			pu->cb.rec_size  = BUFSIZE_USART5;
		 	pu->cb.send_size = BUFSIZE_USART5;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			memset(pu->cb.send_buf,0,BUFSIZE_USART5);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART5);			
		}
		break;
	  case INDEX_USART6:
		{	
			pu->cb.rec_size  = BUFSIZE_USART6;
		 	pu->cb.send_size = BUFSIZE_USART6;
			pu->cb.rec_pt = 0;
			pu->cb.send_pt = 0;
			memset(pu->cb.send_buf,0,BUFSIZE_USART6);
			memset(pu->cb.rec_buf,0,BUFSIZE_USART6);			
		}
		break;
	}

  
  resutlt = INLIB_OK;
  return resutlt;
}

TpBool UsartGpioConfig(Usart* pu)
{
  TpBool resutlt = INLIB_ERROR;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  switch(pu->index)
  {
    case INDEX_USART1:
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
    case INDEX_USART2:
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
    case INDEX_USART6:
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
  }
  
  resutlt = INLIB_OK;
  return resutlt;

}

TpBool UsartDmaConfig(Usart* pu)
{
  TpBool resutlt = INLIB_ERROR;
  
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
    case INDEX_USART1:
    {
			pu->DMA_SentStream = DMA2_Stream7;
			pu->DMA_RecStream = DMA2_Stream2;
			
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
      DMA_DeInit(DMA2_Stream7);
      while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);

      SendDMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
      SendDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; 
      SendDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
      SendDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART1;                      /* Specifies the DMA channel DMA buffer size */
             
      DMA_Init(DMA2_Stream7, &SendDMA_InitStructure);
	  	DMA_Cmd(DMA2_Stream7, DISABLE);

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
      DMA_DeInit(DMA2_Stream2);
      while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);
      RecDMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
      RecDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; 
      
      RecDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
      RecDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART1;                      /* Specifies the DMA channel DMA buffer size */
  
      DMA_Init(DMA2_Stream2, &RecDMA_InitStructure);
      DMA_Cmd(DMA2_Stream2, ENABLE);     
   
    }
    break;
    case INDEX_USART2:
    {
			pu->DMA_SentStream = DMA1_Stream6;
			pu->DMA_RecStream = DMA1_Stream5;
					
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
      DMA_DeInit(DMA1_Stream6);
      while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);

      SendDMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
      SendDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; 
      SendDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
      SendDMA_InitStructure.DMA_BufferSize = 0;                      /* Specifies the DMA channel DMA buffer size */
             
      DMA_Init(DMA1_Stream6, &SendDMA_InitStructure);
	  	DMA_Cmd(DMA1_Stream6, DISABLE);

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
      DMA_DeInit(DMA1_Stream5);
      while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);
      RecDMA_InitStructure.DMA_Channel = DMA_Channel_4;                    /* Channel selection */
      RecDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; 
      
      RecDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
      RecDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART2;                      /* Specifies the DMA channel DMA buffer size */
  
      DMA_Init(DMA1_Stream5, &RecDMA_InitStructure);
      DMA_Cmd(DMA1_Stream5, ENABLE);     
			
			memcpy(&pu->SentDMA_InitStructure,&SendDMA_InitStructure,sizeof(SendDMA_InitStructure));
			memcpy(&pu->RecDMA_InitStructure,&RecDMA_InitStructure,sizeof(RecDMA_InitStructure));
   
    }
    break;
    case INDEX_USART6:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
      DMA_DeInit(DMA2_Stream6);
      while(DMA_GetCmdStatus(DMA2_Stream6) != DISABLE);

      SendDMA_InitStructure.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
      SendDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR; 
      SendDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.send_buf;//(uint32_t)USART2_Buffer_Tx;            /* Memory address */
      SendDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART6;                      /* Specifies the DMA channel DMA buffer size */
             
      DMA_Init(DMA2_Stream6, &SendDMA_InitStructure);
	  	DMA_Cmd(DMA2_Stream6, DISABLE);

      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
      DMA_DeInit(DMA2_Stream1);
      while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
      RecDMA_InitStructure.DMA_Channel = DMA_Channel_5;                    /* Channel selection */
      RecDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR; 
      
      RecDMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pu->cb.rec_buf;            /* Memory address */
      RecDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART6;                      /* Specifies the DMA channel DMA buffer size */
  
      DMA_Init(DMA2_Stream1, &RecDMA_InitStructure);
      DMA_Cmd(DMA2_Stream1, ENABLE);     
   
    }
    break;
  
  }
  
  resutlt = INLIB_OK;
  return resutlt;
}


TpVoid UsartUblox(TpVoid)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  DMA_InitTypeDef SendDMA_InitStructure;
  
  usart1.index = 1;
  UsartComBufConfig(&usart1);

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
	SendDMA_InitStructure.DMA_BufferSize = BUFSIZE_USART1;                      /* Specifies the DMA channel DMA buffer size */
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

  DMA_Init(DMA2_Stream7, &SendDMA_InitStructure);
  DMA_Cmd(DMA2_Stream7, DISABLE);

}

//TpBool UsartSendBuf(Usart* pu,TpUint16 len)
//{
//  TpBool resutlt = INLIB_ERROR;
//  
//  switch(pu->index)
//  {
//    case INDEX_USART1:
//    {
//      DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);  /* Clear Pending DMA channel x flag (DMA2 Stream7 transfer completion flag) */
//      DMA_Cmd(DMA2_Stream7, DISABLE);
//      while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);
//      DMA_SetCurrDataCounter(DMA2_Stream7, len);
//      DMA_Cmd(DMA2_Stream7, ENABLE);    
//    }
//    break;
//    case INDEX_USART2:
//    {
//      DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);  /* Clear Pending DMA channel x flag (DMA1 DMA1_Stream6 transfer completion flag) */
//      DMA_Cmd(DMA1_Stream6, DISABLE);
//      while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);
//      DMA_SetCurrDataCounter(DMA1_Stream6, len);
//      DMA_Cmd(DMA1_Stream6, ENABLE);   
//    }
//    break;
//    case INDEX_USART6:
//    {
//      DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_TCIF6);  /* Clear Pending DMA channel x flag (DMA2 DMA2_Stream6 transfer completion flag) */
//      DMA_Cmd(DMA2_Stream6, DISABLE);
//      while(DMA_GetCmdStatus(DMA2_Stream6) != DISABLE);
//      DMA_SetCurrDataCounter(DMA2_Stream6, len);
//      DMA_Cmd(DMA2_Stream6, ENABLE);
//    }
//    break;
//  
//  }
//  
//  resutlt = INLIB_OK;
//  return resutlt;
//}

TpBool UsartPushBuf(Usart* pu,TpUchar* pbuf,TpUint16 len,TpUint16 index)
{
  TpBool resutlt = INLIB_ERROR;

  TpUint16 i;
  for(i=0;i<len;i++)
  {
    pu->cb.send_buf[i+index] = pbuf[i];
  }
  
	pu->cb.send_pt = index+len;
		
  resutlt = INLIB_OK;
  return resutlt;
}

TpBool UsartParaConfig(Usart* pu,TpUint32 buadrate)
{
	TpBool resutlt = INLIB_ERROR;
	
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
    case INDEX_USART1:
    {  
     	USART_Init(USART1, &USART_InitStructure); 
			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART1, ENABLE);   
    }
    break;
    case INDEX_USART2:
    {

			
      USART_Init(USART2, &USART_InitStructure);
    
      USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART2, ENABLE);      
    }
    break;
    case INDEX_USART6:
    {

			
			USART_Init(USART6, &USART_InitStructure);
      USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
      USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
      USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);

      USART_Cmd(USART6, ENABLE);  
    
    }
    break;
  
  }
  
	 resutlt = INLIB_OK;
   return resutlt;
}


TpBool UsartPushMainBuf(Usart* pu,TpUchar* pbuf,TpUint16 num)
{
	TpBool resutlt = INLIB_ERROR;
  TpUint16 i = 0;
	for(i=0;i<num;i++)
	{
	  pu->mb.send_buf[pu->mb.send_pt] = pbuf[i];
	  pu->mb.send_pt = (pu->mb.send_pt+1)%pu->mb.bufsize_main;
	}
	pu->mb.num_lock = pu->mb.send_pt;
	
	resutlt = INLIB_OK;
  return resutlt;
}

TpBool UsartSendBuf(Usart* pu)
{
	TpBool resutlt = INLIB_ERROR;
	TpUint16 num = 0;
	
	UsartSendMainBuf(pu);
	num  = DMA_GetCurrDataCounter(pu->DMA_SentStream);
	
	if(num)
	{
	  pu->cb.flag_block = 1;
    return 0;		
	}
	if(pu->cb.send_pt)
	{
	 	DMA_DeInit(pu->DMA_SentStream);
		pu->SentDMA_InitStructure.DMA_BufferSize = pu->cb.send_pt;
		DMA_Init(pu->DMA_SentStream, &pu->SentDMA_InitStructure);
		DMA_Cmd(pu->DMA_SentStream, ENABLE);
		pu->cb.send_pt = 0;
	
	}
	
	resutlt = INLIB_OK;
  return resutlt;

}

TpBool UsartSendMainBuf(Usart* pu)
{
	TpBool resutlt = INLIB_ERROR;
	TpUint16 i = 0;
	/* main buf send */
	if(pu->mb.num_lock)
	{
		/* add main buf data */
		for(i = 0;i < pu->mb.num_lock;i++)
		{
			pu->cb.send_buf[pu->cb.send_pt] = pu->mb.send_buf[i];
			pu->cb.send_pt = (pu->cb.send_pt+1)%pu->cb.send_size;
		}
		
	/* set main buf to zero */
	  for(i = 0;i<(pu->mb.send_pt-pu->mb.num_lock);i++)
		{
			pu->mb.send_buf[i] = pu->mb.send_buf[pu->mb.num_lock+i];
			
		}
		pu->mb.send_pt-=pu->mb.num_lock;
		pu->mb.num_lock = 0;
	}
	
	resutlt = INLIB_OK;
  return resutlt;


}

