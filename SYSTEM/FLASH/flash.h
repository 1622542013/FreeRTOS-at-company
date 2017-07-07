/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   flash.h                                                      */
/* Date:        2017.4.24                                                     */
/* Description:                                                              */
/*============================================================================*/

#ifndef __UMI_FLASH_H_
#define __UMI_FLASH_H_

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "definition.h"
#include "Ublox.h"
/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define FLAG_FLASH      ((uint32_t)0xAA55AA55)
#define BASE_ADDRESS    ((uint32_t)0x08004000)


#define OUTDATA_FORMAT_IMU_ASCII    ((TpUint16)0<<1)
#define OUTDATA_FORMAT_AHRS_ASCII   ((TpUint16)0<<2)
#define OUTDATA_FORMAT_AHRS_BIN     ((TpUint16)0<<3)
#define OUTDATA_FORMAT_IGM_ASCII    ((TpUint16)0<<4)
#define OUTDATA_FORMAT_IGM_BIN      ((TpUint16)0<<5)

#define COMMOND_ON      (0x00000001)
#define COMMOND_OFF     (0x00000000)

/*============================================================================*/
/*                             struct define                                  */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct _tagSysPara
{
	/* id */
	TpUint32 product_id;	
	TpUint32 hardware_version;	
	TpUint32 software_version;	
	/* gnss lever arm */
	TpFloat  gnss_lever[3];
	TpFloat  gnss_baseline;
	/* user usart baudrate */
	TpUint32 baud_usart1;	
	TpUint32 baud_usart2;	
	TpUint32 baud_usart6;
	/*APP MODE*/
	TpUint32	 appmode;
	/* mag calibration para */
	TpUint32 mag_sample_rate;	
	TpFloat  matrix_mag[9];
	TpFloat  rotation_mag[9];
	TpFloat  bias_mag[3];
	/* data out rate */
	TpUint32  imu_ascii_out_rate;
	TpUint32  ahrs_ascii_out_rate;
	TpUint32  nav_ascii_out_rate;
	TpUint32  avnav_ascii_out_rate;
	TpUint32  lvnav_ascii_out_rate;
	TpUint32  mvnav_ascii_out_rate;
	
	TpUint32  gpgga_out_rate;
	TpUint32  gprmc_out_rate;
	
	TpUint32  imu_bin_out_rate;
	TpUint32  ahrs_bin_out_rate;
	TpUint32  nav_bin_out_rate;
	TpUint32  avnav_bin_out_rate;
	TpUint32  lvnav_bin_out_rate;
	TpUint32  mvnav_bin_out_rate;
	
	TpUint32  dev_ahrs_bin_out_rate;
	TpUint32  dev_igm_bin_out_rate;
	
	/* data out format */
	TpUint32 data_out_format;
}SysPara;

#pragma pack(pop)

typedef enum
{
	IMU_ASCII,
	AHRS_ASCII,
	NAV_ASCII,
	AVNAV_ASCII,
	LVNAV_ASCII,
	MVNAV_ASCII,
	 
	GPGGA,
	GPRMC,
	
	IMU_BIN,
	AHRS_BIN,
	NAV_BIN,
	AVNAV_BIN,
	LVNAV_BIN,
	MVNAV_BIN,
	
	DEV_AHRS_BIN,
	DEV_NAV_BIN
	
}OutputFormat;


/*============================================================================*/
/*                             Function declaration                           */
/*============================================================================*/

/*************************  init,read and write flash *************************/
/* init flash */
TpVoid FlashInit(TpVoid);

/* write parameter to flash */
TpVoid FlashWrite(TpVoid);

/* read flag from flash */
TpUint32 FlashRead(TpVoid);

/***************************** get  different id   *************************/
TpUint32 GetProductID(TpVoid);
TpUint32 GetHardwareVersion(TpVoid);
TpUint32 GetSoftwareVersion(TpVoid);

/* get user usart baudrate */
TpUint32 GetUserUsartBaudrate(TpVoid);

TpUint32 GetGnssUsartBaudrate(TpVoid);

TpUint32 GetDataUsartBaudrate(TpVoid);

/* get gnss lever arm */
TpVoid   GetGnssLever(TpFloat lever[3]);

/***************************** get  mag  parameter *************************/
TpUint32 GetMagSampleRate(TpVoid);
TpVoid   GetMatrixMag(TpFloat (*matrix_mag)[9]);
TpVoid   GetRotationMag(TpFloat (*rotation_mag)[9]);
TpVoid   GetBiasMag(TpFloat (*bias_mag)[3]);

/***************************set  different id*********************************/
TpVoid SetProductID(TpUint32  product_id);
TpVoid SetHardwareVersion(TpUint32 hardware_version);
TpVoid SetSoftwareVersion(TpUint32 software_version);
TpVoid SetGnssLever(TpFloat   gnss_lever);
TpBool SetUserUsartBaudrate(uint32_t baudrate);

/***************************set  mag  parameter*********************************/
TpBool SetMagSampleRate(uint32_t mag_sample_rate);
void SetMagCaliPara(float matrix_mag[12]);
void SetMagParaUpdateFlag(void);
void ClearMagParaUpdateFlag(void);
uint8_t GetMagParaUpdateFlag(void);

void SetMagCaliParaMatrix(float matrix_mag[9]);
void SetMagCaliParaBias(float bias_mag[3]);
float* GetMagCaliParaBias(void);
float* GetMagCaliParaMatrix(void);



void SetMagDataUpdateFlag(void);
void ClearMagDataUpdateFlag(void);
uint8_t GetMagDataUpdateFlag(void);

void SetMagBias(float bias_mag[3]);	
void SetMagMatrix(float matrix_mag[9]);

uint32_t GetAppMode(void);
void SetAppMode(uint32_t mode);
void SetGnssArm(float arm[3]);
void SetGnssBaseline(float baseline);

void GetGnssArm(float (*arm)[3]);
float GetGnssBaseLine(void);


uint32_t GetMagRegisterRate(void);
TpVoid  SetOutputRate(OutputFormat format,uint8_t rate);
TpUchar GetOutputFormat(OutputFormat format);

#endif 	/* __UMI_FLASH_H_ */

