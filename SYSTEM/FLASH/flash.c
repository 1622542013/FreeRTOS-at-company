/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   flash.c                                                      */
/* Date:        2017.4.24                                                     */
/* Description:                                                              */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include <stdlib.h>
#include "flash.h"
#include "command.h"
#include "RM3100.h"
#include "SPI1.h"
#include "USART.h"


/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

static SysPara syspara;	/* flash para */
static uint8_t mag_para_update_flag = 1;/*  read mag parameters when power on,by default */
static uint8_t mag_data_update_flag = 1;/*  */

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/****************************************************
 * Function:    FlashInit
 * Description: Init Flash
 * Input:       none
 * Output:      none
 * Return:
*****************************************************/
TpVoid FlashInit(TpVoid)
{
	/********* ID parameters *******/
	syspara.product_id	= 00000001;
	syspara.hardware_version = 666666666;
	syspara.software_version = 888888888;
	/*******************************/
	
	/**** gnss lever arm parameters ****/
	syspara.gnss_lever[0] = 0.0f;
	syspara.gnss_lever[1] = 0.0f;
	syspara.gnss_lever[2] = 0.0f;
	
	syspara.gnss_baseline = 0.0f;
	/***********************************/
	
	/**** usart baudrate parameters ****/
	syspara.baud_usart1 	= 115200;
	syspara.baud_usart2 	= 460800;
	syspara.baud_usart6 	= 921600;
	/***********************************/
	
	syspara.appmode = LAND;
	
	/*********** mag parameters *********/
	/* mag sample rate */
	syspara.mag_sample_rate  = Counts_400;
	/* D0 matrix  */
	syspara.matrix_mag[0] = 1.0f;
	syspara.matrix_mag[1] = 0.0f;
	syspara.matrix_mag[2] = 0.0f;
	
	syspara.matrix_mag[3] = 0.0f;
	syspara.matrix_mag[4] = 1.0f;
	syspara.matrix_mag[5] = 0.0f;
	
	syspara.matrix_mag[6] = 0.0f;
	syspara.matrix_mag[7] = 0.0f;
	syspara.matrix_mag[8] = 1.0f;
	
	/* rotation matrix */
	syspara.rotation_mag[0] = 1.0f;
	syspara.rotation_mag[1] = 0.0f;
	syspara.rotation_mag[2] = 0.0f;
	
	syspara.rotation_mag[3] = 0.0f;
	syspara.rotation_mag[4] = 1.0f;
	syspara.rotation_mag[5] = 0.0f;
	
	syspara.rotation_mag[6] = 0.0f;
	syspara.rotation_mag[7] = 0.0f;
	syspara.rotation_mag[8] = 1.0f;
	
	/* bias */
	syspara.bias_mag[0] = 0.0f;
	syspara.bias_mag[1] = 0.0f;
	syspara.bias_mag[2] = 0.0f;	
  /*******************************/
	
	syspara.imu_ascii_out_rate = 0;
	syspara.ahrs_ascii_out_rate = 0;
	syspara.nav_ascii_out_rate = 0;
	syspara.avnav_ascii_out_rate = 0;
	syspara.lvnav_ascii_out_rate = 0;
	syspara.mvnav_ascii_out_rate = 0;
	
	syspara.gpgga_out_rate = 0;
	syspara.gprmc_out_rate = 0;
	
	syspara.imu_bin_out_rate = 0;
	syspara.ahrs_bin_out_rate = 0;
	syspara.nav_bin_out_rate = 0;
	syspara.avnav_bin_out_rate = 0;
	syspara.lvnav_bin_out_rate = 0;
	syspara.mvnav_bin_out_rate = 0;
	
	syspara.dev_ahrs_bin_out_rate = 0;
	syspara.dev_igm_bin_out_rate = 0;
		
	syspara.data_out_format = 0x01;
	
}

