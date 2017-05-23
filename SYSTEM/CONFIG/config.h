/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
<<<<<<< HEAD
/* File name:   config.h                                                */
/* Date:        2017.4.25                                                   */
=======
/* File name:   hw_config.h                                                */
/* Date:        2016.8.4                                                   */
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
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

<<<<<<< HEAD
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
=======
#define SYSTICK_MS       (8400)

#define EXTI_LINE1_ON

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

TpBool HardWareInit(TpVoid);
<<<<<<< HEAD
=======
TpBool Delay_ms(u16 nms);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
TpVoid EXTI_Config(TpVoid);
TpBool TIM_Config(TpVoid);
TpBool GPIO_Config(TpVoid);
  
<<<<<<< HEAD
TpBool StartupPrint(TpVoid);

TpVoid UbloxConfig(TpVoid);
  
TpVoid NVIC_Config(TpVoid);
=======
TpBool SystickInit(TpVoid);
  
TpBool StartupPrint(TpVoid);


  
TpVoid NVIC_Config(TpVoid);
		
#ifdef UBLOX_ON
/* config Ublox  */
TpVoid UbloxConfig(TpVoid);
TpVoid UsartUblox(TpVoid);
#endif
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
<<<<<<< HEAD

=======
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
