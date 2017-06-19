/*============================================================================*/
/* Copyright (C), 2017, Yagro Co., Ltd.                                       */
/* File name:   main.c                                                        */
/* Date:        2017.4.19                                                     */
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

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

/**************test*************/
/**************test*************/
/**************test*************/
TpUint32 mag_collect_index;
/**************test*************/
/**************test*************/
/**************test*************/

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define  ADDR_APP_DEVIATION    ((TpUint32)0x10000)

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

extern UmiIgmBin pUmiOutput;

InterruptRecFlag* pInterrupt_rec_flag;

RM3100 rm3100_out;
MagSend stMagSend;
GnssOutPut gnss_out_data;


/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/
extern TpUchar Gnss_already_flag;

TpInt32 main(TpVoid)
{
	/* Application Programme Deviation */
  SCB->VTOR = FLASH_BASE|ADDR_APP_DEVIATION;

	/* Tim,Usart.. config*/
  HardWareInit();
	
	/* Create MagCaliOnline Instance */
	MagCaliInit();
	
	TpUchar mag_gnss_data_flag = 0;
	
	for(;;)
	{		
			/* usart rec data flag */
			pInterrupt_rec_flag = GetInterruptRecFlag();
			
	/*-------------------------------- decode gnss data ---------------------------------- */
			if(pInterrupt_rec_flag->rec_gnss)
			{
				pInterrupt_rec_flag->rec_gnss = 0;

				DecodeUblox(pInterrupt_rec_flag->buff_gnss,pInterrupt_rec_flag->num_gnss);
				PackGnssData(&gnss_out_data);
				gnss_out_data.check =  CheckSumByte((TpUchar*)&gnss_out_data,sizeof(gnss_out_data));	
			}
	/*------------------------------- decode user commond ------------------------------- */
			if(pInterrupt_rec_flag->rec_user)
			{
				pInterrupt_rec_flag->rec_user = 0;		
				
				DecodeCommond(pInterrupt_rec_flag->buff_user,pInterrupt_rec_flag->num_user);			
			}
	/*------------------------------- Send mag gnss data to ARM2 ------------------------------- */
			if(pInterrupt_rec_flag->rec_arm2)
			{
				pInterrupt_rec_flag->rec_arm2 = 0;
				
				if((Gnss_already_flag == 1)&&(gnss_out_data.head != 0))
				{
					UsartPushMainBuf(GetUsartAddress(USART_6),(TpUchar*)&gnss_out_data,sizeof(gnss_out_data));
					mag_gnss_data_flag |= 1<<1;
				}		
				if(stMagSend.head != 0)
				{
					UsartPushMainBuf(GetUsartAddress(USART_6),(TpUchar*)&stMagSend,sizeof(stMagSend));
					mag_gnss_data_flag |= 1<<2;
				}
						
				if(mag_gnss_data_flag != 0)
				{
					mag_gnss_data_flag = 0;
					UsartSend(GetUsartAddress(USART_6));
				}	
				
				memset(&stMagSend,0,sizeof(stMagSend));
				memset(&gnss_out_data,0,sizeof(gnss_out_data));
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
	 
			}			
	}
}


