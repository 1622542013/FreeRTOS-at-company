/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
<<<<<<< HEAD
/* File name:   globals.h                                                      */
/* Date:        2014.4.29                                                     */
/* Description: globals.h                                                     */
=======
/* File name:   user_define.h                                                      */
/* Date:        2016.5.18                                                     */
/* Description: gnss.c                                                       */
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/*============================================================================*/

#ifndef  __UMI_USER_DEFINE_H
#define  __UMI_USER_DEFINE_H

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"
<<<<<<< HEAD
 
=======

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

<<<<<<< HEAD
#define  DATA_FROM_ARM2_HEAD_1  ((TpUchar)0xCD)
#define  DATA_FROM_ARM2_HEAD_2  ((TpUchar)0x34)

#define  MAG_BIN_HEAD           ((TpUint16))

#define  DATA_FROM_ARM2_HEAD    ((TpUint16)0x34CD)

#define F32_MACHEPS             (2.22045e-16)

#define RESULT_OK               				(1)	
#define RESULT_ERROR            				(0)													 
#define RESULT_PARA_NOT_VALID           (-1)
#define RESULT_OUTPUT_RATE_TOOHIGH      (-2)
#define NO_ANSWER               				(-3)
#define RESULT_COMMAND_INVALID          (-4)

#define NMEA_USE                (1)
#define GPS_UTC                 (17000)
#define Cycle_100MS             (10)
#define Cycle_200MS             (20)




#define NMEA_ON
=======
#define NMEA_USE                (1)
#define GPS_UTC                 (17000)
#define Cycle_100MS             (10)
#define Cycle_200MS             (20)
#define PROJECT_DATE_RATE       (100)

#define GNSS_ON
//#define RM3100_ON
#define UBLOX_ON
#define NMEA_ON

#ifdef  RM3100_ON
#define SPI1_ON
#endif

#define UMI_FORMAT
#define UMI_SATCOM_FORMAT
#define UMI_BINARY_VERISON (3)

#ifdef UMI_SATCOM_FORMAT
/* header */
#define HEADER_BYTE_FIRST           ((TpUchar)0xBD)
#define HEADER_BYTE_SECOND          ((TpUchar)0xDB)
#define HEADER_BYTE_RESET           ((TpUchar)0xDE)
/* msg id */
#define MSG_ID_YAW_INIT             ((TpUchar)0xA4)
#define MSG_ID_YAW_UPDATE           ((TpUchar)0xA5)
#define MSG_ID_AHRS_IMU_OUT         ((TpUchar)0x04)
#define MSG_ID_AHRS_POS_OUT         ((TpUchar)0x05)

#define MSG_ID_ARM3_RESET_1         ((TpUchar)0x06)
#define MSG_ID_ARM3_RESET_2         ((TpUchar)0x07)
#define MSG_ID_ARM3_RESET_3         ((TpUchar)0x08)
/* att flag */
#define FLAG_VALID_INIT_ROLL        ((TpUchar)1<<0)
#define FLAG_VALID_INIT_PITCH       ((TpUchar)1<<1)
#define FLAG_VALID_INIT_YAE         ((TpUchar)1<<2)
/* att init control  */
#define ATT_INIT_FACTOR_MAX         (100)
#define ATT_INIT_FACTOR_MIN         ((TpFloat)1.0/ATT_INIT_FACTOR_MAX)
#define QUALITY_YAW_INIT_VALUE      ((TpFloat)2.0)
#define QUALITY_YAW_INIT            ((TpInt16)ATT_INIT_FACTOR_MAX*QUALITY_YAW_INIT_VALUE)

/* att update control  */
#define ATT_UP_FACTOR_MAX           (100)
#define ATT_UP_FACTOR_MIN           ((TpFloat)1.0/ATT_UP_FACTOR_MAX)
#define QUALITY_YAW_UP_VALUE        ((TpFloat)2.0)
#define QUALITY_YAW_UPDATE          ((TpInt16)ATT_UP_FACTOR_MAX*QUALITY_YAW_UP_VALUE)

/* data factor  */
#define IMU_OUT_FACTOR_MAX          (100)
#define IMU_OUT_FACTOR_MIN          ((TpFloat)1.0/IMU_OUT_FACTOR_MAX) 
/* mode */
#define MODE_VEHICLE                ((TpUchar)0)
#define MODE_SHIP                   ((TpUchar)1)
#define DEBUG1_DEFAULT              ((TpUchar)0)

/* info and factor */

#define INFO_INIT                   ((TpUint16)0x0520)
#define INFO_OVER_RANGE             ((TpUint16)0x01)
#define INFO_NO_OVER_CNT            (100)