/****************************************************
 * Function:    FlashWriet
 * Description: write Flash parameters
 * Input:       none
 * Output:      none
 * Return:
*****************************************************/
TpVoid FlashWrite(TpVoid)
{	
  union
  {
    float fData;
    uint32_t iData;
  }FlashData;
		
	uint32_t Address = BASE_ADDRESS;	/* start adress */
	
	FLASH_Unlock();					/* unlock */
	FLASH_DataCacheCmd(DISABLE);	/* disabel data cache when erase flash*/ 
	FLASH_EraseSector(FLASH_Sector_1, VoltageRange_3);	/* VCC=2.7~3.6V ,use sector 1 to save parameters */
	
	/********************************* write FLAG *************************/
	FLASH_ProgramWord(Address, FLAG_FLASH);
	Address += 4;
	/********************************* write id ****************************/
	/* write product id */
	FLASH_ProgramWord(Address,syspara.product_id);
	Address += 4;
	/* write hardware id */
	FLASH_ProgramWord(Address,syspara.hardware_version);
	Address += 4;
	/* write software id */
	FLASH_ProgramWord(Address,syspara.software_version);	
	Address += 4;
	/*****************************************************************************/
	
	/********************************* write gnss lever arm***********************/
	/* write gnss lever amr */
	FlashData.fData = syspara.gnss_lever[0];
	FLASH_ProgramWord(Address,FlashData.iData);
	Address += 4;
	/* write gnss lever amr */
	FlashData.fData = syspara.gnss_lever[1];
	FLASH_ProgramWord(Address,FlashData.iData);
	Address += 4;
	/* write gnss lever amr */
	FlashData.fData = syspara.gnss_lever[2];
	FLASH_ProgramWord(Address,FlashData.iData);
	Address += 4;
	
	/* write gnss base line */
	FlashData.fData = syspara.gnss_baseline;
	FLASH_ProgramWord(Address,FlashData.iData);
	Address += 4;
	/*****************************************************************************/
	
	/********************************* write usart baudrate***********************/
	/* write usart1 baudrate */
	FLASH_ProgramWord(Address,syspara.baud_usart1);
	Address += 4;
	/* write usart2 baudrate */
	FLASH_ProgramWord(Address,syspara.baud_usart2);
	Address += 4;
	/* write usart6 baudrate */
	FLASH_ProgramWord(Address,syspara.baud_usart6);
	Address += 4;
	
	/*******************************work mode*************************************/
	/* write work mode */
	FLASH_ProgramWord(Address,syspara.appmode);
	Address += 4;
	
	/**************************** write mag parameters **************************/
	/* write mag sample rate */
	FLASH_ProgramWord(Address,syspara.mag_sample_rate);
	Address += 4;
	
	/* write mag D0 matrix */
	for(int i = 0;i<9;i++)    
	{
		FlashData.fData = syspara.matrix_mag[i];
		FLASH_ProgramWord(Address, FlashData.iData);
		Address += 4;
	}
	/* write mag rotation matrix */
	for(int i = 0;i<9;i++)    
	{
		FlashData.fData = syspara.rotation_mag[i];
		FLASH_ProgramWord(Address, FlashData.iData);
		Address += 4;		
	}
	
	/* write mag bias */
	for(int i = 0;i<3;i++)
	{
			FlashData.fData = syspara.bias_mag[i];
			FLASH_ProgramWord(Address, FlashData.iData);
			Address += 4;
	}
	/*****************************************************************************/
	
	/************************* write out data parameters *************************/
	
	/* imu ascii out */
	FlashData.fData = syspara.imu_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* ahrs ascii out */
	FlashData.fData = syspara.ahrs_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* nav ascii out */
	FlashData.fData = syspara.nav_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* avnav ascii out */
	FlashData.fData = syspara.avnav_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* lvnav ascii out */
	FlashData.fData = syspara.lvnav_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* mvnav ascii out */
	FlashData.fData = syspara.mvnav_ascii_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	
	
	/* gpgga ascii out */
	FlashData.fData = syspara.gpgga_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* gprmc ascii out */
	FlashData.fData = syspara.gprmc_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
/*--------------------------------------------bin----------------------------------------------*/	
	
	/* imu bin out */
	FlashData.fData = syspara.imu_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* ahrs bin out */
	FlashData.fData = syspara.ahrs_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* nav bin out */
	FlashData.fData = syspara.nav_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* avnav bin out */
	FlashData.fData = syspara.avnav_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* lvnav bin out */
	FlashData.fData = syspara.lvnav_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* mvnav bin out */
	FlashData.fData = syspara.mvnav_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;


/*--------------------------------------------dev----------------------------------------------*/
	
	/* dev ahrs bin out */
	FlashData.fData = syspara.dev_ahrs_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/* dev igm bin out */
	FlashData.fData = syspara.dev_igm_bin_out_rate;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	

	/*****************************************************************************/
	
	/* data out format  */
	FlashData.fData = syspara.data_out_format;
	FLASH_ProgramWord(Address, FlashData.iData);
	Address += 4;
	
	/*****************************************************************************/
	
	FLASH_DataCacheCmd(ENABLE);	/* flash write over,start data cache */
	FLASH_Lock();				/* lock flash */
}



