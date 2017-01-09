#ifndef __GNSS_H
#define __GNSS_H

#include "usart.h"
#include <stdlib.h>
#include <string.h>


#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint8_t u8Start[2];
	uint16_t u16Week;
	uint32_t u32UTC;
	double dLatitude;
	double dLongitude;
	float fAltitude;
	uint16_t u16Flag;
	float fVgroud;
	float fHeading;
	uint16_t u16Hdop;
	float fAzi;
	uint8_t u8Check;
	
	uint8_t u8CheckSum;
	
}GNSS;


typedef struct
{
	double UTC_Time;		//UTC ʱ��	(��ʽΪ hhmmss.sss)
	double Latitude;		//γ��	(��ʽΪ ddmm.mmmm)
	char N_or_S;			//γ�Ȱ���
	double Longitude;		//����	(��ʽΪ dddmm.mmmm)
	char E_or_W;			//���Ȱ���
	uint8_t GPS_Status;		//GPS ״̬ (0:δ��λ  1:�ǲ�ֶ�λ  2:��ֶ�λ)
	uint8_t Satellite_Num;	//���Ǹ��� (00--12)
	float HDOP;				//HDOP ˮƽ��ȷ������  (0.5--99.99)
	double Altitude;		//���θ߶�  (-9999.9--9999.9��)
	double Geoid_Height;	//���ˮ׼��߶�  (-9999.9--9999.9��)
	uint32_t Diff_Time;		//���ʱ��	(��λ��s)
	uint16_t Diff_Base;		//��ֲο���վ���  (0000--1023)
	
	uint16_t u16Hdop;
	uint8_t u8GpggaDataFlag;
	uint8_t u8RtkFlag;
	
}GNGGA;


typedef struct
{
	double UTC_Time;		//UTC ʱ��	(��ʽΪ hhmmss.sss)
	char Location_State;	//��λ״̬  (A:��Ч��λ  V:��Ч��λ)
	double Latitude;		//γ��	(��ʽΪ ddmm.mmmm)
	char N_or_S;			//γ�Ȱ���
	double Longitude;		//����	(��ʽΪ dddmm.mmmm)
	char E_or_W;			//���Ȱ���
	float Ground_Speed;		//�����ٶ�  (000.0--999.9��)(1��=1852��/Сʱ)
	double Ground_Course;	//���溽��  (000.0--359.9�ȣ����汱��Ϊ�ο���׼)
	uint32_t UTC_Date;		//UTC����  (��ʽΪ ddmmyy)
	float Mag_Declination;	//��ƫ��  (000.0--180.0��)
	char Mag_Direction;		//��ƫ�Ƿ���  (E or W)
	char Mode_Indicator;	//ģʽָʾ  (A:������λ  D:���  E:����  N:������Ч)
	
	uint8_t u8Data_valid;
	
}GNRMC;


typedef struct
{
	GNGGA Gngga;
	GNRMC Gnrmc;
	
}NMEA;

#pragma pack(pop)


extern NMEA Nmea;


void GNSS_Package(NMEA* Nmea);
void NMEA_Decoding(uint8_t* data);
void NMEA_Protocol(uint8_t* data, NMEA* Nmea);
void NMEA_GNGGA(uint8_t* data, GNGGA* gngga);
void NMEA_GNRMC(uint8_t* data, GNRMC* gnrmc);

double Ddmm2dd(double ddmm);
uint16_t Date2Week(float fTime, uint32_t u32Data);
uint32_t hhmmss2ss(double fddmm);

uint8_t check_sum(uint8_t* Buffer, int length);

uint8_t ReturnWeekDay(uint32_t u32Date);

#endif 	//__GNSS_H
