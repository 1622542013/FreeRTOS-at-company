/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   GNSS.h                                                */
/* Date:        2016.8.5                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_GNSS_H__
#define __UMI_GNSS_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define GNSS_PACK_SIZE       (512)
#define MILE2KM              (1852.0f/3600.0f)
#define DAY_NIGHT_MS         (86400000)
#define HDOP_FAC             (100)

#define CRC32_POLYNOMIAL     (0xEDB88320L)
#define UTC2GPS              (0)

#define NONE_IN				       ((TpUchar)0)
#define GPGGA_IN			       ((TpUchar)1)
#define GPRMC_IN				     ((TpUchar)2)
#define GPHDT_IN			       ((TpUchar)3)
#define BESTVELA_IN          ((TpUchar)4)
#define HEADINGA_IN          ((TpUchar)5)

#define GNSS_FLAG		         (0x8000)
#define GPGGA_FLAG           (0x0001)
#define GPRMC_FLAG           (0x0002)
#define GPHDT_FLAG           (0x0004)
#define BESTVELA_FLAG        (0x0008)
#define HEADINGA_FLAG        (0x0010)

/* GNSS fix type */
#define GNSS_FIX_INVALID     ((TpUint16)0)
#define GNSS_FIX_PV          ((TpUint16)1<<0)
#define GNSS_FIX_ORT         ((TpUint16)1<<1)
#define GNSS_FIX_SPS         ((TpUint16)1<<10)
#define GNSS_FIX_DGPS        ((TpUint16)1<<11)
#define GNSS_FIX_FLOAT       ((TpUint16)1<<12)
#define GNSS_FIX_RTK         ((TpUint16)1<<13)
#define GNSS_FIX_1PPS        ((TpUint16)1<<14)
#define GNSS_FIX_DATA        ((TpUint16)1<<15)
#define GNSS_FIX_VALID       (GNSS_FIX_PV)


/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	TpUint16  head;
	TpUint16  week;
	TpInt32   time_utc;
	TpDouble  lat;
	TpDouble  lon;
	TpFloat   alt;
	TpUint16  flag;
	TpFloat   vg;
	TpFloat   heading;
	TpUint16  hdop;
	TpFloat   orient;
	TpUchar   check;
}GnssOut;

/* Log Header */
typedef struct
{
  TpUchar   sync;
	TpUchar   msg[10];
	TpUchar   port[5];
	TpUchar   seq[20];
	TpUchar   idle_time[20];
	TpUchar   time_status[20];
	TpUint16  week;
	TpDouble  time_gps;
	TpUchar   rec_status[10];
	TpUchar   resv[4];
	TpUchar   version[4];
}LogHead;


typedef struct tagGpgga
{
	TpDouble  time_utc;
	TpDouble  lat;
	TpDouble 	lon;
	TpFloat 	alt;
	TpUchar 	sat_num;
	TpUchar 	fs;
	TpFloat 	hdop;
	TpUchar 	sv;
	TpFloat 	altref;
	TpInt32 	diff_time;
	TpUint16 	diff_id;
	TpUchar 	data_flag;
	TpUchar 	rtk_flag;
	TpUchar   gnss_mode;
	TpUchar   gps_state;
}Gpgga;

typedef struct tagGprmc
{
	TpDouble 	time_utc;
  TpUchar   data_valid;
	TpDouble 	lat;
	TpDouble 	lon;
	TpFloat   vg;
	TpFloat   heading;
	TpInt32   date;
	TpFloat   mag_azi;
	TpUchar   sysmode;
}Gprmc;

typedef struct tagGphdt
{
	TpFloat   orient;
  TpUchar   true_flag;
}Gphdt;

typedef struct tagBestvela
{
	LogHead   loghead;
	TpUchar   age[10];
	TpUchar   sol_status[20];
	TpUchar   vel_type[20];
	TpUchar   latency[10];
	TpUchar   resv[4];
	TpFloat   track;
	TpFloat   vg;
	TpFloat   ve;
	TpFloat   vn;
	TpFloat   vu;
	TpUchar   sol_s;
	TpUchar   pv_type;
	TpUchar   vdata_flag;
	TpUchar   time_type;
}BestVela;

typedef struct tagHeadinga
{
	LogHead   loghead;
	TpUchar   sol_sta[30];
	TpUchar   pos_type[20];
	TpUchar   baseline[20];

  TpInt32   sol_st;

  TpFloat   bs;	   //Baseline length (0 to 3000 m)
  TpFloat   pitch;		     //Pitch (¡À90 degrees)
  TpFloat   heading;		   //Heading in degrees (0 to 360.0 degrees)
  TpFloat   heading_std;		   //Heading standard deviation in degrees
  TpFloat   pitch_std;	   //Pitch standard deviation in degrees
  TpChar    stn_id[4];
  TpUchar   svs; 			   //Number of observations tracked
  TpUint16  sol_svs;		   //Number of satellites in solution
  TpUint16  obs;          //Number of satellites above the elevation mask
  TpUint16  multi;        //Number of satellites above the mask angle with L2


  TpUchar   sol_source;
  TpUchar   sigmask1;
  TpUchar   sigmask2;

  TpUchar   resv1;
  TpUchar   extsol;
  TpUchar   resv2;
  TpUchar   sigmask;
  TpUint16  pv_type;
  TpUint16  heading_flag;
}Headinga;

typedef struct tagNmea
{
 Gpgga     gpgga;
 Gprmc     gprmc;
 Gphdt     gphdt;
 TpUint16  flag;
}Nmea;

typedef struct tagGnssRec
{
 Nmea      nmea;
 BestVela  bestvela;
 Headinga  headinga;
 TpUint16  flag;
}GnssRec;


 typedef struct tagPackageGnss
{
	TpUchar  data_ptr[GNSS_PACK_SIZE];
	TpUint16  buff_len;
	TpUint16  pt;
	TpUchar   start;
}PackageGnss;

#pragma pack(pop)

/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern GnssOut gnssout;
extern PackageGnss package;
extern GnssRec gnssrec;
  
extern TpUchar  pps_start;

TpVoid  PackageInit(PackageGnss *pa);
TpVoid  PackageRec(TpUchar *pbuf,TpUint16 num);
TpVoid  GnssCombine(GnssOut *gno,GnssRec *gr);

TpUchar GpggaDecode(PackageGnss* pa,GnssRec *gr);
TpUchar GprmcDecode(PackageGnss* pa,GnssRec *gr);
TpUchar GphdtDecode(PackageGnss* pa,GnssRec *gr);
TpVoid  GnssDecode(PackageGnss* pa,GnssRec *gr);

static TpUchar BestVelDec(PackageGnss* pa,GnssRec *gr);
static TpUchar HeadingaDec(PackageGnss* pa,GnssRec *gr);

static TpChar PvType(TpChar* buf,TpUint32 len);
static TpChar SolStatus(TpChar* buf,TpUint32 len);

static  TpChar CheckSumNovatel(TpUchar *buf,TpInt32 count);
TpInt32 Asc2Int(TpUchar* buf);
TpInt32 CalculateBlockCRC32(TpInt32 count,TpUchar* buf );
TpInt32 CRC32Value(TpInt32 i);

static   TpUchar CheckSumNmea(const TpUchar *buf,const TpUint16 count);
TpUchar  Asc2Uchar(TpUchar data);
TpDouble Ddmm2dd(TpDouble data);
TpInt32  Hhmmss2ss(TpDouble data);
static TpUint16 Date2Week(TpFloat time,TpInt32 date);
TpUchar  ReturnDay(TpInt32 date);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