/****************************************************
 * Function:    FlashRead
 * Description: read flash parameters,return FLAG
 * Input:       none
 * Output:      none
 * Return:
*****************************************************/
TpUint32 FlashRead(TpVoid)
{
	 union
	{
		float fData;
		uint32_t iData;
	}FlashData;
	
	uint32_t Address = BASE_ADDRESS;	/* start address */
	uint32_t Flash_Write_Flag;	    	/* FLAG */
	
	/********************************* read FLAG *************************/
	Flash_Write_Flag = (*(vu32*)Address);
	Address += 4;
	/*********************************************************************/
	
	/********************************* read id *************************/
	syspara.product_id = (*(vu32*)Address);
	Address += 4;
	
	syspara.hardware_version = (*(vu32*)Address);
	Address += 4;
	
	syspara.software_version = (*(vu32*)Address);
	Address += 4;
	/******************************************************************/
	
	/******************  read gnss lever arm *************************/
	FlashData.iData = (*(vu32*)Address);
	syspara.gnss_lever[0] = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.gnss_lever[1] = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.gnss_lever[2] = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.gnss_baseline = FlashData.fData;
	Address += 4;
	/******************************************************************/
	
	/******************  read usart baudrate *************************/
	syspara.baud_usart1 = (*(vu32*)Address);
	Address += 4;
	syspara.baud_usart2 = (*(vu32*)Address);
	Address += 4;
	syspara.baud_usart6 = (*(vu32*)Address);
	Address += 4;
	
	/******************************************************************/
	
	/******************  read work mode *************************/
	syspara.appmode = (*(vu32*)Address);
	Address += 4;
	
  /******************************************************************/
	
	/******************  read mag parameters *************************/
	/* mag sample rate */
	syspara.mag_sample_rate = (*(vu32*)Address);
	Address += 4;
	
	/* D0 matrix */
	for(int i = 0;i<9;i++)
	{
		FlashData.iData = (*(vu32*)Address);
		syspara.matrix_mag[i] = FlashData.fData;
		Address += 4;
	}
	/* rotation matrix */
	for(int i = 0;i<9;i++)
	{
		FlashData.iData = (*(vu32*)Address);
		syspara.rotation_mag[i] = FlashData.fData;
		Address += 4;

	}
	
	/* bias */
	for(int i = 0;i<3;i++)
	{
			FlashData.iData = (*(vu32*)Address);
			syspara.bias_mag[i] = FlashData.fData;
			Address += 4;
	}
	/******************************************************************/
	
	/******************  read data out parameters *************************/
	
	FlashData.iData = (*(vu32*)Address);
	syspara.imu_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.ahrs_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.nav_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.avnav_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.lvnav_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.mvnav_ascii_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.gpgga_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.gprmc_out_rate = FlashData.fData;
	Address += 4;

/*--------------------------------------------bin----------------------------------------------*/	
	
	FlashData.iData = (*(vu32*)Address);
	syspara.imu_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.ahrs_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.nav_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.avnav_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.lvnav_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.mvnav_bin_out_rate = FlashData.fData;
	Address += 4;
	
/*--------------------------------------------dev----------------------------------------------*/	
	
	FlashData.iData = (*(vu32*)Address);
	syspara.dev_ahrs_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.dev_igm_bin_out_rate = FlashData.fData;
	Address += 4;
	
	FlashData.iData = (*(vu32*)Address);
	syspara.data_out_format = FlashData.fData;
	Address += 4;

	return Flash_Write_Flag;
}


