/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   Flash.c                                                       */
/* Date:        2016.8.4                                                     */
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/
#include "flash.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

SysPara syspara;

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

TpBool FlashInit(SysPara* sp)
{
  TpBool resutlt = INLIB_ERROR;
  
  sp->ub.GNGGA = COMMOND_ON;
  sp->ub.GNRMC = COMMOND_ON;
  
	sp->ub.GNDTM = COMMOND_OFF;
	sp->ub.GNGBS = COMMOND_OFF;
	sp->ub.GNGLL = COMMOND_OFF;
	sp->ub.GNGNS = COMMOND_OFF;
	sp->ub.GNGRS = COMMOND_OFF;
	sp->ub.GNGSA = COMMOND_OFF;
	sp->ub.GNGST = COMMOND_OFF;
	sp->ub.GNGSV = COMMOND_OFF;
	sp->ub.GNVLW = COMMOND_OFF;
	sp->ub.GNVTG = COMMOND_OFF;
	sp->ub.GNZDA = COMMOND_OFF;
	
	sp->ub.Output_Rate = 0x00000005;
	
	sp->ub.GPS_Upload = COMMOND_OFF;
	
	sp->id[0] = 1;
  sp->id[1] = 0;
  sp->id[2] = 1;
  sp->id[3] = 0;
  
  sp->baud_usart1 = 115200;
  sp->baud_usart2 = 115200;
	sp->baud_usart6 = 921600;
  sp->pos_freq = 1;
  sp->imu_freq = 100;
  
  resutlt = INLIB_OK;
  return resutlt;
}

TpBool FlashWrite(SysPara* sp)
{
   TpBool resutlt = INLIB_ERROR;
  
	uint32_t Address = BASE_ADDRESS;
	
	FLASH_Unlock();
	FLASH_DataCacheCmd(DISABLE);
	FLASH_EraseSector(FLASH_Sector_2, VoltageRange_3);	
	
	FLASH_ProgramWord(Address, FLAG_FLASH);
	Address += 4;
	
	FLASH_ProgramWord(Address, sp->ub.GNGGA);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNRMC);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNVTG);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGSA);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGSV);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGLL);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGRS);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGST);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNZDA);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGBS);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNDTM);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNGNS);
	Address += 4;
	FLASH_ProgramWord(Address, sp->ub.GNVLW);
	Address += 4;
	
	FLASH_ProgramWord(Address, sp->ub.Output_Rate);
	Address += 4;
	
	FLASH_ProgramWord(Address, sp->ub.GPS_Upload);
	Address += 4;
	
/* init print info  */
	
	FLASH_ProgramWord(Address, sp->id[0]);
	Address += 4;
	FLASH_ProgramWord(Address, sp->id[1]);
	Address += 4;
  FLASH_ProgramWord(Address, sp->id[2]);
	Address += 4;
  FLASH_ProgramWord(Address, sp->id[3]);
	Address += 4;
  FLASH_ProgramWord(Address, sp->baud_usart1);
	Address += 4;
  FLASH_ProgramWord(Address, sp->baud_usart2);
	Address += 4;
	FLASH_ProgramWord(Address, sp->baud_usart6);
	Address += 4;
  FLASH_ProgramWord(Address, sp->pos_freq);
	Address += 4;
  FLASH_ProgramWord(Address, sp->imu_freq);
	
	
	FLASH_DataCacheCmd(ENABLE);
	FLASH_Lock();
  
  resutlt = INLIB_OK;
  return resutlt;
}

uint32_t FlashRead(SysPara* sp)
{
   
	uint32_t Address = BASE_ADDRESS;
	uint32_t Flash_Write_Flag;
	
	Flash_Write_Flag = (*(vu32*)Address);
	Address += 4;

	sp->ub.GNGGA = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNRMC = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNVTG = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGSA = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGSV = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGLL = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGRS = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGST = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNZDA = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGBS = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNDTM = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNGNS = (*(vu32*)Address);
	Address += 4;
	sp->ub.GNVLW = (*(vu32*)Address);
	Address += 4;
	
	sp->ub.Output_Rate = (*(vu32*)Address);
	Address += 4;
	
	sp->ub.GPS_Upload = (*(vu32*)Address);
	Address += 4;
	
	sp->id[0] = (*(vu32*)Address);
	Address += 4;
  sp->id[1] = (*(vu32*)Address);
	Address += 4;
  sp->id[2] = (*(vu32*)Address);
	Address += 4;
  sp->id[3] = (*(vu32*)Address);
	Address += 4; 
  sp->baud_usart1 = (*(vu32*)Address);
	Address += 4; 
  sp->baud_usart2 = (*(vu32*)Address);
	Address += 4; 
	sp->baud_usart6 = (*(vu32*)Address);
	Address += 4; 
  sp->pos_freq = (*(vu32*)Address);
	Address += 4; 
  sp->imu_freq = (*(vu32*)Address);
	
	return Flash_Write_Flag;
}

