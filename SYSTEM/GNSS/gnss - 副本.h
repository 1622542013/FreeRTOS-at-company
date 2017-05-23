/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   GNSS.h                                                */
/* Date:        2016.5.18                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_GNSS_H__
#define __UMI_GNSS_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include <math.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define _PACKAGESIZE          (512)
#define  MILE2KM              (1852.0f/3600.0f)
#define _D2R                  (0.01745329251994f)
#define CRC32_POLYNOMIAL      (0xEDB88320L)
#define _UTC2GPS              (17000)

#define _NONE				  (0)
#define _GPGGA			      (1)
#define _GPRMC				  (2)
#define _GPHDT			      (3)
#define _BESTVELA             (4)
#define _HEADINGA             (4)

#define GPS_GPSDATA_IN		  (0x8000)
#define GPS_GPGGA_IN          (0x0001)
#define GPS_GPRMC_IN          (0x0002)
#define GPS_GPHDT_IN          (0x0004)
#define GPS_BESTVELA_IN       (0x0008)
#define GPS_HEADINGA_IN       (0x0010)


/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	uint8_t   u8Start[2];
	uint16_t  u16Week;
	uint32_t  u32UTC;
	double    dLatitude;
	double    dLongitude;
	float     fAltitude;
	uint16_t  u16Flag;
	float     fVgroud;
	float     fHeading;
	uint16_t  u16Hdop;
	float     fAzi;
	uint8_t   u8Check;
}stGnssOut;

/* Log Header */
typedef struct
{
  uint8_t   u8Sync;
	uint8_t   u8Message[10];
	uint8_t   u8Port[5];
	uint8_t   u8Sequence[20];
	uint8_t   u8IdleTime[20];
	uint8_t   u8TimeStatus[20];
	uint16_t  u16Week;
	double    dGpsSec;
	uint8_t   u8ReceiverStatus[10];
	uint8_t   u8Reserved[4];
	uint8_t   u8Version[4];
}stLogHeader;


typedef struct
{
	double 		dUtcTime;
	double 		dLatitude;
	double 		dLongitude;
	float 		fAltitude;
	uint8_t 	Num_Satellites;
	uint8_t 	uFS;
	float 	    fHdop;
	uint8_t 	u8NoSV;
	float 		fAltref;
	uint32_t 	u32DiffTime;
	uint16_t 	u16DiffId;
	uint8_t 	u8GpggaDataFlag;
	uint8_t 	u8RtkFlag;
	uint8_t     u8Gnss_Mode;
	uint8_t     u8GPS_State;
}stGpgga;

typedef struct
{
	double 		dUtcTime;
  uint8_t   u8Data_valid;
	double 		dLatitude;
	double 		dLongitude;
	float     fVgoroud;
	float     fHeading;
	uint32_t  u32Date;
	float     fMagn_Azi;
	uint8_t   uSystme_mode;
}stGprmc;

typedef struct
{
	float     fAzi;
  uint8_t   uTrue;
}stGphdt;

typedef struct
{
	stLogHeader m_stLogHeader;
	uint8_t     u8Age[10];
	uint8_t     u8SolStatus[20];
	uint8_t     u8VelType[20];
	uint8_t     u8Latency[10];
	uint8_t     u8Reserved[4];
	float       fTrack;
	float       fVGround;
	float       fVe;
	float       fVn;
	float       fVu;
	uint8_t     u8SolutionStatus;
	uint8_t     u8P_VType;
	uint8_t     u8VDataFlag;
	uint8_t     u8TimeType;
}stBestVela;

typedef struct
{
	stLogHeader m_stLogHeader;
	uint8_t     strSolStat[30];
	uint8_t     strPosType[20];
	uint8_t     strBaseLine[20];

  uint32_t    u32SolStat;

  float       fBaseline;	   //Baseline length (0 to 3000 m)
  float       fPitch;		     //Pitch (¡À90 degrees)
  float       fHeading;		   //Heading in degrees (0 to 360.0 degrees)
  float       fHdg_std;		   //Heading standard deviation in degrees
  float       fPtch_std;	   //Pitch standard deviation in degrees
  int8_t      cStnID[4];
  uint8_t     uSVs; 			   //Number of observations tracked
  uint16_t    uSolnSVs;		   //Number of satellites in solution
  uint16_t    uObs;          //Number of satellites above the elevation mask
  uint16_t    uMulti;        //Number of satellites above the mask angle with L2


  uint8_t     u8SolSource;
  uint8_t     u8SigMask_1;
  uint8_t     u8SigMask_2;

  uint8_t     ucReserved1;
  uint8_t     ucExtSolStat;
  uint8_t     ucReserved2;
  uint8_t     ucSigMask;
  uint16_t    uP_VType;
  uint16_t    uHeadingaFlag;
}stHeadinga;

