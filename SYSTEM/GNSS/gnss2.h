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
	double UTC_Time;		//UTC 时间	(格式为 hhmmss.sss)
	double Latitude;		//纬度	(格式为 ddmm.mmmm)
	char N_or_S;			//纬度半球
	double Longitude;		//经度	(格式为 dddmm.mmmm)
	char E_or_W;			//经度半球
	uint8_t GPS_Status;		//GPS 状态 (0:未定位  1:非差分定位  2:差分定位)
	uint8_t Satellite_Num;	//卫星个数 (00--12)
	float HDOP;				//HDOP 水平精确度因子  (0.5--99.99)
	double Altitude;		//海拔高度  (-9999.9--9999.9米)
	double Geoid_Height;	//大地水准面高度  (-9999.9--9999.9米)
	uint32_t Diff_Time;		//差分时间	(单位：s)
	uint16_t Diff_Base;		//差分参考基站标号  (0000--1023)
	
	uint16_t u16Hdop;
	uint8_t u8GpggaDataFlag;
	uint8_t u8RtkFlag;
	
}GNGGA;


typedef struct
{
	double UTC_Time;		//UTC 时间	(格式为 hhmmss.sss)
	char Location_State;	//定位状态  (A:有效定位  V:无效定位)
	double Latitude;		//纬度	(格式为 ddmm.mmmm)
	char N_or_S;			//纬度半球
	double Longitude;		//经度	(格式为 dddmm.mmmm)
	char E_or_W;			//经度半球
	float Ground_Speed;		//地面速度  (000.0--999.9节)(1节=1852米/小时)
	double Ground_Course;	//地面航向  (000.0--359.9度，以真北方为参考基准)
	uint32_t UTC_Date;		//UTC日期  (格式为 ddmmyy)
	float Mag_Declination;	//磁偏角  (000.0--180.0度)
	char Mag_Direction;		//磁偏角方向  (E or W)
	char Mode_Indicator;	//模式指示  (A:自主定位  D:差分  E:估算  N:数据无效)
	
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
