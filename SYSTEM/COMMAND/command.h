/*=========================================================================*/
/* Copyright (C), 2017, Yagro Co., Ltd.                                    */
/* File name:   commond.h                                                  */
/* Date:        2017.5.2                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_COMMAND_H
#define __UMI_COMMAND_H

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "usart.h"
#include "globals.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define COM_ARM3_TO_ARM2				USART_6
#define COM_ARM3_TO_USER        USART_2


#define  OUTPUT_ID_IMU_ASCII     ((TpUchar)1)
#define	 OUTPUT_ID_AHRS_ASCII    ((TpUchar)2)
#define	 OUTPUT_ID_AHRS_BIN      ((TpUchar)3)
#define	 OUTPUT_ID_IGM_ASCII     ((TpUchar)4)
#define	 OUTPUT_ID_IGM_BIN       ((TpUchar)5)

#define  BIN_HEAD_0            ((TpUchar)0xAB)
#define  BIN_HEAD_1            ((TpUchar)0x12)

#define  COMMOND_START         ((TpUchar)0x24) // '$'

#define  COMMOND_END_1				 (',')
#define  COMMOND_END_2				 ('*')
#define  COMMOND_END_f				 ('f')
#define  COMMOND_END_5				 ('\r')
#define  COMMOND_END_6				 ('\n')
#define  COMMOND_END         	 (",*ff\r\n")

#define  LETTER_CAPITAL_A       ((TpUchar)0x41)  /* 'A' */
#define  LETTER_CAPITAL_Z       ((TpUchar)0x5a)  /* 'Z' */
#define  CAPITAL_LOWERCASE_LEN  ((TpUchar)0x20)
#define  LETTER_STAR_HEX        ((TpUchar)0x2A) // '*'
#define  LETTER_COMMA_HEX       ((TpUchar)0x2C) // ','
#define  COMMA_CHARACTER_ASCII  (",")

/************************ ascii commond  *******************************/

/* ascii head */
#define ASCII_CLASS_HEAD  				("$cmd,")

/* config ok or error */
#define FREEDBACK_OK 							("$cmd,Config,ok*ff\r\n")
#define FREEDBACK_ERROR  					("$cmd,Config,error*ff !!!\r\n")
#define NOT_A_VALID_CONFIG  			("$cmd,Config,Parameter is Invalid !!!\r\n")
#define NOT_A_VALID_COMMAND  			("$cmd,Command is Invalid !!!\r\n")

/************************ set commond****************************/
/* ascii head of set */
#define ASCII_CLASS_SET 					("$cmd,set,")
/* set user usart baudrate */
#define SET_BAUDRATE  						("$cmd,set,com,baudrate,")
/* set product id */
#define SET_PRODUCT_ID 						("$cmd,set,product,id,")
/* set hardware version */
#define SET_HARD_VERSION 					("$cmd,set,version,hardware,")
/* set software version */
#define SET_SOFT_VERSION 					("$cmd,set,version,software,")
/* set mag sample rate */
#define SET_MAG_RATE      			  ("$cmd,set,mag,samplerate,")
/* set mag cali para */
#define SET_MAG_CAL_PARA 					("$cmd,set,mag,calpara,")
/* erase mag cali para */
#define SET_MAG_CAL_PARA_ERASE  	("$cmd,set,mag,calerase,*ff")
/* mag cali online */
#define SET_MAG_CAL_ONLINE        ("$cmd,set,mag,calon,*ff")
/* settings save or restore */
#define ALL_SETTING_SAVE					("$cmd,save,config,*ff")
#define ALL_SETTING_RESTORE 			("$cmd,freset,*ff")

/************************ get commond****************************/
/* ascii head of get */
#define ASCII_CLASS_GET  					("$cmd,get,")
/* user baudrate */
#define GET_BAUDRATE 							("$cmd,get,usart,baudrate,*ff")
#define GET_BAUDRATE_OUT 					("$cmd,get,usart,baudrate,%d,*ff\r\n")
/* product id*/
#define GET_PRODUCT_ID 						("$cmd,get,productid,*ff")
#define GET_PRODUCT_ID_OUT 				("$cmd,get,productid,%d,*ff\r\n")
/* hardware version */
#define GET_HARD_VERSION 					("$cmd,get,version,hardware,*ff")
#define GET_HARD_VERSION_OUT 			("$cmd,get,version,hardware,%d,*ff\r\n")
/* software version */
#define GET_SOFT_VERSION 					("$cmd,get,version,software,,*ff")
#define GET_SOFT_VERSION_OUT 			("$cmd,get,version,software,,%d,*ff\r\n")
/* mag sample rate */
#define GET_MAG_RATE 							("$cmd,get,mag,samplerate,*ff")
#define GET_MAG_RATE_OUT 					("$cmd,get,mag,samplerate,%dHZ,*ff\r\n")
/* mag cali parameters */
#define GET_MAG_CAL_PARA 					("$cmd,get,mag,calpara,*ff")
#define GET_MAG_CAL_PARA_OUT 			("$cmd,get,mag,calpara,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,*ff\r\n")

