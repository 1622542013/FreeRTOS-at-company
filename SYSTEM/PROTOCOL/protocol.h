/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   protocol.h                                                 */
/* Date:        2016.12.28                                                 */
/* Description:                                                            */
/*=========================================================================*/
#ifndef __PROJECT_UMI_PROTOCOL_H__
#define __PROJECT_UMI_PROTOCOL_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define BUFFSIZE_PROTOCOL    (128)
#define BUFFSIZE_LOG         (512)

#define LOG_MAXRATE          (PROJECT_DATE_RATE)
#define DATA_SEND_NAV_LEN    (100)

#define PROTOCOL_START       ((TpUchar)0x24) // '$'
#define PROTOCOL_END_1       ((TpUchar)0x0D)
#define PROTOCOL_END_2       ((TpUchar)0x0A)
#define LETTERS_CAPTIAL_A    ((TpUchar)0x41) // 'A'
#define LETTERS_CAPTIAL_Z    ((TpUchar)0x5a) // 'Z'
#define LETTERS_CAPTIAL_LEN  ((TpUchar)0x20)
#define LETTERS_STAR         ((TpUchar)0x2A) // '*'
#define LETTERS_COMMA         ((TpUchar)0x2C) // ','

#define LOG_NONE             ((TpUint16)1<<0)
#define LOG_NAV              ((TpUint16)1<<1)
#define LOG_IMU              ((TpUint16)1<<2)
#define LOG_BIN              ((TpUint16)1<<3)
#define LOG_GNSS             ((TpUint16)1<<4)

#ifdef UMI_SATCOM_FORMAT
#define LOG_POS              ((TpUint16)1<<5)
#endif

/******/
#define LETTERS_OUTPUT_NULL                "null"
#define LETTERS_OUTPUT_NAV                 "nav"
#define LETTERS_OUTPUT_IMU                 "imu"
#define LETTERS_OUTPUT_GNSS                "gnss"
#define LETTERS_OUTPUT_BIN                 "bin"
#ifdef UMI_SATCOM_FORMAT
#define LETTERS_OUTPUT_POS                 "pos"
#endif
/******************************* protocol ***********************************/
#define PROTOCOL_UMI_HEAD                  "$cmd,umi,"
/* arm3 protocol */
#define PROTOCOL_UMI_ARM3_HEAD             "$cmd,umi,"
/* arm3,output protocol */
#define PROTOCOL_UMI_ARM3_OUTPUT_HEAD      "$cmd,umi,output,"
#define PROTOCOL_UMI_ARM3_OUTPUT_IMU       "$cmd,umi,output,imu,"
#define PROTOCOL_UMI_ARM3_OUTPUT_NAV       "$cmd,umi,output,nav,"
#define PROTOCOL_UMI_ARM3_OUTPUT_BIN       "$cmd,umi,output,bin,"
#define PROTOCOL_UMI_ARM3_OUTPUT_GNSS      "$cmd,umi,output,bin,"
/* arm3,through gnss */
#define PROTOCOL_UMI_ARM3_THROUGH          "$cmd,umi,through,"
#define PROTOCOL_UMI_ARM3_THROUGH_GNSS_ON  "$cmd,umi,through,gnss,on*ff"
#define PROTOCOL_UMI_ARM3_THROUGH_GNSS_OFF "$cmd,umi,through,gnss,off*ff"
/* arm3,set protocol */
#define PROTOCOL_UMI_ARM3_SET_HEAD         "$cmd,umi,set,"
#define PROTOCOL_UMI_ARM3_SET_MIS          "$cmd,umi,set,mis,"
#define PROTOCOL_UMI_ARM3_SET_BAUDRATE     "$cmd,umi,set,baudrate,"
/* arm3,get protocol */
#define PROTOCOL_UMI_ARM3_GET_HEAD           "$cmd,umi,get,"
#define PROTOCOL_UMI_ARM3_GET_MIS            "$cmd,umi,get,mis,"
/* arm3,save protocol */
#define PROTOCOL_UMI_ARM3_SAVE               "$cmd,umi,saveconfig*ff"
/* arm3, through protocol to usart1 and usart2*/
#define PROTOCOL_UMI_ARM3_THROUGH_USART1_ON  "$cmd,umi,through,usart1,on*ff"
#define PROTOCOL_UMI_ARM3_THROUGH_USART1_OFF "$cmd,umi,through,usart1,off*ff"
#define PROTOCOL_UMI_ARM3_THROUGH_USART2_ON  "$cmd,umi,through,usart2,on*ff"
#define PROTOCOL_UMI_ARM3_THROUGH_USART2_OFF "$cmd,umi,through,usart2,off*ff"
/* arm3,reset protocol */
#define PROTOCOL_UMI_ARM3_RESET              "$cmd,umi,reset*ff"