typedef struct
{
 stGpgga  m_stGpgga;
 stGprmc  m_stGprmc;
 stGphdt  m_stGphdt;
 uint16_t u16Flag;
}stNMEA;

typedef struct
{
 stNMEA      m_stNMEA;
 stBestVela  m_stBestVela;
 stHeadinga  m_stHeadinga;
 uint16_t    u16Flag;
}stGnssIn;


 typedef struct
{
	uint8_t  u8Vec_Package[_PACKAGESIZE];
	uint16_t  u16Num_Package;
	uint16_t  u16Pointer;
	uint8_t   u8Start_Package;
}stPackage;

typedef struct
{
	uint8_t   u8Hour;
	uint8_t   u8Minute;
	uint8_t   u8Second;
	uint16_t	u16MilSecond;
}stUtcData;

#pragma pack(pop)

/*============================================================================*/
/*                               declaration                             */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern stGnssOut m_stGnssOut;
extern stPackage m_stPackage;
extern stGnssIn m_stGNSSIn;
extern stGnssIn m_stGnssModify;
extern stHeadinga m_stHeadingaSave;

void Init_Package(stPackage *pstPackage);
void Package_Rec(uint8_t *pBuffer,uint16_t u16Num);
//static void Package_GNSS(stGnssOut *pstGNSSOut,stGnssIn *pstGNSSIn);
extern void Combain_GNSS(stGnssOut *pstGNSSOut,stGnssIn *pstGNSSIn);

static uint8_t Decode_Gpgga(stPackage* pstPackage,stGnssIn *pstGNSSIn);
static uint8_t Decode_Gprmc(stPackage* pstPackage,stGnssIn *pstGNSSIn);
static uint8_t Decode_Gphdt(stPackage* pstPackage,stGnssIn *pstGNSSIn);
static void GNSS_Decode(stPackage* pstPackage,stGnssIn *pstGNSSIn);

static uint8_t Decode_BestVela(stPackage* pstPackage,stGnssIn *pstGNSSIn);
static uint8_t Decode_Headinga(stPackage* pstPackage,stGnssIn *pstGNSSIn);

static char Test_P_V_Type(const char* DataBuffer,unsigned Length);
static char Test_SolStat(const char* DataBuffer,unsigned Length);

void Combin_Gpgga(stGnssIn* pstGnssIn,uint32_t u32UtcTime,double dLati,double dLon,float fAlt);
void Combin_Bestvela(stGnssIn* pstGnssIn,uint32_t u32UtcTime,float fVground,float fHeading,float fVu,const char* pBuffSolStatus,const char* pBuffPosSataus);
void Combin_Headinga(stHeadinga* pstHeadinga,uint32_t u32UtcTime,float fHeading,float fPitch,float fRoll,uint8_t* pBuffSolStatus,uint8_t* pBuffPosSataus);

static char Checmsum_Novtel(uint8_t *ucBuffer,uint32_t ulCount);
uint32_t Asc_Int2Int(uint8_t*Buffer);
uint32_t CalculateBlockCRC32(uint32_t ulCount,uint8_t *ucBuffer );
uint32_t CRC32Value(int32_t i);

static uint8_t CheckSum_NMEA(const uint8_t *u8Buffer,const uint16_t u16Count);
uint8_t ASCII2u8(uint8_t u8Data);
double Ddmm2dd(double ddmm);
uint32_t hhmmss2ss(double fddmm);
static uint16_t Date2Week(float fTime,uint32_t u32Data);
uint8_t ReturnWeekDay( uint32_t u32Date);
static uint8_t Check_Out(uint8_t* Buffer ,int length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
