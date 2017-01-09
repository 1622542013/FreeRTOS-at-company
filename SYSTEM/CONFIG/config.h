/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   hw_config.h                                                */
/* Date:        2016.8.4                                                   */
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

#define SYSTICK_MS       (8400)

#define EXTI_LINE1_ON


/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

TpBool HardWareInit(TpVoid);
TpBool Delay_ms(u16 nms);
TpVoid EXTI_Config(TpVoid);
TpBool TIM_Config(TpVoid);
TpBool GPIO_Config(TpVoid);
  
TpBool SystickInit(TpVoid);
  
TpBool StartupPrint(TpVoid);


  
TpVoid NVIC_Config(TpVoid);
		
#ifdef UBLOX_ON
/* config Ublox  */
TpVoid UbloxConfig(TpVoid);
TpVoid UsartUblox(TpVoid);
#endif
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
