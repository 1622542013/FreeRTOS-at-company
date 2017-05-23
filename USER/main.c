/*============================================================================*/
<<<<<<< HEAD
/* Copyright (C), 2017, Yagro Co., Ltd.                                       */
/* File name:   main.c                                                        */
/* Date:        2017.4.19                                                     */
=======
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   main.c                                                        */
/* Date:        2016.11.29                                                    */
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/
<<<<<<< HEAD

#include "config.h"
#include "gnss.h"
#include "RM3100.h"
#include "stm32f4xx_it.h"
#include "command.h"
#include "SPI1.h"
#include "Decode_Ublox.h"
#include "MagCali.h"
#include "flash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define  ADDR_APP_DEVIATION    ((TpUint32)0x10000)

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

UmiIgmBin pUmiOutput;

InterruptRecFlag* pInterrupt_rec_flag;

RM3100 rm3100_out;
MagSend stMagSend;
GnssOutPut gnss_out_data;

/* magcali  */
unsigned char state_mag = 0;
EllipFittingResult ell_result;
TpUchar  mag_result = 0;

=======
#include "stm32f4xx.h"
#include "config.h"
#include "gnss.h"
#include "protocol.h"
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/
<<<<<<< HEAD
extern TpUchar Gnss_not_already_flag;
int count = 0;
TpInt32 num;
TpInt32 main(TpVoid)
{
	/* Application Programme Deviation */
  SCB->VTOR = FLASH_BASE|ADDR_APP_DEVIATION;

	/* Tim,Usart.. config*/
  HardWareInit();
	
	/* Create MagCaliOnline Instance */
	MagCaliInit();
	
	for(;;)
	{
		mag_result = MagCaliOnline(&state_mag,&ell_result);
		if(mag_result)
		{
		   OutMagCaliOnlinePara(ell_result.center0,ell_result.D0m_inv);
			 SetMagCaliParaBias(ell_result.center0);
			 SetMagCaliParaMatrix(ell_result.D0m_inv);
		}
		
		/* usart rec data flag */
		pInterrupt_rec_flag = GetInterruptRecFlag();
		
/*-------------------------------- decode gnss data ---------------------------------- */
		if(pInterrupt_rec_flag->rec_gnss)
		{
			pInterrupt_rec_flag->rec_gnss = 0;

			DecodeUblox(pInterrupt_rec_flag->buff_gnss,pInterrupt_rec_flag->num_gnss);
			PackGnssData(&gnss_out_data);
			gnss_out_data.check =  CheckSumByte((TpUchar*)&gnss_out_data,sizeof(gnss_out_data));
			
			if(Gnss_not_already_flag == 0)
			{
				UsartPushMainBuf(GetUsartAddress(USART_6),(TpUchar*)&gnss_out_data,sizeof(gnss_out_data));
			}
		}
/*------------------------------- decode user commond ------------------------------- */
		if(pInterrupt_rec_flag->rec_user)
		{
			pInterrupt_rec_flag->rec_user = 0;		
			
			DecodeCommond(pInterrupt_rec_flag->buff_user,pInterrupt_rec_flag->num_user);			
		}
/*------------------------------- decode ARM2 data ------------------------------- */
		if(pInterrupt_rec_flag->rec_arm2)
		{
			pInterrupt_rec_flag->rec_arm2 = 0;
			
			DecodeARM2Bin(pInterrupt_rec_flag->buff_arm2,pInterrupt_rec_flag->num_arm2,&pUmiOutput);
			UsartSend(GetUsartAddress(USART_2));
		}
/*------------------------------ decode MAG data ------------------------------- */
		if(pInterrupt_rec_flag->rec_mag)
		{
			pInterrupt_rec_flag->rec_mag = 0;
			DecodeMagData(pInterrupt_rec_flag->buff_mag,&rm3100_out);
			
			stMagSend.head  = 0x45ab;
			stMagSend.magx  = rm3100_out.magx;
			stMagSend.magy  = rm3100_out.magy;
			stMagSend.magz  = rm3100_out.magz;
			
			stMagSend.check = CheckSumByte((TpUchar*)&stMagSend,sizeof(stMagSend));
			UsartPushMainBuf(GetUsartAddress(USART_6),(TpUchar*)&stMagSend,sizeof(stMagSend));
			UsartSend(GetUsartAddress(USART_6));	
			
					 /* MagCali online */
		 if(GetCommondFlag()->magcali_online)
		 {
        CheckMagCaliOk(&stMagCaliFlag,&pUmiOutput,&rm3100_out,&mea_in);
		 }	
		}
	}
}


=======

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
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