/**************************************************************************/
/*												Application program															*/
/**************************************************************************/
void GetGnssArm(float (*arm)[3])
{
	(*arm)[0] = syspara.gnss_lever[0];
	(*arm)[1] = syspara.gnss_lever[1];
	(*arm)[2] = syspara.gnss_lever[2];
}

float GetGnssBaseLine(void)
{
	return syspara.gnss_baseline;
}

uint32_t GetAppMode(void)
{
	return syspara.appmode;
}

uint32_t GetProductID(void)
{
	return syspara.product_id;
}

uint32_t GetHardwareVersion(void)
{
	return syspara.hardware_version;
}

uint32_t GetSoftwareVersion(void)
{
	return syspara.software_version;
}

TpVoid  GetGnssLever(TpFloat lever[3])
{
	lever[0] = syspara.gnss_lever[0];
	lever[1] = syspara.gnss_lever[1];
	lever[2] = syspara.gnss_lever[2];
	
}

uint32_t GetUserUsartBaudrate(void)
{
	return syspara.baud_usart2;
}

uint32_t GetGnssUsartBaudrate(void)
{
	return syspara.baud_usart1;
}

TpUint32 GetDataUsartBaudrate(TpVoid)
{
  return syspara.baud_usart6;
}


uint32_t GetMagSampleRate(void)
{
	uint32_t rate;
	
	rate = Rm3100ReadFreq(syspara.mag_sample_rate);
	
	return rate;
}

uint32_t GetMagRegisterRate(void)
{
	return syspara.mag_sample_rate;
}


void GetMatrixMag(float (*matrix_mag)[9])
{
	uint8_t i;
	
	for(i = 0;i < 9;i++)
	{
		(*matrix_mag)[i] = syspara.matrix_mag[i];
	}
}

TpVoid GetRotationMag(TpFloat (*rotation_mag)[9])
{
	uint8_t i;
	
	for(i = 0;i < 9;i++)
	{
	   (*rotation_mag)[i] = syspara.rotation_mag[i];

	}
}

void GetBiasMag(float (*bias_mag)[3])
{	
	(*bias_mag)[0] =  syspara.bias_mag[0];
	(*bias_mag)[1] =  syspara.bias_mag[1];
	(*bias_mag)[2] =  syspara.bias_mag[2];
}

/**************************************************************************/
void SetGnssArm(float arm[3])
{
	syspara.gnss_lever[0] = arm[0];
	syspara.gnss_lever[1] = arm[1];
	syspara.gnss_lever[2] = arm[2];
}

void SetGnssBaseline(float baseline)
{
	syspara.gnss_baseline = baseline;
}

void SetAppMode(uint32_t mode)
{
	syspara.appmode = mode;
}

void SetProductID(uint32_t product_id)
{
	syspara.product_id = product_id;
}

void SetHardwareVersion(uint32_t hardware_version)
{
	syspara.hardware_version = hardware_version;
}

void SetSoftwareVersion(uint32_t software_version)
{
	syspara.software_version = software_version;
}


TpBool SetUserUsartBaudrate(uint32_t baudrate)
{
	TpBool result = RESULT_ERROR;
	
	switch(baudrate)
	{
		case 4800		:	
		case 9600 	:
		case 19200 	:
		case 38400 	:
		case 76800 	:
		case 115200 :	
		case 230400 :
		case 460800 :		
									syspara.baud_usart2 = baudrate;
											
									__disable_irq();
								//	UsartConfig(GetUsartAddress(USART_2),USART_2,baudrate);
									__enable_irq();

									result = RESULT_OK;
									break;
		
		default :
									result = RESULT_PARA_NOT_VALID;
									break;
	}
	return result;
}

