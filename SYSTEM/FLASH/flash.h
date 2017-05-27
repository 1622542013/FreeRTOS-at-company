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
	/* user usart baudrate */
	TpUint32 baud_usart1;	
	TpUint32 baud_usart2;	
	TpUint32 baud_usart6;	
	/* mag calibration para */
	TpUint32 mag_sample_rate;	
	TpFloat  matrix_mag[9];
	TpFloat  rotation_mag[9];
	TpFloat  bias_mag[3];
	/* data out rate */
	TpUchar  imu_ascii_out_rate;
	TpUchar  ahrs_ascii_out_rate;
	TpUchar  ahrs_bin_out_rate;
	TpUchar  igm_ascii_out_rate;
	TpUchar  igm_bin_out_rate;
	/* data out format */
	TpUint16 data_out_format;
}SysPara;

#pragma pack(pop)

typedef enum
{
	IMU_ASCII  = 1,
	AHRS_ASCII = 2,
	AHRS_BIN   = 3,
	IGM_ASCII  = 4,
	IGM_BIN    = 5
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


void SetMagDataUpdateFlag(void);
void ClearMagDataUpdateFlag(void);
uint8_t GetMagDataUpdateFlag(void);


uint32_t GetMagRegisterRate(void);
TpVoid  SetOutputRate(OutputFormat format,uint8_t rate);
TpUchar GetOutputFormat(OutputFormat format);

#endif 	/* __UMI_FLASH_H_ */

