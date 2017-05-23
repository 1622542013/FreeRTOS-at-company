/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   config.h                                                */
/* Date:        2017.4.25                                                   */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_HW_CONFIG_H_
#define __UMI_HW_CONFIG_H_

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "stm32f4xx.h"
#include "globals.h"
#include "usart.h"

/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define  CONFIG_OPEN          (1)
#define  CONFIG_CLOSE         (0)

#define GNSS_OPEN             CONFIG_OPEN
#define RM3100_OPEN           CONFIG_OPEN
#define UBLOX_OPEN            CONFIG_OPEN
#define EXTI_LINE1_OPEN       CONFIG_OPEN

#if (RM3100_OPEN)
#define SPI1_OPEN             CONFIG_OPEN
#else
#define SPI1_OPEN             CONFIG_CLOSE
#endif

/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

TpBool HardWareInit(TpVoid);
TpVoid EXTI_Config(TpVoid);
TpBool TIM_Config(TpVoid);
TpBool GPIO_Config(TpVoid);
  
TpBool StartupPrint(TpVoid);

TpVoid UbloxConfig(TpVoid);
  
TpVoid NVIC_Config(TpVoid);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

