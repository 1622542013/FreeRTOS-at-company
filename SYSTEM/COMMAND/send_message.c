#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "send_message.h"
#include "command_bin.h"
#include "command.h"
#include "flash.h"

TpVoid LogOutput(UmiIgmBin* pUmiOutput)
{
	TpUint16 ratio = 0;
	TpUint16 index = 0;
	
	/* ascii out */
	index = GetOutputFormat(IMU_ASCII);
	if(index)
	{
	   ratio = BENCHMARK_FREQ /index;
		 if(pUmiOutput->index%ratio==0)
		 {
		   LogImuAscii(pUmiOutput);
		 }	
	}
	
	/* ahrs ascii  */
	index = 0;
	index = GetOutputFormat(AHRS_ASCII);
	if(index)
	{
	   ratio = BENCHMARK_FREQ /index;
		 if(pUmiOutput->index%ratio==0)
		 {
		    LogAhrsAscii(pUmiOutput);
		 }	
	}
  
	/* ahrs bin  */
	index = 0;
	index = GetOutputFormat(AHRS_BIN);
	if(index)
	{
	   ratio = BENCHMARK_FREQ /index;
		 if(pUmiOutput->index%ratio==0)
		 {
		    LogAhrsBin(pUmiOutput);
		 }	
	}
 	

	/* igm ascii  */
	index = 0;
	index = GetOutputFormat(IGM_ASCII);
	if(index)
	{
	   ratio = BENCHMARK_FREQ /index;
		 if(pUmiOutput->index%ratio==0)
		 {	  
		    LogIgmAscii(pUmiOutput);
		 }	
	}
	/* igm bin  */
	index = 0;
	index = GetOutputFormat(IGM_BIN);
	if(index)
	{
		
	   ratio = BENCHMARK_FREQ /index;
		 if(pUmiOutput->index%ratio==0)
		 {
		    LogIgmBin(pUmiOutput);
		 }	
	}
	
}

uint8_t imu_data_buff[512];

TpVoid LogImuAscii(UmiIgmBin* pUmiOutput)
{
	TpUchar len = 0;
	float Acc_Temp  = (float)pUmiOutput->imu.acc_temp / 16.0f;
	float Gyro_temp = (float)pUmiOutput->imu.gyo_temp / 16.0f;
	float Bmp_Temp  = (float)pUmiOutput->imu.bmp_temp / 16.0f;

	len = snprintf((char*)imu_data_buff,200,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",
		      OUTPUT_ID_IMU_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,
					pUmiOutput->imu.gyox,pUmiOutput->imu.gyoy,pUmiOutput->imu.gyoz,
					pUmiOutput->imu.accx,pUmiOutput->imu.accy,pUmiOutput->imu.accz,
					pUmiOutput->mag.magx,pUmiOutput->mag.magy,pUmiOutput->mag.magz,
					Gyro_temp,Acc_Temp,Bmp_Temp);
	
  UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)imu_data_buff,(TpUint16)len);
}

TpVoid LogAhrsAscii(UmiIgmBin* pUmiOutput)
{
	TpUchar len = 0;

	len = snprintf((char*)imu_data_buff,200,"%d,%d,%d,%f,%f,%f\r\n",OUTPUT_ID_AHRS_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,
																	pUmiOutput->nav.heading,pUmiOutput->nav.roll,pUmiOutput->nav.pitch);
	
  UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)imu_data_buff,(TpUint16)len);
}

TpVoid LogAhrsBin(UmiIgmBin* pUmiOutput)
{
		UmiAhrsBin ahrs_bin;
	
		float Acc_Temp  = (float)pUmiOutput->imu.acc_temp / 16.0f;
		float Gyro_temp = (float)pUmiOutput->imu.gyo_temp / 16.0f;
		float Bmp_Temp  = (float)pUmiOutput->imu.bmp_temp / 16.0f;
	
	
	  ahrs_bin.head  = DATA_FROM_ARM2_HEAD;
		ahrs_bin.index = pUmiOutput->index;
	
		ahrs_bin.mag_id = OUTPUT_ID_AHRS_BIN;
	
		ahrs_bin.tow_imu = pUmiOutput->tow_imu;
	
		ahrs_bin.gyox = pUmiOutput->imu.gyox;
		ahrs_bin.gyoy = pUmiOutput->imu.gyoy;
		ahrs_bin.gyoz = pUmiOutput->imu.gyoz;
	
		ahrs_bin.accx = pUmiOutput->imu.accx;
		ahrs_bin.accy = pUmiOutput->imu.accy;
		ahrs_bin.accz = pUmiOutput->imu.accz;

		ahrs_bin.magx = pUmiOutput->mag.magx;
		ahrs_bin.magy = pUmiOutput->mag.magy;
		ahrs_bin.magz = pUmiOutput->mag.magz;
	
		ahrs_bin.temp_gyo = pUmiOutput->imu.gyo_temp;
		ahrs_bin.temp_acc = pUmiOutput->imu.acc_temp;
		ahrs_bin.temp_mag = 0.0;//pUmiOutput->imu.tmpx;
		
		ahrs_bin.quat[0] = 0.0;
		ahrs_bin.quat[1] = 0.0;
		ahrs_bin.quat[2] = 0.0;
		ahrs_bin.quat[3] = 0.0;
		
		ahrs_bin.check = CheckSumByte((TpUchar*)&ahrs_bin,sizeof(ahrs_bin));
		ahrs_bin.end = 0xFE;
		
		UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)&ahrs_bin,sizeof(ahrs_bin));	
}