/* arm2,protocol */
#define PROTOCOL_UMI_ARM2_HEAD               "$cmd,umi,arm2,"
/* arm2,miscali */
#define PROTOCOL_UMI_ARM2_MIS_CALI_ON        "$cmd,umi,arm2,mis,cali,on*ff"
#define PROTOCOL_UMI_ARM2_MIS_CALI_OFF       "$cmd,umi,arm2,mis,cali,on*ff"
#define PROTOCOL_UMI_ARM2_SET_MIS            "$cmd,umi,arm2,set,mis,"
#define PROTOCOL_UMI_ARM2_GET_MIS            "$cmd,umi,arm2,get,mis*ff"
#define PROTOCOL_UMI_ARM2_SAVE_MIS           "$cmd,umi,arm2,save,mis*ff"
#define PROTOCOL_UMI_ARM2_RESET              "$cmd,umi,arm2,reset*ff"
/* ublox,protocol */
#define PROTOCOL_UMI_UBLOX_HEAD              "$cmd,umi,ublox,"
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
  TpUint16  index;
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
	TpUchar  pos_out;
}OutFlag;

typedef struct tagOutRage
{
	TpUchar bin_rate;
	TpUchar pos_rate;
}OutRate;

typedef struct tagLogFlag
{
  TpUchar  nav_log;
  TpUchar  imu_log;
  TpUchar  bin_log;
  TpUchar  gnss_log;
	TpUchar  pos_log;
}LogFlag;

typedef struct tagDataSendNav
{
	float    mis[3];
	TpUchar  buf[DATA_SEND_NAV_LEN];
	TpUint16 len;
}DataSendNav;

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

extern Protocol    protocol;
extern OutFlag     outflag;
extern Logout      logout;
extern LogFlag     logflag;
extern TpUint32    logtimer;
extern OutRate     outrate;
extern DataSendNav dataSendNav;
  
TpVoid ProtocolInit(Protocol *pt);
TpVoid LogInit(Logout *lo);
TpVoid ProtocolDecAscii(Protocol *pt,TpUchar *pBuf,TpUint16 len);
TpVoid ProtocolDec(Protocol *pt);

/*============================================================================*/
/*                              Functions                                     */
/*============================================================================*/

TpVoid SetMis(Protocol *pt,DataSendNav* dn);


TpVoid OutputProtocol(Protocol *pt);
TpVoid SetProtocol(Protocol *pt);
  
TpVoid LogProtocol(Logout* lo,UmiOutput* uo);

// protocol about umi
TpBool ARM3Protocol(Protocol *pt);

TpVoid LogNav(Logout* lo,UmiOutput* uo);
TpVoid LogImu(Logout* lo,UmiOutput* uo);
TpVoid LogBin(Logout* lo,UmiOutput* uo);
TpVoid LogGnss(Logout* lo,UmiOutput* uo);

// protocol about nav arm
TpVoid ARM2Protocol(Protocol *pt,DataSendNav* dn);

TpVoid ThroughProtocol(Protocol *pt);
// protocol about ublox 
TpBool UbloxProtocol(Protocol *pt);

TpVoid SetBaudRate(uint8_t* data, TpUint32* baudrate);
TpVoid SaveConfig(TpVoid);
TpVoid SoftReset(TpVoid);

/*   */
TpVoid UsartDataDec(TpUchar index,TpUchar *pb,TpUint16 num);

#ifdef UMI_SATCOM_FORMAT
TpUchar SatComCheckSum(TpUchar *pinf, TpInt32 len);
TpUint16 YawDataInitControl(SatComYawInit* yi,SatComYawFlag* yf);
TpUint16 YawDataUpdateControl(SatComYawUpdate* yu,SatComYawFlag* yf);
TpVoid LogSatComImu(Logout* lo,UmiOutput* uo,SatComImuOut* so,SatComOverRange* sr);
TpVoid LogSatComPos(Logout* lo,UmiOutput* uo,SatComPosOut* so);
TpUchar CheckOverRange(UmiOutput* uo,SatComImuOut* so,SatComOverRange* sr);
#endif
 
#ifdef UMI_FORMAT
TpInt16 UmiCheckSum(TpUchar *pinf, TpInt32 len);
#endif

TpVoid  StartPrint();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

