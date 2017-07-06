#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include "command.h"
#include "command_bin.h"
#include "globals.h"

#define OUTPUT_RATE_MAX						(100) /*100hz */

#pragma pack(push)
#pragma pack(1)

typedef struct
{
  TpUint16 head;
	TpUchar  Class;
	TpUchar  ID;
	TpUint16 length;
	
	TpUint32 index;	
	TpUint32 tow_imu;	
  TpFloat  gyox;
	TpFloat  gyoy;
	TpFloat  gyoz;
  TpFloat  accx;
	TpFloat  accy;
	TpFloat  accz;
  TpFloat  magx;
	TpFloat  magy;
	TpFloat  magz;
	TpFloat  temp_gyo;
	TpFloat  temp_acc;
	TpUchar  check;
	TpUchar  end;
}ImuBin;

typedef struct 
{
  TpUint16 head;
	TpUchar  Class;
	TpUchar  ID;
	TpUint16 length;
	TpUint32 index;	
	TpUint32 tow_imu;  
  TpFloat  heading; /* heading in degree */
	TpFloat  roll;   /* roll in degree */
	TpFloat  pitch;   /* pitch in degree */
	TpFloat  quat[4]; /* Quaternions*/	
	TpUchar  check;
	TpUchar  end;
	
}AhrsBin;


typedef struct 
{
  TpUint16 head;
	TpUchar  Class;
	TpUchar  ID;
	TpUint16 length;
	TpUint32 index;	
	TpUint32 tow_imu;  
	
	TpDouble lat;
	TpDouble lon;
  TpFloat  heading; /* heading in degree */
	TpFloat  roll;   /* roll in degree */
	TpFloat  pitch;   /* pitch in degree */
	
	TpFloat  ve; 
	TpFloat  vn; 
	TpFloat  vu; 
	
	TpUchar  check;
	TpUchar  end;
	
}NavBin;



#pragma pack(pop)


#define BENCHMARK_FREQ   OUTPUT_RATE_MAX

/* output  */
TpVoid LogOutput(UmiIgmBin* pUmiOutput);

#endif