TpBool SetMagSampleRate(uint32_t mag_sample_rate)
{
	TpBool result = RESULT_ERROR;	
	uint32_t mag_register_rate;
	
	mag_register_rate = Rm3100ReadFreq(mag_sample_rate);
	
	if(mag_register_rate == 0)
	{
		
	}
	else if(mag_register_rate == 0xffff)
	{
		result = RESULT_PARA_NOT_VALID;	
		return result;
	}
	else
	{
		result = ChangeMagSampleRate(mag_register_rate);
		syspara.mag_sample_rate = mag_register_rate;
	}
	
	return result;
}

void SetMagCaliPara(float matrix_mag[12])
{
	uint8_t i;
  
  float bias_new[3];
  float k_new[9];
  
  for(i = 0;i < 12;i++)
	{
		if(i < 9)
		{
			k_new[i] = matrix_mag[i];/*matrix_mag from 0 to 8*/
		}
		else
		{
			bias_new[i-9] = matrix_mag[i];
		}
	}
  
  MagMatrixNewCalc(bias_new,k_new);
  
//	for(i = 0;i < 12;i++)
//	{
//		if(i < 9)
//		{
//			syspara.matrix_mag[i] = matrix_mag[i];/*matrix_mag from 0 to 8*/
//		}
//		else
//		{
//			syspara.bias_mag[i-9] = matrix_mag[i];
//		}
//	}
}

void SetMagCaliParaErase(float matrix_mag[12])
{
	uint8_t i;
  
	for(i = 0;i < 12;i++)
	{
		if(i < 9)
		{
			syspara.matrix_mag[i] = matrix_mag[i];/*matrix_mag from 0 to 8*/
		}
		else
		{
			syspara.bias_mag[i-9] = matrix_mag[i];
		}
	}
}


void SetMagBias(float bias_mag[3])
{
	uint8_t i;
	
	for(i = 0;i < 3;i++)
	{
		if(i < 3)
		{
			syspara.bias_mag[i] = bias_mag[i];/*bias_mag from 9 to 11*/
		}
	}
}
	
void SetMagMatrix(float matrix_mag[9])
{
	uint8_t i;
	
	for(i = 0;i < 9;i++)
	{
		if(i<9)
		{
			syspara.matrix_mag[i] = matrix_mag[i];/*matrix_mag from 0 to 8*/
		}
	}
}




/**************************************************************************/


/*note : Mag calibration parameter refresh required*/
void SetMagParaUpdateFlag(void)
{
	mag_para_update_flag = 1;	
}
/*note : Mag calibration parameter refresh over*/
void ClearMagParaUpdateFlag(void)
{
	mag_para_update_flag = 0;	
}
/*note : Determine whether to update mag calibration parameter*/
uint8_t GetMagParaUpdateFlag(void)
{
	return mag_para_update_flag;	
}

void SetMagDataUpdateFlag(void)
{
	mag_data_update_flag = 1;	
}

void ClearMagDataUpdateFlag(void)
{
	mag_data_update_flag = 0;	
}

/*Select mag to update*/
uint8_t GetMagDataUpdateFlag(void)
{
	return mag_data_update_flag;	
}


void Clear_Ascii_Rate(void)
{
	syspara.imu_ascii_out_rate = 0;
	syspara.ahrs_ascii_out_rate = 0;
	syspara.nav_ascii_out_rate = 0;
	syspara.avnav_ascii_out_rate = 0;
	syspara.lvnav_ascii_out_rate = 0;
	syspara.mvnav_ascii_out_rate = 0;
	syspara.gpgga_out_rate = 0;
	syspara.gprmc_out_rate = 0;
}


void Clear_BIN_Rate(void)
{
	syspara.imu_bin_out_rate = 0;
	syspara.ahrs_bin_out_rate = 0;
	syspara.nav_bin_out_rate = 0;
	syspara.avnav_bin_out_rate = 0;
	syspara.lvnav_bin_out_rate = 0;
	syspara.mvnav_bin_out_rate = 0;
	syspara.dev_ahrs_bin_out_rate = 0;
	syspara.dev_igm_bin_out_rate = 0;
}