#define INFO_RANGE_FACTOR           (32768.0f)
#define INFO_RANGE_ATT              (360.0f)
#define INFO_RANGE_GYO              (150.0f)
#define INFO_RANGE_ACC              (2.0f)
#define INFO_RANGE_TEMP             (200.0f)

#define FACTOR_ATT                  (INFO_RANGE_FACTOR/INFO_RANGE_ATT)
#define FACTOR_GYO                  (INFO_RANGE_FACTOR/INFO_RANGE_GYO)
#define FACTOR_ACC                  (INFO_RANGE_FACTOR/INFO_RANGE_ACC)
#define FACTOR_TEMP                 (INFO_RANGE_FACTOR/INFO_RANGE_TEMP)
#define FACTOR_TMEP_OLD             (16.0)
#endif


/*  add for VG and AHRS*/
#define FSM_STATE_INIT             ((unsigned int)0)
#define FSM_STATE_VG               ((unsigned int)1<<0)
#define FSM_STATE_AHRS             ((unsigned int)1<<1)
#define FSM_STATE_NAV              ((unsigned int)1<<2)


//#define DEBUG_MODE

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                             struct define                                  */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

<<<<<<< HEAD
typedef struct
{
	TpChar  buf[512];
	TpUint16 num;
	TpUchar  start;
	TpUint16 pt ;
  TpUchar  flag;
}Package;

=======
typedef struct tagUmiNav
{
  TpDouble  lat;     /* lat in degree */
  TpDouble  lon;     /* lon in degree */
  TpFloat   alt;     /* alt in m */
  TpFloat   ve;      /* ve in m/s */
  TpFloat   vn;      /* vn in m/s */
  TpFloat   vu;      /* vu in m/s */
  TpFloat   pitch;   /* pitch in degree */
  TpFloat   roll;    /* roll in degree */
  TpFloat   heading; /* heading in degree */
  TpInt16   gbx;     /* gbx/1000  = gyro bias in d/s */
  TpInt16   gby;     /* gby/1000  = gyro bias in d/s */
  TpInt16   gbz;     /* gbz/1000  = gyro bias in d/s */
  TpInt16   abx;     /* abx/1000  = acc bias in m/s2 */
  TpInt16   aby;     /* aby/1000  = acc bias in m/s2 */
  TpInt16   abz;     /* abz/1000  = acc bias in m/s2 */
#if (UMI_BINARY_VERISON<=1)
  TpInt16   misx;    /* misx/1000 = mis in degree */
  TpInt16   misy;    /* misy/1000 = mis in degree */
  TpInt16   misz;    /* misz/1000 = mis in degree */
#endif
#if (UMI_BINARY_VERISON>=3)
#ifdef UMI_SATCOM_FORMAT
  TpUchar  fsm_state;
  TpUint32  timestamp;
#endif
#endif 
} UmiNav;


typedef struct 
{
  float  gyox;
  float  gyoy;
  float  gyoz;
  float  accx;
  float  accy;
  float  accz;
  short  tmpx; /* tmpx/100 = temp in degree celsius */
  short  tmpy; /* tmpx/100 = temp in degree celsius */
  short  tmpz; /* tmpx/100 = temp in degree celsius */
}UmiImuVti;

typedef struct tagUmiImuOut
{
  TpUint16 flag;
  TpFloat  gyox;
  TpFloat  gyoy;
  TpFloat  gyoz;
  TpFloat  accx;
  TpFloat  accy;
  TpFloat  accz;
  TpInt16  tmp_Imu;
  TpFloat  alt;
  TpInt16  tmp_bmp;
}UmiImuOut;

typedef struct 
{
  TpUint32   tow_pps;
	TpUint16   weekn;
  TpUint16   gflag;
  TpDouble   lat;
  TpDouble   lon;
  TpFloat    alt;
  TpFloat    spd;
  TpFloat    heading;
  TpFloat    orient;
#ifdef UMI_SATCOM_FORMAT
	TpFloat    orient_q;
	TpUchar    ack;
#endif
  TpUint16   hdop;
} UmiGnss;

typedef struct tagUmiImuENU
{
  TpFloat  gyox;
  TpFloat  gyoy;
  TpFloat  gyoz;
  TpFloat  accx;
  TpFloat  accy;
  TpFloat  accz;
}UmiImuENU;

typedef struct tagUmiImuSt
{
  TpFloat  gyox;
  TpFloat  gyoy;
  TpFloat  gyoz;
  TpFloat  accx;
  TpFloat  accy;
  TpFloat  accz;
  TpInt16  tmp;  /* tmp/100 = temp in degree celsius */
}UmiImuSt;

