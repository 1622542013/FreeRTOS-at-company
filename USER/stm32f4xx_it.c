/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    04-September-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <string.h>
#include "gnss.h"
#include "RM3100.h"
#include "usart.h"
#include "flash.h"

//#include "Mag.h"
#include "math.h"
#include "command.h"

static InterruptRecFlag interrupt_rec_flag;


/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

void EXTI2_IRQHandler(void)				   
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		SPI1_CS1_LOW();
		
		SPI1_Buffer_Tx[0] = RM3100_MX<<8;
		SPI1_Buffer_Tx[0] |= 0x80FF;
		SPI1_Buffer_Tx[1] = 0xFFFF;
		SPI1_Buffer_Tx[2] = 0xFFFF;
		SPI1_Buffer_Tx[3] = 0xFFFF;
		SPI1_Buffer_Tx[4] = 0xFFFF;
		
		SPI1_DMA_TX();
		
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) != RESET)
	{
		SPI1_CS1_HIGH();
		
		interrupt_rec_flag.rec_mag = 1;
		memcpy(interrupt_rec_flag.buff_mag,SPI1_Buffer_Rx,SPI1_RX_SIZE * 2);/*spi buff is Uint16*/
																																				/*so spi_size needs to multiply 2*/
			
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
    
    USART1->SR;
    USART1->DR;
		/* get rec num  */	
    interrupt_rec_flag.num_gnss = BUFSIZE_USART1_REC-DMA_GetCurrDataCounter(DMA2_Stream2);
		memcpy(interrupt_rec_flag.buff_gnss,GetUsartAddress(USART_1)->cb.rec_buf,interrupt_rec_flag.num_gnss);	
		/* set rec flag  */		
		interrupt_rec_flag.rec_gnss = 1;

		UsartRecEnable(GetUsartAddress(USART_1));			
	}
}


void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{ 
    USART2->SR;
    USART2->DR;

		/* get rec num  */	
    interrupt_rec_flag.num_user = BUFSIZE_USART2_REC-DMA_GetCurrDataCounter(DMA1_Stream5);	
		memcpy(interrupt_rec_flag.buff_user,GetUsartAddress(USART_2)->cb.rec_buf,interrupt_rec_flag.num_user);  
		/* set rec flag  */				
		interrupt_rec_flag.rec_user = 1;
		UsartRecEnable(GetUsartAddress(USART_2));	

	
	}
}

UmiIgmBin pUmiOutput;
void USART6_IRQHandler(void)
{
	int num = 0;
	
	if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
		USART6->SR;
    USART6->DR;
				
		interrupt_rec_flag.rec_arm2 = 1;
		
		/* get rec num  */		
		num = GetUsartRxNum(USART_6);	

		
		DecodeARM2Bin(GetUsartAddress(USART_6)->cb.rec_buf,num,&pUmiOutput);
		
			
		UsartSend(GetUsartAddress(USART_2));
		
		UsartRecEnable(GetUsartAddress(USART_6));		
			
   }
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

InterruptRecFlag* GetInterruptRecFlag(TpVoid)
{
   return &interrupt_rec_flag;
}
