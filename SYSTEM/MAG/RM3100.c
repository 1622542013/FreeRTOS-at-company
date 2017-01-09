/****************************************************************
 * Copyright (C) 2016, Yagro, all right reserved.
 * File name:    RM3100.c
 * Date:         2016.07.21
 * Description:  RM3100 Driver, SPI Communication Interface
*****************************************************************/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "RM3100.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

RM3100 rm3100;

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/****************************************************
 * Function:    RM3100_ReadData
 * Description: Read data from RM3100 register.
 * Input:       ADDR: RM3100 Register Address
 * Output:
 * Return:      Data register
*****************************************************/
TpUchar RM3100_ReadData(TpUchar addr)
{
	uint16_t data, i;
	
	addr = addr|0x80;
  
  for(i=0; i<0x05; i++);
	
	SPI1_CS1_LOW();
	data = SPI1_SendHalfWord(((uint16_t)addr<<8)|0xFF);
	SPI1_CS1_HIGH();
  
  for(i=0; i<0x05; i++);
	
	return(data);
}

/****************************************************
 * Function:    RM3100_WriteData
 * Description: Write data from RM3100 register.
 * Input:       ADDR: RM3100 Register Address
 *              Data: Data
 * Output:
 * Return:
*****************************************************/
TpBool RM3100_WriteData(TpUchar addr, TpUchar data)
{
  TpBool resutlt = INLIB_ERROR;
  TpUchar i;
  
  for(i=0; i<0x05; i++);
  
	SPI1_CS1_LOW();
	SPI1_SendHalfWord(((uint16_t)addr<<8)|data);
	SPI1_CS1_HIGH();
  
  for(i=0; i<0x05; i++);
  
  resutlt = INLIB_OK;
  return resutlt;
}

/****************************************************
 * Function:    RM3100_DRDY_Init
 * Description: Initialization RM3100 DRDY pin.
 * Input:
 * Output:
 * Return:
*****************************************************/
TpBool RM3100_DRDY_Init(TpVoid)
{
  TpBool resutlt = INLIB_ERROR;
  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
  
  resutlt = INLIB_OK;
  return resutlt;
  
}

/****************************************************
 * Function:    RM3100_Init
 * Description: Initialization RM3100.
 * Input:       Counts: Cycle Counts
 *              Rate: Sample Rate
 * Output:
 * Return:
*****************************************************/
TpBool  RM3100_Init(TpUint16 counts, TpUchar rate)
{
  TpBool resutlt = INLIB_ERROR;
  
	 uint8_t data;
  
    RM3100_DRDY_Init();
  
  /* Off Continuous Measurement Mode */
    RM3100_WriteData(RM3100_CMM, 0x78);
    while( (data&0xF0) != 0xF0 )
    {
      RM3100_WriteData(RM3100_BIST, 0x87);  /* On Self-Test */
      RM3100_WriteData(RM3100_POLL, 0x70);
      while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
      data = RM3100_ReadData(RM3100_BIST);
    }
    RM3100_WriteData(RM3100_BIST, 0x00);  /* Off Self-Test */
    
    /* On Continuous Measurement Mode */
    RM3100_WriteData(RM3100_CMM, 0x79);
    
    RM3100_WriteData(RM3100_CCX, (uint8_t)(counts>>8));
    RM3100_WriteData(RM3100_CCX+1, (uint8_t)(counts&0x00FF));
    
    RM3100_WriteData(RM3100_CCY, (uint8_t)(counts>>8));
    RM3100_WriteData(RM3100_CCY+1, (uint8_t)(counts&0x00FF));
    
    RM3100_WriteData(RM3100_CCZ, (uint8_t)(counts>>8));
    RM3100_WriteData(RM3100_CCZ+1, (uint8_t)(counts&0x00FF));
    
    RM3100_WriteData(RM3100_TMRC, rate);;
  
  resutlt = INLIB_OK;
  return resutlt;
  
}

/****************************************************
 * Function:    RM3100_Read
 * Description: Read RM3100 MAG Data.
 * Input:       &rm3100
 * Output:
 * Return:
*****************************************************/
TpBool RM3100_Read(RM3100* rm)
{
  TpBool resutlt = INLIB_ERROR;
	TpUint32 Data;
	
	Data = RM3100_ReadData(RM3100_MX)<<16;
	Data |= RM3100_ReadData(RM3100_MX+1)<<8;
	Data |= RM3100_ReadData(RM3100_MX+2);
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	rm->mag_reg[0] = Data;
	
	Data = RM3100_ReadData(RM3100_MY)<<16;
	Data |= RM3100_ReadData(RM3100_MY+1)<<8;
	Data |= RM3100_ReadData(RM3100_MY+2);
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	rm->mag_reg[1] = Data;
	
	Data = RM3100_ReadData(RM3100_MZ)<<16;
	Data |= RM3100_ReadData(RM3100_MZ+1)<<8;
	Data |= RM3100_ReadData(RM3100_MZ+2);
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	rm->mag_reg[2] = Data;
  
  resutlt = INLIB_OK;
  return resutlt;
  
}

/****************************************************
 * Function:    RM3100_DataConversion
 * Description: Data Conversion.
 * Input:       &rm3100
 *              &fData_rm3100
 * Output:
 * Return:
*****************************************************/
TpBool RM3100_DataConversion(RM3100* rm)
{
  TpBool resutlt = INLIB_ERROR;
  
	rm->mag[0] = rm->mag_reg[0] * MAG_LSB_TO_GS;
	rm->mag[1] = rm->mag_reg[1] * MAG_LSB_TO_GS;
	rm->mag[2] = rm->mag_reg[2] * MAG_LSB_TO_GS;
  
  resutlt = INLIB_OK;
  return resutlt;
  
}

TpBool RM3100Config(TpVoid)
{
  TpBool resutlt = INLIB_ERROR;
  
  SPI1_Init();	
	RM3100_Init(Counts_800, Rate_600Hz);
  SPI1_DMA_TX_Init();
	SPI1_DMA_RX_Init();
  
  resutlt = INLIB_OK;
  return resutlt;
}