void SetOutputRate(OutputFormat format,uint8_t rate)
{
	switch(format)
	{
		
/*-----------------------------------------------------------------------------------------------------
																							ASCII 
-----------------------------------------------------------------------------------------------------*/
		
		case	IMU_ASCII   : syspara.imu_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		
		case	AHRS_ASCII  : syspara.ahrs_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	NAV_ASCII   : syspara.nav_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	AVNAV_ASCII : syspara.avnav_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	LVNAV_ASCII : syspara.lvnav_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	MVNAV_ASCII : syspara.mvnav_ascii_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	GPGGA 		  : syspara.gpgga_out_rate = rate;
											  Clear_BIN_Rate();
											  break;
		case	GPRMC 			: syspara.gprmc_out_rate = rate;
											  Clear_BIN_Rate();
											  break;

/*-----------------------------------------------------------------------------------------------------
																					BIN
-----------------------------------------------------------------------------------------------------*/	

		case	IMU_BIN   : syspara.imu_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
		case	AHRS_BIN  : syspara.ahrs_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
		case	NAV_BIN	  : syspara.nav_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
		case	AVNAV_BIN : syspara.avnav_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
		case	LVNAV_BIN : syspara.lvnav_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
		case	MVNAV_BIN : syspara.mvnav_bin_out_rate = rate;
											Clear_Ascii_Rate();
											break;
											
/*-----------------------------------------------------------------------------------------------------
																					developer
-----------------------------------------------------------------------------------------------------*/																	
		
		case	DEV_AHRS_BIN  : syspara.dev_ahrs_bin_out_rate = rate;
													Clear_Ascii_Rate();
													break;
		
		case	DEV_NAV_BIN   : syspara.dev_igm_bin_out_rate = rate;
													Clear_Ascii_Rate();
													break;
			
		default 				:break;
	}
}


uint8_t GetOutputFormat(OutputFormat format)
{
	switch(format)
	{
		
		case	IMU_ASCII  	 	: return syspara.imu_ascii_out_rate;
		case	AHRS_ASCII  	: return syspara.ahrs_ascii_out_rate;
		case	NAV_ASCII  	 	: return syspara.nav_ascii_out_rate;
		case	AVNAV_ASCII 	: return syspara.avnav_ascii_out_rate;
		case	LVNAV_ASCII 	: return syspara.lvnav_ascii_out_rate;
		case	MVNAV_ASCII 	: return syspara.mvnav_ascii_out_rate;
		case	GPGGA 		  	: return syspara.gpgga_out_rate;
		case	GPRMC 				: return syspara.gprmc_out_rate;
		case	IMU_BIN   		: return syspara.imu_bin_out_rate;
		case	AHRS_BIN  		: return syspara.ahrs_bin_out_rate;
		case	NAV_BIN	  		: return syspara.nav_bin_out_rate;
		case	AVNAV_BIN 		: return syspara.avnav_bin_out_rate;
		case	LVNAV_BIN 		: return syspara.lvnav_bin_out_rate;
		case	MVNAV_BIN 		: return syspara.mvnav_bin_out_rate;	
		case	DEV_AHRS_BIN  : return syspara.dev_ahrs_bin_out_rate;
		case	DEV_NAV_BIN   : return syspara.dev_igm_bin_out_rate;
	
		default 				:break;
	}
	return 0x00;
}

void SetMagCaliParaBias(float bias_mag[3])
{
	uint8_t i;
	for(i = 0;i < 3;i++)
	{
      syspara.bias_mag[i] = bias_mag[i];/*bias_mag from 9 to 11*/
	}
}

void SetMagCaliParaMatrix(float matrix_mag[9])
{
	uint8_t i;
	for(i = 0;i < 9;i++)
	{
     syspara.matrix_mag[i] = matrix_mag[i];/*matrix_mag from 0 to 8*/
	}
}

float* GetMagCaliParaBias(void)
{
	return syspara.bias_mag;
}

float* GetMagCaliParaMatrix(void)
{
	return syspara.matrix_mag;
}

