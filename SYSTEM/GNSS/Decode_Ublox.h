#ifndef DECODE_UBLOX_H
#define DECODE_UBLOX_H

#include "definition.h"

#define HEAD_GGA							"$GPGGA,"
#define HEAD_RMC							"$GPRMC,"
#define COMMA_ASCII_DIVISION	","

#define MILE2KM              (1852.0f/3600.0f)

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

#define GNSS_INCOMPLETE      ((TpUint16)1<<2)

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	TpDouble  time_utc;
	TpDouble  lat;
	TpChar 		lat_dir;
	TpDouble 	lon;
	TpChar    lon_dir;
	TpUchar   quality;
	TpUchar		numsv;
	TpFloat   hdop;
	TpFloat 	alt;	
	TpChar 		ualt;	
	TpFloat		sep;
	TpChar 		usep;	
	TpUchar		diffage;
	TpUchar   diffstation;
	TpUchar		check;	
}GPGGA_DATA;


typedef struct
{
	TpDouble 	time_utc;
  TpUchar   status;
	
	TpDouble  lat;
	TpChar 		lat_dir;
	TpDouble 	lon;
	TpChar    lon_dir;
	
	TpFloat   spd;
	TpFloat   cog;
	TpUint32  date;
	
	TpUchar   mv;
	TpUchar   mvew;
	TpUchar   posmode;
	TpUchar   navstatus;
	TpUchar   check;

}GPRMC_DATA;


typedef struct
{
	TpUint16  head;
	TpUint16  week_num;
	TpUint32  week_second;
	TpDouble  lat;
	TpDouble  lon;
	TpFloat   alt;
	TpUint16  flag;
	TpFloat   spd;
	TpFloat   heading;
	TpUint16  hdop;
	TpFloat   orient;
	TpUchar   check;
}GnssOutPut;

#pragma pack(pop)


TpVoid DecodeUblox(TpUchar *buf,TpUint16 length);
TpVoid PackGnssData(GnssOutPut* gnss);

TpVoid TimeChange(TpUint16 * week_num,TpUint32 * week_s);

#endif
