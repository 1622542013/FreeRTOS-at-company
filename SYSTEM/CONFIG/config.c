/**
 * @file        config.c
 * @brief       初始化文件
 */

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "config.h"
#include "flash.h"
#include "USART.h"
#include "delay.h"


/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

void USART_Init_Usr()
{
  Usart* usr_usart;
  usr_usart = GetUsartAddress(USART_2);
  
  UsartConfig(usr_usart,USART_2,230400);
}

TpVoid NVIC_Config(TpVoid)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 

}


/**
 * @brief 定时器初始化
 * @note  TIM2 ： 20KHZ    以供FreeRTOS系统使用
 *
 * @retval 成功返回值： 无
 * @retval 失败返回值： 无
 * @pre    调用举例 ： 
 */ 

void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  /* Enable TIM2 clock */

  TIM_TimeBaseInitStructure.TIM_Prescaler = 83;                   /* Specifies the prescaler value used to divide the TIM clock. */
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; /* Specifies the counter mode */
  TIM_TimeBaseInitStructure.TIM_Period = 49;                     /* Reload value	approximate 20KHz */
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

void HardWareInit(TpVoid)
{
  TIM_Configuration();
  USART_Init_Usr();
  NVIC_Config();
}


