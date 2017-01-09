/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   Flash.h                                                    */
/* Date:        2016.8.4                                                   */
/* Description:                                                            */
/*=========================================================================*/
#ifndef __UMI_FLASH_H_
#define __UMI_FLASH_H_

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "Ublox.h"
#include "definition.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define FLAG_FLASH      (0xAA55AA55)
#define BASE_ADDRESS    (0x08008000)
#define COMMOND_ON      (0x00000001)
#define COMMOND_OFF     (0x00000000)
/*============================================================================*/
/*                                struct define                               */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct tagSysPara
{
	Ublox ub;	
	TpUint32 id[4];
  TpUint32 baud_usart1;
  TpUint32 baud_usart2;
	TpUint32 baud_usart6;
  TpUint32 pos_freq;
  TpUint32 imu_freq;
}SysPara;

#pragma pack(pop)


/*============================================================================*/
/*                           declarations                                     */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
  
extern SysPara syspara;

TpBool   FlashInit(SysPara* sp);
TpBool   FlashWrite(SysPara* sp);
TpUint32 FlashRead(SysPara* sp);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
