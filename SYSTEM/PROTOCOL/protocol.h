/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   protocol.h                                                */
/* Date:        2016.5.18                                                  */
/* Description:                                                            */
/*=========================================================================*/
#ifndef __UMI_PROTOCOL_H__
#define __UMI_PROTOCOL_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"
#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define BUFFSIZE_PROTOCOL    (128)
#define BUFFSIZE_LOG         (512)

#define LOG_MAXRATE          (100)

#define LOG_NONE             (0)
#define LOG_NAV              (1)
#define LOG_IMU              (2)
#define LOG_BIN              (3)
#define LOG_GNSS             (4)

#define BAUD_RATE_921600    ((uint32_t)921600)
#define BAUD_RATE_460800    ((uint32_t)460800)
#define BAUD_RATE_230400    ((uint32_t)230400)
#define BAUD_RATE_115200    ((uint32_t)115200)
#define BAUD_RATE_57600     ((uint32_t)57600)
#define BAUD_RATE_38400     ((uint32_t)38400)
#define BAUD_RATE_19200     ((uint32_t)19200)
#define BAUD_RATE_9600      ((uint32_t)9600)
#define BAUD_RATE_4800      ((uint32_t)4800)
#define BAUD_RATE_2400      ((uint32_t)2400)

/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct tagProtocol
{
	TpUchar  buf[BUFFSIZE_PROTOCOL];
	TpUint16 num;
	TpUchar  start;
	TpUint16 pt ;
  TpUchar  flag;
}Protocol;

typedef struct tagLogout
{
  TpUchar  index;
  TpUint16 timer;
  TpUint16 rate;
  TpUchar  buf[BUFFSIZE_LOG];
  TpUint16 buf_len;
}Logout;

typedef struct tagOutFlag
{
  TpUchar  nav_out;
  TpUchar  imu_out;
  TpUchar  bin_out;
  TpUchar  gnss_out;
}OutFlag;

typedef struct tagLogFlag
{
  TpUchar  nav_log;
  TpUchar  imu_log;
  TpUchar  bin_log;
  TpUchar  gnss_log;
}LogFlag;

#pragma pack(pop)

/*============================================================================*/
/*                               declaration                             */
/*============================================================================*/

/*============================================================================*/
/*                             variables                                      */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern Protocol protocol;
extern OutFlag  outflag;
extern Logout   logout;
extern LogFlag  logflag;
extern TpUint32 logtimer;
  
TpVoid ProtocolInit(Protocol *pt);
TpVoid LogInit(Logout *lo);
TpVoid ProtocolDecAsc(Protocol *pt, TpUchar *pBuff,TpUchar u8num);
TpVoid DecodeProtocol(Protocol *pt);

/*============================================================================*/
/*                              Functions                                     */
/*============================================================================*/

TpVoid Set_Mis(Protocol *pt);


TpVoid OutputProtocol(Protocol *pt);
TpVoid SetProtocol(Protocol *pt);
  
TpVoid LogProtocol(Logout* lo,UmiOutput* uo);

// protocol about umi
TpBool UmiProtocol(Protocol *pt);

TpVoid LogNav(Logout* lo,UmiOutput* uo);
TpVoid LogImu(Logout* lo,UmiOutput* uo);
TpVoid LogBin(Logout* lo,UmiOutput* uo);
TpVoid LogGnss(Logout* lo,UmiOutput* uo);

// protocol about nav arm
TpVoid NavProtocol(Protocol *pt);
// protocol about ublox 
TpBool UbloxProtocol(Protocol *pt);

TpVoid SetBaudRate(uint8_t* data, TpUint32* baudrate);
TpVoid SaveConfig(TpVoid);
TpVoid SoftReset(TpVoid);


TpVoid Set_MagPara(Protocol *pt);
TpVoid Get_MagPara(Protocol *pt);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

