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
<<<<<<< HEAD
#include "gnss.h"
#include "RM3100.h"
#include "usart.h"
#include "flash.h"

//#include "Mag.h"
#include "math.h"


static InterruptRecFlag interrupt_rec_flag;

=======


TpUint16 u16NumUart1,u16NumUart2,u16NumUart6;  /* data num received  */
TpUchar PPS_flag = 0;
TpUchar PPS_index = 0;
TpUchar SendCycle = 0;
TpUchar BufSendNav[100] = {0};
TpUchar pps_ok = 0;
TpUchar pps_cnt = 0;
TpUchar pos_send_cnt = 0;

union
{
  TpUchar  chardata[2];
  TpUint16 idata;
}check_rec;
TpUint16 checkerror = 0;
uint16_t u16DebugCnt = 0;
uint32_t u32DebugTime = 0;
uint8_t u8DataSendARM2[100];   /* send data to arm2 */
uint8_t SendNavFlag = 0;
uint8_t flag_sendgnss = 0;
TpUint16 check_sum = 0;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

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
<<<<<<< HEAD
=======

    if(0==pps_ok&&pps_start)
    {
        pps_cnt++;
        if(5==pps_cnt)
        {
          pps_ok = 1;
        }
    }
    PPS_flag = 1;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
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
<<<<<<< HEAD
=======

	TpUint32 Data;
	
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) != RESET)
	{
		SPI1_CS1_HIGH();
		
<<<<<<< HEAD
		interrupt_rec_flag.rec_mag = 1;
		memcpy(interrupt_rec_flag.buff_mag,SPI1_Buffer_Rx,SPI1_RX_SIZE * 2);/*spi buff is Uint16*/
																																				/*so spi_size needs to multiply 2*/
			
=======
		Data = (SPI1_Buffer_Rx[0]&0x00FF)<<16;
		Data |= SPI1_Buffer_Rx[1];
		if(Data&0x00800000)
		{
			Data = Data|0xFF000000;
		}
		rm3100.mag_reg[0] = Data;
		
		Data = SPI1_Buffer_Rx[2]<<8;
		Data |= SPI1_Buffer_Rx[3]>>8;
		if(Data&0x00800000)
		{
			Data = Data|0xFF000000;
		}
		rm3100.mag_reg[1] = Data;
		
		Data = (SPI1_Buffer_Rx[3]&0x00FF)<<16;
		Data |= SPI1_Buffer_Rx[4];
		if(Data&0x00800000)
		{
			Data = Data|0xFF000000;
		}
		rm3100.mag_reg[2] = Data;
		
		RM3100_DataConversion(&rm3100);
		
		umiMagSend.head = 0x23AC;
		umiMagSend.magx = rm3100.mag[0];
    umiMagSend.magy = rm3100.mag[1];
    umiMagSend.magz = rm3100.mag[2];
		umiMagSend.check = CheckSumByte((uint8_t*)&umiMagSend, sizeof(umiMagSend));
    
    memset(BufSendNav,0,sizeof(umiMagSend));
    memcpy(BufSendNav,&umiMagSend,sizeof(umiMagSend));
    
    UsartPushSendBuf(&usart6,BufSendNav,sizeof(umiMagSend),0);
    UsartSend(&usart6);
	
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
	}
}

<<<<<<< HEAD
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
=======


void USART1_IRQHandler(void)
{
  uint8_t i = 0;
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
    
    DMA_Cmd(DMA2_Stream2,DISABLE);
    DMA_ClearFlag(DMA2_Stream2,DMA_FLAG_TEIF2|DMA_FLAG_TCIF2);

    u16NumUart1 = USART1->SR;
    u16NumUart1 = USART1->DR;
    u16NumUart1 = BUFSIZE_USART1-DMA_GetCurrDataCounter(DMA2_Stream2);
    DMA2_Stream2->NDTR = BUFSIZE_USART1;
      
    PackageRec(usart1.cb.rec_buf,u16NumUart1);
   
   if(flag_throughgps)
   {     
    UsartPushMainBuf(&usart2,usart1.cb.rec_buf,u16NumUart1);
	  UsartPushSendBuf(&usart2,usart1.cb.rec_buf,u16NumUart1,0);	 
    UsartSend(&usart2);
		
   }

    DMA_Cmd(DMA2_Stream2,ENABLE);

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	}
}


void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
   
<<<<<<< HEAD
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