typedef struct 
{
  TpFloat magx;
  TpFloat magy;
  TpFloat magz;
  TpInt16 tmpm;
} UmiMag;


typedef struct
{
  unsigned short  head;
  unsigned int    tow_imu; /* tow_imu/1000.0 = tow in second */
  UmiNav          nav;     /* Nav Data */
  UmiImuVti       imuv;    /* VTI Imu Data */
#if (UMI_BINARY_VERISON<=1)
  UmiImuSt        imus;    /* ST Imu Data */ 
	UmiMag          mag;     /* Mag Data */
#endif

  UmiGnss         gnss;    /* Gnss data */
  unsigned short  check;
} UmiOutput;

typedef struct tagUmiMagSend
{
	TpUint16 head;
	TpFloat  magx;
  TpFloat  magy;
  TpFloat  magz;
	TpUchar  check;
}UmiMagSend;

typedef struct tagUmiOutIMU
{
  double   dAx;
	double   dAy;
	double   dPitch;
	double   dRoll;
}UmiOutIMU;

/////////////////////////////////////////////////////////////////////
/* add for 54 suo */
typedef struct tagUmiYawInit
{
	TpUchar header_first;
	TpUchar header_second;
	TpUchar msg_id;
	TpInt16 roll;
	TpInt16 pitch;
	TpInt16 yaw;
	TpInt16 roll_q;
	TpInt16 pitch_q;
	TpInt16 yaw_q;
	TpUchar ack;
	TpUchar status;
	TpUchar check;
}SatComYawInit;

typedef struct tagUmiYawUpdate
{
	TpUchar header_first;
	TpUchar header_second;
	TpUchar msg_id;
	TpInt16 roll;
	TpInt16 pitch;
	TpInt16 yaw;
	TpInt16 roll_q;
	TpInt16 pitch_q;
	TpInt16 yaw_q;
	TpUchar ack;
	TpUchar status;
	TpUchar check;
}SatComYawUpdate;

typedef struct tagUmiYawFlag
{
  TpUchar init_rec;
	TpUchar update_rec;
	TpUchar init_ok;
	TpUchar update_ok;
}SatComYawFlag;

typedef struct tagSatComImuOut
{
	TpUchar  header_first;
	TpUchar  header_second;
	TpUchar  msg_id;
  TpInt16  roll;
	TpInt16  pitch;
	TpInt16  yaw;
	TpUchar  ack;
	TpUchar  mode;
	TpInt16  debug1;
	TpInt16  gyox;
	TpInt16  gyoy;
	TpInt16  gyoz;
	TpInt16  accx;
	TpInt16  accy;
	TpInt16  accz;
	TpInt16  temp;
	TpUint32 timestamp;
	TpUint16 info;
	TpUchar  check;
}SatComImuOut;

typedef struct tagSatComPosOut
{
  TpUchar  header_first;
	TpUchar  header_second;
	TpUchar  msg_id;
	TpDouble lat;
	TpDouble lon;
	TpFloat  alt;
	TpFloat  ve;
	TpFloat  vn;
	TpFloat  vu;
	TpUchar  check;	
}SatComPosOut;

typedef struct tagSatComOverRange
{
	TpUchar over_gyox;
	TpUchar over_gyoy;
	TpUchar over_gyoz;
	TpUchar over_accx;
	TpUchar over_accy;
	TpUchar over_accz;
	TpUchar over_flag;
	TpUint16 no_over_cnt;
}SatComOverRange;

////////////////////////////////////////////////////////////////////////
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
#pragma pack(pop)

/*============================================================================*/
/*                               declaration                             */
/*============================================================================*/


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

<<<<<<< HEAD
/*******************************************************/

	
TpUchar CheckSumByte(TpUchar* Buffer, TpUint16 Length);
short int CheckSum(unsigned char *pinf, int len);
TpBool My_atoi(const char* buff,int32_t* num);
	
=======
extern UmiOutput st_UmiOutput;
extern UmiOutIMU st_UmiOutIMU;
extern UmiMagSend    umiMagSend;
	
#ifdef UMI_SATCOM_FORMAT
extern SatComYawInit    satComYawInit;
extern SatComYawUpdate  satComYawUpdate;
extern SatComYawFlag    satComYawFlag;
extern SatComImuOut     satComImuOut;
extern SatComPosOut     satComPosOut;
extern SatComOverRange  satComOverRange;
#endif	
	
	
extern uint8_t outgps_flag;
extern uint8_t outimu_flag;


extern uint8_t outimu_len;
extern uint8_t outimu_buf[50];
extern uint8_t outmis_flag;
extern TpUint32 logtimer;
extern uint8_t rec_reply;
  
extern TpUchar flag_throughgps;
  
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