/* mag cali para user out */
#define MAG_CAL_PARA_USER_OUT 	  ("$cmd,mag,calipara,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,*ff\r\n")
/************************ output commond *******************************/

#define ASCII_CLASS_OUTPUT  			("$cmd,output,")
#define OUTPUT_IMU_ASCII_RATE 		("$cmd,output,gpimu,ascii,")
#define OUTPUT_AHRS_ASCII_RATE 		("$cmd,output,gpahrs,ascii,")
#define OUTPUT_NAV_ASCII_RATE 		("$cmd,output,gpnav,ascii,")
#define OUTPUT_AVNAV_ASCII_RATE 	("$cmd,output,avnav,ascii,")
#define OUTPUT_LVNAV_ASCII_RATE 	("$cmd,output,lvnav,ascii,")
#define OUTPUT_MVNAV_ASCII_RATE 	("$cmd,output,mvnav,ascii,")

#define OUTPUT_GPGGA_RATE 				("$cmd,output,gpgga,")
#define OUTPUT_GPRMC_RATE 				("$cmd,output,gprmc,")

#define OUTPUT_IMU_BIN_RATE 			("$cmd,output,gpimu,bin,")
#define OUTPUT_AHRS_BIN_RATE 			("$cmd,output,gpahrs,bin,")
#define OUTPUT_NAV_BIN_RATE 			("$cmd,output,gpnav,bin,")
#define OUTPUT_AVNAV_BIN_RATE 		("$cmd,output,avnav,bin,")
#define OUTPUT_LVNAV_BIN_RATE 		("$cmd,output,lvnav,bin,")
#define OUTPUT_MVNAV_BIN_RATE 		("$cmd,output,mvnav,bin,")

#define OUTPUT_DEV_AHRS_BIN_RATE 	("$cmd,output,dev*gpahrs,bin,")
#define OUTPUT_DEV_IGM_BIN_RATE 	("$cmd,output,dev*gpigm,bin,")
/* commond sent to arm2 and arm1  */
/************************ set commond****************************/
#define SET_ACC_PARA_COMMAND  		("$cmd,set,acc,calpara,")
#define SET_GYRO_PARA_COMMAND  		("$cmd,set,gyro,calpara,")
#define ERASE_ACC_GYRO_PARA    		("$cmd,set,erase,accgyrocalpara,*ff")
#define GET_ACC_PARA_COMMAND  		("$cmd,get,acc,cal_para,*ff")
#define GET_GYRO_PARA_COMMAND  		("$cmd,get,gyro,cal_para,*ff")

/*-----------------------------------------------------------------*/
#define SET_NAV_WORK_MODE 				("$cmd,set,appmode,")
#define SET_LEVER_ARM 						("$cmd,set,gnss,leverarm,")
#define SET_BASE_LINE 						("$cmd,set,gnss,baseline,")
/************************ get commond****************************/
#define GET_NAV_WORK_MODE 				("$cmd,get,appmode,*ff")
#define GET_LEVER_ARM 						("$cmd,get,gnss,leverarm,*ff")
#define GET_BASE_LINE 						("$cmd,set,gnss,baseline,")

#define NAV_LAND_MODE 						("land")
#define NAV_AIR_MODE 							("air")
#define NAV_OCEAN_MODE 						("ocean")

#define NAV_LAND_MODE_OUT					("Navigation mode is land *ff\r\n")
#define NAV_AIR_MODE_OUT 					("Navigation mode is air *ff\r\n")		
#define NAV_OCEAN_MODE_OUT				("Navigation mode is ocean *ff\r\n")		


/************************ ARM1,2 freedback****************************/



#define OUTPUT_RATE_MAX						(100) /*100hz */

#pragma pack(push)
#pragma pack(1)