=======
    DMA_Cmd(DMA1_Stream5,DISABLE);
    DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TEIF5|DMA_FLAG_TCIF5);

    u16NumUart2 = USART2->SR;
    u16NumUart2 = USART2->DR;
    u16NumUart2 = BUFSIZE_USART2-DMA_GetCurrDataCounter(DMA1_Stream5);
    DMA1_Stream5->NDTR = BUFSIZE_USART2;
		
		usart2.cb.rec_flag = 1;
    
		UsartDataDec(INDEX_USART2,usart2.cb.rec_buf,u16NumUart2);
  
		
	  DMA_Cmd(DMA1_Stream5,ENABLE);
		
	}
}

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
void USART6_IRQHandler(void)
{
	if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
<<<<<<< HEAD
		USART6->SR;
    USART6->DR;
		
		/* get rec num  */	
		interrupt_rec_flag.num_arm2 = BUFSIZE_USART6_REC-DMA_GetCurrDataCounter(DMA2_Stream1);
		memcpy(interrupt_rec_flag.buff_arm2,GetUsartAddress(USART_6)->cb.rec_buf,interrupt_rec_flag.num_arm2);
		/* set rec flag  */		
		interrupt_rec_flag.rec_arm2 = 1;
		UsartRecEnable(GetUsartAddress(USART_6));		
		
   }
}
=======
    DMA_Cmd(DMA2_Stream1,DISABLE);
    DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TEIF1|DMA_FLAG_TCIF1);

    u16NumUart6 = USART6->SR;
    u16NumUart6 = USART6->DR;
    u16NumUart6 = BUFSIZE_USART6-DMA_GetCurrDataCounter(DMA2_Stream1);
    DMA2_Stream1->NDTR = BUFSIZE_USART6;
		
		
		if(1==outmis_flag)
		{
			 UsartPushSendBuf(&usart2,usart6.cb.rec_buf,u16NumUart6,0);
//       UsartSend(&usart2,u16NumUart6);
			 UsartDataDec(INDEX_USART6,usart6.cb.rec_buf,u16NumUart6);
		}
		
    
    check_rec.chardata[0] = usart6.cb.rec_buf[u16NumUart6-2];
    check_rec.chardata[1] = usart6.cb.rec_buf[u16NumUart6-1];
		
    check_sum =  UmiCheckSum(usart6.cb.rec_buf,u16NumUart6);

		
    if(check_rec.idata!=check_sum)
    {
      checkerror++;
    }
      

    if((0xCD==usart6.cb.rec_buf[0])&&(0x34==usart6.cb.rec_buf[1])&&(check_sum==check_rec.idata))
    {
      memcpy(&st_UmiOutput,&usart6.cb.rec_buf,u16NumUart6);
				
      if(pps_ok)
      {      
        if(flag_sendgnss==0)
        {
          flag_sendgnss = 1;
          SendCycle = 0;
        }
         if(Cycle_100MS==SendCycle&&flag_sendgnss)
         {
             GnssCombine(&gnssout,&gnssrec);
             memset(&gnssrec,0,sizeof(gnssrec));
             SendCycle = 0;     
         }
         
     
      if(SendNavFlag==0&&st_UmiOutput.tow_imu%1000==0)
          SendNavFlag = 1;
      
       SendCycle++;
      
       }
			else
			{
			#ifdef UMI_SATCOM_FORMAT
			if(satComYawFlag.init_ok||satComYawFlag.update_ok)
       {   
			   SatComYawCombain(&gnssout,&satComYawFlag);
       }     
			#endif
			
			}
            
      if(LOG_MAXRATE*10==logtimer)
        logtimer = 0;
      LogProtocol(&logout,&st_UmiOutput);
           logtimer++;  
      
      if(SendNavFlag==1&&outflag.nav_out==1)
      {
         outflag.nav_out = 0;
         LogNav(&logout,&st_UmiOutput); 
      }

			pos_send_cnt++;
			
       if(outflag.bin_out==1)
      {
        outflag.bin_out = 0;
				LogSatComImu(&logout,&st_UmiOutput,&satComImuOut,&satComOverRange);
				
				
				
				if(pos_send_cnt==outrate.pos_rate)
				{ pos_send_cnt = 0;
			   	LogSatComPos(&logout,&st_UmiOutput,&satComPosOut);
				}
		
				
      }
			
			if(pos_send_cnt>100)
				pos_send_cnt = 0;
			
			
      
      if(SendNavFlag==1&&outflag.imu_out==1)
      {
         outflag.imu_out = 0;
         LogImu(&logout,&st_UmiOutput); 
      }
                
 
      if(SendNavFlag==1&&outflag.gnss_out==1&&st_UmiOutput.gnss.tow_pps>0)
				{
					 outflag.gnss_out = 0;
					 LogGnss(&logout,&st_UmiOutput); 
				}
			

      
#ifdef  DEBUG_MODE

   u16DebugCnt++;
   if(10==u16DebugCnt)
   {
     u16DebugCnt = 0;
     gnssout.head = 0x23AB;
     u32DebugTime = u32DebugTime+200;
     gnssout.time_utc = u32DebugTime;
     gnssout.week = 1905;
     gnssout.lat = 39.78308849;
     gnssout.lon = 116.51620747;
     gnssout.alt = 0.0;
     gnssout.heading = 100.0;
     gnssout.vg = 0.0;
     gnssout.flag = 33793;
     gnssout.hdop = 70;
     gnssout.orient = 0.0;  
     memset(u8DataSendARM2,0,sizeof(u8DataSendARM2));
     memcpy(u8DataSendARM2,&gnssout,sizeof(gnssout));
     gnssout.check = CheckSumByte(u8DataSendARM2,sizeof(gnssout));
     memcpy(u8DataSendARM2,&gnssout,sizeof(gnssout));
     
      UsartPushSendBuf(&usart6,u8DataSendARM2,sizeof(gnssout));
//      UsartSend(&usart6,sizeof(gnssout));

  }
  
#endif 
  }  
   
     }
   else
    {
       checkerror++;
    }
      
    
    DMA_Cmd(DMA2_Stream1,ENABLE);
	
}

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
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

<<<<<<< HEAD
InterruptRecFlag* GetInterruptRecFlag(TpVoid)
{
   return &interrupt_rec_flag;
}
=======
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
