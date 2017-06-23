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

uint8_t output_data_buff[512];

TpVoid LogImuAscii(UmiIgmBin* pUmiOutput)
{
	TpUint16 len = 0;
	float Acc_Temp  = (float)pUmiOutput->imu.acc_temp / 16.0f;
	float Gyro_temp = (float)pUmiOutput->imu.gyo_temp / 16.0f;
	float Bmp_Temp  = (float)pUmiOutput->imu.bmp_temp / 16.0f;

	len = snprintf((char*)output_data_buff,200,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",
		      OUTPUT_ID_IMU_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,
					pUmiOutput->imu.gyox,pUmiOutput->imu.gyoy,pUmiOutput->imu.gyoz,
					pUmiOutput->imu.accx,pUmiOutput->imu.accy,pUmiOutput->imu.accz,
					pUmiOutput->mag.magx,pUmiOutput->mag.magy,pUmiOutput->mag.magz,
					Gyro_temp,Acc_Temp);
	
  UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)output_data_buff,(TpUint16)len);
}


TpVoid LogAhrsAscii(UmiIgmBin* pUmiOutput)
{
	TpUint16 len = 0;
	
	len = snprintf((char*)output_data_buff,200,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\r\n",
									OUTPUT_ID_AHRS_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,
									pUmiOutput->nav.heading,pUmiOutput->nav.roll,pUmiOutput->nav.pitch,
									pUmiOutput->nav.quat[0],pUmiOutput->nav.quat[1],pUmiOutput->nav.quat[2],pUmiOutput->nav.quat[3]);
	
  UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)output_data_buff,(TpUint16)len);
}

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint8_t head[6];
	uint8_t length;
	
	uint64_t time;
	
	uint8_t ID;
	
	float gx;
	float	gy;
	float	gz;
	float	ax;
	float	ay;
	float	az;
	float gx_integral;
	float	gy_integral;
	float	gz_integral;
	float	ax_integral;
	float	ay_integral;
	float	az_integral;
	float	mx;
	float	my;
	float	mz;
	float	gyro_temperature;
	
	float Quat[4]; 
	
	uint8_t CRC_bit;
	uint8_t end_bit;
	
}Ahrs_IMU;

#pragma pack(pop)

Ahrs_IMU Ahrs_IMU_upper;

const uint8_t CRC_TABLE[256] = {
0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};
uint8_t GetCheckbyte(uint8_t * p_char, uint32_t datanum )
{
	uint8_t crc = 0;
	while( datanum-- ) crc = CRC_TABLE[crc ^ *p_char++];
	return crc;
}

#define GRA    		9.8f  /* Gravitational acceleration */ 
#define S_TO_US 	(uint64_t)1000000	 /*Second to Microsecond*/
TpVoid LogAhrsBin(UmiIgmBin* pUmiOutput)
{
	float changetime = 0.0;
	float Gyro_temp = (float)pUmiOutput->imu.gyo_temp / 16.0f;
	
	uint32_t  freq = GetOutputFormat(AHRS_BIN);
	
	    changetime = 1.0f / (float)freq;
	
			Ahrs_IMU_upper.head[0] = 0xfd;
			Ahrs_IMU_upper.head[1] = 0x04;
			Ahrs_IMU_upper.head[2] = 0x00;
			Ahrs_IMU_upper.head[3] = 0x01;
			Ahrs_IMU_upper.head[4] = 0xa0;
			Ahrs_IMU_upper.head[5] = 0x86;
			Ahrs_IMU_upper.length  = sizeof(Ahrs_IMU_upper);
			
			Ahrs_IMU_upper.time = (uint64_t)pUmiOutput->index * (uint64_t)((uint64_t)S_TO_US / (uint64_t)freq);
			Ahrs_IMU_upper.ID = 0;
			Ahrs_IMU_upper.ax = pUmiOutput->imu.accx;
			Ahrs_IMU_upper.ay = pUmiOutput->imu.accy;
			Ahrs_IMU_upper.az = pUmiOutput->imu.accz;
			Ahrs_IMU_upper.gx = pUmiOutput->imu.gyox;
			Ahrs_IMU_upper.gy = pUmiOutput->imu.gyoy;
			Ahrs_IMU_upper.gz = pUmiOutput->imu.gyoz;	
		
			Ahrs_IMU_upper.ax_integral = pUmiOutput->imu.accx * GRA * changetime; 
			Ahrs_IMU_upper.ay_integral = pUmiOutput->imu.accy * GRA * changetime;
			Ahrs_IMU_upper.az_integral = pUmiOutput->imu.accz * GRA * changetime;
			Ahrs_IMU_upper.gx_integral = pUmiOutput->imu.gyox * changetime;
			Ahrs_IMU_upper.gy_integral = pUmiOutput->imu.gyoy * changetime;
			Ahrs_IMU_upper.gz_integral = pUmiOutput->imu.gyoz * changetime;
			
			Ahrs_IMU_upper.mx = pUmiOutput->mag.magx;
			Ahrs_IMU_upper.my = pUmiOutput->mag.magy;
			Ahrs_IMU_upper.mz = pUmiOutput->mag.magz;
			
			Ahrs_IMU_upper.gyro_temperature = Gyro_temp;
			
			Ahrs_IMU_upper.Quat[0] = pUmiOutput->nav.quat[0];
			Ahrs_IMU_upper.Quat[1] = pUmiOutput->nav.quat[1];
			Ahrs_IMU_upper.Quat[2] = pUmiOutput->nav.quat[2];
			Ahrs_IMU_upper.Quat[3] = pUmiOutput->nav.quat[3];
			
			Ahrs_IMU_upper.CRC_bit = GetCheckbyte((uint8_t *)&Ahrs_IMU_upper, sizeof(Ahrs_IMU_upper) - 2);
			Ahrs_IMU_upper.end_bit = 0xfe;

			UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)&Ahrs_IMU_upper,sizeof(Ahrs_IMU_upper));	
}

