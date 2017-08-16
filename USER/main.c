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
#include "flash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************** mag cali online use ***************************/
#include "MagCaliOnline.h"

/********** mag cali online use  ************/

float acc[3] = {0.0f};
float gyo[3] = {0.0f};
float mag[3] = {0.0f};
float att0[3] = {0.0f};
float att[3] = {0.0f};


float bias[3],k_matrix[9];

unsigned char outputPara[200];
unsigned short int len = 0;
unsigned char out_para = 0;

float eular[3] = {0.0f};
float quat[4]  = {0.0f};
unsigned char flag_cali = 0;
/*******************************************/

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define  ADDR_APP_DEVIATION    ((TpUint32)0x10000)

/*============================================================================*/
/*                              valu data				                              */
/*============================================================================*/

extern UmiIgmBin pUmiOutput;
RM3100 rm3100_out;
MagSend stMagSend;
GnssOutPut gnss_out_data;

/*============================================================================*/
/*                              flag						                              */
/*============================================================================*/
InterruptRecFlag* pInterrupt_rec_flag;
CommondFlag* pCommondFlag;
extern TpUchar Gnss_already_flag;/*gnss*/


/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

void MagCalibration(void);
void MagCaliStart(void);

TpInt32 main(TpVoid)
{
	/* Application Programme Deviation */
  SCB->VTOR = FLASH_BASE|ADDR_APP_DEVIATION;

	/* Tim,Usart.. config*/
  HardWareInit();
		
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

				MagCaliStart();
			
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
				
				// acc
				acc[0] = pUmiOutput.imu.accx;
				acc[1] = pUmiOutput.imu.accy;
				acc[2] = pUmiOutput.imu.accz;
				// gyo
				gyo[0] = pUmiOutput.imu.gyox;
				gyo[1] = pUmiOutput.imu.gyoy;
				gyo[2] = pUmiOutput.imu.gyoz;

				
				eular[0] = pUmiOutput.nav.pitch;
				eular[1] = pUmiOutput.nav.roll;
				eular[2] = pUmiOutput.nav.heading;
				
				quat[0] = pUmiOutput.nav.quat[0];
				quat[1] = pUmiOutput.nav.quat[1];
				quat[2] = pUmiOutput.nav.quat[2];
				quat[3] = pUmiOutput.nav.quat[3];			
			}
	/*------------------------------ decode MAG data ------------------------------- */
			if(pInterrupt_rec_flag->rec_mag)
			{
				pInterrupt_rec_flag->rec_mag = 0;
				DecodeMagData(pInterrupt_rec_flag->buff_mag,&rm3100_out);
				
				stMagSend.head  = 0x45ab;
				stMagSend.magx  = rm3100_out.cal_magx;
				stMagSend.magy  = rm3100_out.cal_magy;
				stMagSend.magz  = rm3100_out.cal_magz;
				
				stMagSend.check = CheckSumByte((TpUchar*)&stMagSend,sizeof(stMagSend));
				
				/***************** mag cali online use *********************/
							
				// mag
				mag[0] = rm3100_out.cal_magx;
				mag[1] = rm3100_out.cal_magy;
				mag[2] = rm3100_out.cal_magz;

				MagCalibration(); 
			}			
	}
}

void MagCaliStart(void)
{
		pCommondFlag = GetCommondFlag();
	
		if(pCommondFlag->magcali_online)
		{
			 pCommondFlag->magcali_online = 0;
			
			 flag_cali = 1;
			 StartMagCali();
			
		}	
}

void MagCalibration(void)
{
		if(flag_cali)
		{
				
				if(!CheckCaliInitDone())
				{
					 MagCaliOnlineInit(pUmiOutput.index,gyo,acc,&stAhrsOut);
				}
				else
				{
						  MagCaliOnline(&stAhrsOut,gyo,acc,mag,0.01);
					 	  GetEuler(&stAhrsOut,eular);
				    	GetQuat(&stAhrsOut,quat);
					
							if(!CheckMagSampleDone())
							{
								 FindAppropriateMag(&stAhrsOut,mag);
							}
							else
							{						
									if(0==out_para)
									{
											out_para = 1;
											if(CheckEllipFittingOk())
											{
												flag_cali = 0;
												GetEllipFittingPara(bias,k_matrix);
												
                        MagMatrixNewCalc(bias,k_matrix);
                        		
											  len = snprintf((char*)outputPara,200,"Mag Calibration succeed !!!\r\n");
												UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)outputPara,(TpUint16)len);
												out_para = 0;										
											}
											else
											{
												flag_cali = 0;
												
												len = snprintf((char*)outputPara,200,"Mag Calibration failed !!!\r\n");
												UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)outputPara,(TpUint16)len);	
												out_para = 0;
											
											}
									}
								
							}
				
				}

		}
}


