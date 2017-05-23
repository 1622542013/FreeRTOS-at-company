/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.h 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    04-September-2015
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
<<<<<<< HEAD
#include "definition.h"
#include "usart.h"
#include "SPI1.h"
=======
#include "gnss.h"
#include "RM3100.h"
#include "usart.h"
#include "protocol.h"

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
<<<<<<< HEAD

typedef struct _tagInterruptRecFlag
{
	/* flag */
	TpUchar rec_mag;
	TpUchar rec_gnss;
	TpUchar rec_user;
	TpUchar rec_arm2;
	/* num of data */
	TpUint16 num_mag;
	TpUint16 num_gnss;
	TpUint16 num_user;
	TpUint16 num_arm2;
	
	TpUint16 buff_mag[SPI1_RX_SIZE];
	TpUchar buff_gnss[BUFSIZE_USART1_REC];
	TpUchar buff_user[BUFSIZE_USART2_REC];
	TpUchar buff_arm2[BUFSIZE_USART6_REC];
	
}InterruptRecFlag;


=======
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	 
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

<<<<<<< HEAD
InterruptRecFlag* GetInterruptRecFlag(TpVoid);

extern TpUchar isSetMag;


/*   */


=======
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