TpVoid LogIgmAscii(UmiIgmBin* pUmiOutput)
{
	TpUchar len = 0;
	float Acc_Temp  = (float)pUmiOutput->imu.acc_temp / 16.0f;
	float Gyro_temp = (float)pUmiOutput->imu.gyo_temp / 16.0f;
	float Bmp_Temp  = (float)pUmiOutput->imu.bmp_temp / 16.0f;

//	len = snprintf((char*)imu_data_buff,512,"%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%.10f,%.10f,%f,%d\r\n",
//		      OUTPUT_ID_IGM_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,pUmiOutput->week,
//					pUmiOutput->imu.gyox,pUmiOutput->imu.gyoy,pUmiOutput->imu.gyoz,
//					pUmiOutput->imu.accx,pUmiOutput->imu.accy,pUmiOutput->imu.accz,
//					pUmiOutput->mag.magx,pUmiOutput->mag.magy,pUmiOutput->mag.magz,
//	        Gyro_temp,Acc_Temp,Bmp_Temp,
//					pUmiOutput->gnss.weekn,pUmiOutput->gnss.tow_pps,pUmiOutput->gnss.lat,pUmiOutput->gnss.lon,
//	        pUmiOutput->gnss.alt,pUmiOutput->gnss.hdop
//					);
	
		len = snprintf((char*)imu_data_buff,512,"%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%.10f,%.10f\r\n",
		      OUTPUT_ID_IGM_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,pUmiOutput->week,
					pUmiOutput->imu.gyox,pUmiOutput->imu.gyoy,pUmiOutput->imu.gyoz,
					pUmiOutput->imu.accx,pUmiOutput->imu.accy,pUmiOutput->imu.accz,
					pUmiOutput->mag.magx,pUmiOutput->mag.magy,pUmiOutput->mag.magz,
					pUmiOutput->gnss.lat,pUmiOutput->gnss.lon
					);
	
  UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)imu_data_buff,(TpUint16)len);
}

TpVoid LogIgmBin(UmiIgmBin* pUmiOutput)
{
	UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)pUmiOutput,sizeof(UmiIgmBin));	
}

TpChar send_buff[512];
TpVoid AccCalPara(Commond_ACC_GYRO_PARA* acc_para)
{
	 TpUint16 out_len;
		
	 out_len = snprintf(send_buff,512,ACC_CAL_PARA_OUT,\
	 acc_para->ks0[0],acc_para->ks0[1],acc_para->ks0[2],
	 acc_para->ks1[0],acc_para->ks1[1],acc_para->ks1[2],
	 acc_para->kz0[0],acc_para->kz0[1],acc_para->kz0[2],
	 acc_para->kz1[0],acc_para->kz1[1],acc_para->kz1[2],
	
	 acc_para->n0[0],acc_para->n0[1],acc_para->n0[2],
	 acc_para->n1[0],acc_para->n1[1],acc_para->n1[2],
	 acc_para->n2[0],acc_para->n2[1],acc_para->n2[2]);
	
	 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)send_buff,out_len);
}

TpVoid GyroCalPara(Commond_ACC_GYRO_PARA* gyro_para)
{
	 TpUint16 out_len;
		
	 out_len = snprintf(send_buff,512,GYRO_CAL_PARA_OUT,\
	 gyro_para->ks0[0],gyro_para->ks0[1],gyro_para->ks0[2],
	 gyro_para->ks1[0],gyro_para->ks1[1],gyro_para->ks1[2],
	 gyro_para->kz0[0],gyro_para->kz0[1],gyro_para->kz0[2],
	 gyro_para->kz1[0],gyro_para->kz1[1],gyro_para->kz1[2],
	
	 gyro_para->n0[0],gyro_para->n0[1],gyro_para->n0[2],
	 gyro_para->n1[0],gyro_para->n1[1],gyro_para->n1[2],
	 gyro_para->n2[0],gyro_para->n2[1],gyro_para->n2[2]);
	
	 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)send_buff,out_len);
}