TpVoid LogIgmAscii(UmiIgmBin* pUmiOutput)
{
	TpUint16 len_message = 0;

	len_message = snprintf((char*)output_data_buff,512,"%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%.10f,%.10f,%.10f,%.10f,%f,%f,%f,%f,%f,%f\r\n",
		      OUTPUT_ID_IGM_ASCII,pUmiOutput->index,pUmiOutput->tow_imu,pUmiOutput->week,
					pUmiOutput->imu.gyox,pUmiOutput->imu.gyoy,pUmiOutput->imu.gyoz,
					pUmiOutput->imu.accx,pUmiOutput->imu.accy,pUmiOutput->imu.accz,
					pUmiOutput->mag.magx,pUmiOutput->mag.magy,pUmiOutput->mag.magz,
					pUmiOutput->gnss.tow_pps,pUmiOutput->gnss.lat,pUmiOutput->gnss.lon,
					pUmiOutput->nav.lat,pUmiOutput->nav.lon,pUmiOutput->nav.heading,pUmiOutput->nav.pitch,pUmiOutput->nav.roll,
					pUmiOutput->nav.ve,pUmiOutput->nav.vn,pUmiOutput->nav.vu);

	UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)output_data_buff,len_message);
}

TpVoid LogIgmBin(UmiIgmBin* pUmiOutput)
{
	UsartPushSendBuf(GetUsartAddress(USART_2),(TpUchar*)pUmiOutput,sizeof(UmiIgmBin));	
}

TpVoid AccCalPara(Commond_ACC_GYRO_PARA* acc_para)
{
	 TpUint16 out_len;
		
	 out_len = snprintf((char*)output_data_buff,512,ACC_CAL_PARA_OUT,\
	 acc_para->ks0[0],acc_para->ks0[1],acc_para->ks0[2],
	 acc_para->ks1[0],acc_para->ks1[1],acc_para->ks1[2],
	 acc_para->kz0[0],acc_para->kz0[1],acc_para->kz0[2],
	 acc_para->kz1[0],acc_para->kz1[1],acc_para->kz1[2],
	
	 acc_para->n0[0],acc_para->n0[1],acc_para->n0[2],
	 acc_para->n1[0],acc_para->n1[1],acc_para->n1[2],
	 acc_para->n2[0],acc_para->n2[1],acc_para->n2[2]);
	
	 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)output_data_buff,out_len);
}

TpVoid GyroCalPara(Commond_ACC_GYRO_PARA* gyro_para)
{
	 TpUint16 out_len;
		
	 out_len = snprintf((char*)output_data_buff,512,GYRO_CAL_PARA_OUT,\
	 gyro_para->ks0[0],gyro_para->ks0[1],gyro_para->ks0[2],
	 gyro_para->ks1[0],gyro_para->ks1[1],gyro_para->ks1[2],
	 gyro_para->kz0[0],gyro_para->kz0[1],gyro_para->kz0[2],
	 gyro_para->kz1[0],gyro_para->kz1[1],gyro_para->kz1[2],
	
	 gyro_para->n0[0],gyro_para->n0[1],gyro_para->n0[2],
	 gyro_para->n1[0],gyro_para->n1[1],gyro_para->n1[2],
	 gyro_para->n2[0],gyro_para->n2[1],gyro_para->n2[2]);
	
	 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)output_data_buff,out_len);
}