typedef struct 
{
  TpDouble  lat;     /* lat in degree */
  TpDouble  lon;     /* lon in degree */
  TpFloat   alt;     /* alt in m */
  TpFloat   ve;      /* ve in m/s */
  TpFloat   vn;      /* vn in m/s */
  TpFloat   vu;      /* vu in m/s */
  TpFloat    pitch;   /* pitch in degree */
  TpFloat   roll;   /* roll in degree */
  TpFloat   heading; /* heading in degree */
	TpFloat   quat[4]; /* Quaternions*/	
  TpInt16   gbx;     /* gbx/1000  = gyro bias in d/s */
  TpInt16   gby;     /* gby/1000  = gyro bias in d/s */
  TpInt16   gbz;     /* gbz/1000  = gyro bias in d/s */
  TpInt16   abx;     /* abx/1000  = acc bias in m/s2 */
  TpInt16   aby;     /* aby/1000  = acc bias in m/s2 */
  TpInt16   abz;     /* abz/1000  = acc bias in m/s2 */
  TpInt16   misx;    /* misx/1000 = mis in degree */
  TpInt16   misy;    /* misy/1000 = mis in degree */
  TpInt16   misz;    /* misz/1000 = mis in degree */
  TpInt32   resv[4]; /* reserved*/
} UmiNav;

typedef struct 
{
  TpFloat    gyox;
  TpFloat    gyoy;
  TpFloat    gyoz;
	TpInt16  	 gyo_temp;
	
  TpFloat    accx;
  TpFloat    accy;
  TpFloat    accz;  
  TpInt16  	 acc_temp;

  TpFloat    altitude;
  TpInt16  	 bmp_temp;
}UmiImu;


typedef struct 
{
  TpUint32    tow_pps;
  TpUint16    weekn;
  TpUint16    gflag;
  TpDouble   	lat;
  TpDouble  	lon;
  TpFloat    	alt;
  TpFloat    	spd;
  TpFloat    	heading;
  TpFloat    	orient;
  TpUint16  	hdop;
} UmiGnss;




typedef struct 
{
  TpFloat  magx;
  TpFloat  magy;
  TpFloat  magz;
  TpUint16 mag_temp;
} UmiMag;


typedef struct
{
  TpUchar  			  head[2];
  TpUint32  			index;
  TpUint16  			week;	
  TpUint32    		tow_imu; /* tow_imu/1000.0 = tow in second */
  UmiNav          nav;     /* Nav Data */
  UmiImu     			imu;    /* VTI Imu Data */
  UmiMag          mag;     /* Mag Data */
  UmiGnss         gnss;    /* Gnss data */
  TpUint16 			  check;
} UmiIgmBin;

typedef struct tagUmiMagSend
{
	TpUint16 head;
	TpFloat  magx;
  TpFloat  magy;
  TpFloat  magz;
	TpUchar  check;
}UmiMagBin;

typedef struct _tagUmiAhrsBin
{
  TpUint16 head;
	TpUchar  mag_id;
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
	TpFloat	 temp_mag;
	TpFloat  quat[4]; 
	TpUchar  check;
	TpUchar  end;
}UmiAhrsBin;

typedef struct _tagCommondFlag
{
	TpUchar  magcali_online;
	TpUchar  magpara_update;

}CommondFlag;


#pragma pack(pop)



void feedback_ok(void);
void feedback_err(void);

TpBool DecodeCommond(uint8_t * pBuf,uint16_t len);

void Push_into_main_buff(char* buff,uint16_t length);
void Push_into_interrupt_buff(char* buff,uint16_t length);


/* Logout Data  */
TpVoid LogInterrupt(TpVoid);
TpVoid LogMain(TpVoid);


/*****************************************/

TpBool My_atoi(const char* buff,int32_t* num);

//short int CheckSum(unsigned char *pinf, int len);
TpBool DecodeARM2Bin(TpUchar* pUsart_buff,TpUint16 len,UmiIgmBin* pUmiOutput);
TpBool DecodeAsciiCommond(Package* pa);
TpBool GetAsciiCommond(uint8_t * pBuf,uint16_t len,Package* pa);
TpBool GetLetterField(TpUchar* pBuf,Package* pa,TpUchar* field[],TpUchar* num);


TpVoid OutMagCaliOnlinePara(TpFloat bias[3],TpFloat matrix[9]);
CommondFlag* GetCommondFlag(TpVoid);
#endif
