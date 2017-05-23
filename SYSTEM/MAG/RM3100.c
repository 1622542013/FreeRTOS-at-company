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

<<<<<<< HEAD

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/
static RM3100 rm3100;
static float MAG_LSB_TO_GS ;

=======
/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

RM3100 rm3100;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/****************************************************
<<<<<<< HEAD
 * Function:    Rm3100ReadData
=======
 * Function:    RM3100_ReadData
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Read data from RM3100 register.
 * Input:       ADDR: RM3100 Register Address
 * Output:
 * Return:      Data register
*****************************************************/
<<<<<<< HEAD
TpUchar Rm3100ReadData(TpUchar addr)
=======
TpUchar RM3100_ReadData(TpUchar addr)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
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
<<<<<<< HEAD
 * Function:    Rm3100WriteData
=======
 * Function:    RM3100_WriteData
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Write data from RM3100 register.
 * Input:       ADDR: RM3100 Register Address
 *              Data: Data
 * Output:
 * Return:
*****************************************************/
<<<<<<< HEAD
TpVoid Rm3100WriteData(TpUchar addr, TpUchar data)
{
=======
TpBool RM3100_WriteData(TpUchar addr, TpUchar data)
{
  TpBool resutlt = INLIB_ERROR;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  TpUchar i;
  
  for(i=0; i<0x05; i++);
  
	SPI1_CS1_LOW();
	SPI1_SendHalfWord(((uint16_t)addr<<8)|data);
	SPI1_CS1_HIGH();
  
  for(i=0; i<0x05; i++);
<<<<<<< HEAD
}

/****************************************************
 * Function:    Rm3100DRDYInit
=======
  
  resutlt = INLIB_OK;
  return resutlt;
}

/****************************************************
 * Function:    RM3100_DRDY_Init
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Initialization RM3100 DRDY pin.
 * Input:
 * Output:
 * Return:
*****************************************************/
<<<<<<< HEAD
TpVoid Rm3100DRDYInit(TpVoid)
{  
=======
TpBool RM3100_DRDY_Init(TpVoid)
{
  TpBool resutlt = INLIB_ERROR;
  
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
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
  
<<<<<<< HEAD
}

/****************************************************
 * Function:    Rm3100Init
=======
  resutlt = INLIB_OK;
  return resutlt;
  
}

/****************************************************
 * Function:    RM3100_Init
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Initialization RM3100.
 * Input:       Counts: Cycle Counts
 *              Rate: Sample Rate
 * Output:
 * Return:
*****************************************************/
<<<<<<< HEAD
TpVoid  Rm3100Init(TpUint16 counts, TpUchar rate)
{ 
	 uint8_t data;
  
    Rm3100DRDYInit();
  
  /* Off Continuous Measurement Mode */
    Rm3100WriteData(RM3100_CMM, 0x78);
    while( (data&0xF0) != 0xF0 )
    {
      Rm3100WriteData(RM3100_BIST, 0x87);  /* On Self-Test */
      Rm3100WriteData(RM3100_POLL, 0x70);
      while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
      data = Rm3100ReadData(RM3100_BIST);
    }
    Rm3100WriteData(RM3100_BIST, 0x00);  /* Off Self-Test */
    
    /* On Continuous Measurement Mode */
    Rm3100WriteData(RM3100_CMM, 0x79);
    
    Rm3100WriteData(RM3100_CCX, (uint8_t)(counts>>8));
    Rm3100WriteData(RM3100_CCX+1, (uint8_t)(counts&0x00FF));
    
    Rm3100WriteData(RM3100_CCY, (uint8_t)(counts>>8));
    Rm3100WriteData(RM3100_CCY+1, (uint8_t)(counts&0x00FF));
    
    Rm3100WriteData(RM3100_CCZ, (uint8_t)(counts>>8));
    Rm3100WriteData(RM3100_CCZ+1, (uint8_t)(counts&0x00FF));
    
    Rm3100WriteData(RM3100_TMRC, rate);;  
}

/****************************************************
 * Function:    Rm3100Read
=======
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
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Read RM3100 MAG Data.
 * Input:       &rm3100
 * Output:
 * Return:
*****************************************************/
<<<<<<< HEAD
TpBool Rm3100Read(RM3100* rm)
{
//  TpBool resutlt = INLIB_ERROR;
	  TpBool resutlt = 0;
	TpUint32 Data;
	
	Data = Rm3100ReadData(RM3100_MX)<<16;
	Data |= Rm3100ReadData(RM3100_MX+1)<<8;
	Data |= Rm3100ReadData(RM3100_MX+2);
=======
TpBool RM3100_Read(RM3100* rm)
{
  TpBool resutlt = INLIB_ERROR;
	TpUint32 Data;
	
	Data = RM3100_ReadData(RM3100_MX)<<16;
	Data |= RM3100_ReadData(RM3100_MX+1)<<8;
	Data |= RM3100_ReadData(RM3100_MX+2);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
<<<<<<< HEAD
	rm->magx_reg = Data;
	
	Data = Rm3100ReadData(RM3100_MY)<<16;
	Data |= Rm3100ReadData(RM3100_MY+1)<<8;
	Data |= Rm3100ReadData(RM3100_MY+2);
=======
	rm->mag_reg[0] = Data;
	
	Data = RM3100_ReadData(RM3100_MY)<<16;
	Data |= RM3100_ReadData(RM3100_MY+1)<<8;
	Data |= RM3100_ReadData(RM3100_MY+2);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
<<<<<<< HEAD
	rm->magy_reg = Data;
	
	Data = Rm3100ReadData(RM3100_MZ)<<16;
	Data |= Rm3100ReadData(RM3100_MZ+1)<<8;
	Data |= Rm3100ReadData(RM3100_MZ+2);
=======
	rm->mag_reg[1] = Data;
	
	Data = RM3100_ReadData(RM3100_MZ)<<16;
	Data |= RM3100_ReadData(RM3100_MZ+1)<<8;
	Data |= RM3100_ReadData(RM3100_MZ+2);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
<<<<<<< HEAD
	rm->magz_reg = Data;
=======
	rm->mag_reg[2] = Data;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  
  resutlt = INLIB_OK;
  return resutlt;
  
}

/****************************************************
<<<<<<< HEAD
 * Function:    Rm3100DataConversion
=======
 * Function:    RM3100_DataConversion
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
 * Description: Data Conversion.
 * Input:       &rm3100
 *              &fData_rm3100
 * Output:
 * Return:
*****************************************************/
<<<<<<< HEAD
TpBool Rm3100DataConversion(RM3100* rm)
{ 
	rm->magx = rm->magx_reg * MAG_LSB_TO_GS;
	rm->magy = rm->magy_reg * MAG_LSB_TO_GS;
	rm->magz = rm->magz_reg * MAG_LSB_TO_GS;
  
  return INLIB_OK; 
}

TpBool RM3100Config(TpUint16 rate)
{
  SPI1_Init();	
	Rm3100Init(rate, Rate_600Hz);
  SPI1_DMA_TX_Init();
	SPI1_DMA_RX_Init();
	
	MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_400;
  
  return INLIB_OK;
}

TpUint16 Rm3100ReadFreq(TpUint32 Mag_rate)
{
	switch(Mag_rate)
	{
		case 0						: return 0;
		case Counts_25600	: return 1;
		case Counts_12800	: return 2;
		case Counts_6400	: return 4;
		case Counts_3200	: return 8;
		case Counts_1600	: return 16;
		case Counts_800		: return 35;
		case Counts_400		: return 70;
		case Counts_200		: return 140;
		case Counts_100		: return 280;
		case Counts_50		: return 350;
		
		case 1		: return Counts_25600;
		case 2		: return Counts_12800;
		case 4		: return Counts_6400;
		case 8		: return Counts_3200;
		case 16		: return Counts_1600;
		case 35		: return Counts_800;
		case 70		: return Counts_400;
		case 140	: return Counts_200;
		case 280	: return Counts_100;
		case 350	: return Counts_50;
		
		default : return 0xffff;
	}
}

TpVoid   Rm3100SetMagLsbToGs(TpUint32 mag_rate)
{
	switch(mag_rate)
	{
		case 0	:break;		
		case Counts_25600	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_25600;break;
		case Counts_12800 : MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_12800;break;
		case Counts_6400	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_6400;break;
		case Counts_3200	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_3200;break;
		case Counts_1600	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_1600;break;
		case Counts_800		: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_800;break;
		case Counts_400		: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_400;break;
		case Counts_200 	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_200;break;
		case Counts_100 	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_100;break;
		case Counts_50  	: MAG_LSB_TO_GS = MAG_LSB_TO_GS_Counts_50;break;			
		default:break;
	}
}

/*** decode mag data ***/
TpBool DecodeMagData(TpUint16* mag_data_buff,RM3100* pRm3100)
{
	TpBool result = RESULT_ERROR;
	
	TpUint32 Data;
	
	/* magx */
	Data = (mag_data_buff[0]&0x00FF)<<16;
	Data |= mag_data_buff[1];
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	pRm3100->magx_reg = Data;
	
	/* magy  */
	Data = mag_data_buff[2]<<8;
	Data |= mag_data_buff[3]>>8;
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	pRm3100->magy_reg = Data;
	
	/* magz */
	Data = (mag_data_buff[3]&0x00FF)<<16;
	Data |= mag_data_buff[4];
	if(Data&0x00800000)
	{
		Data = Data|0xFF000000;
	}
	pRm3100->magz_reg = Data;
	
	/* reg data to mag data */
	Rm3100DataConversion(pRm3100);
	
	return result;

}
/* mag parameters compensate*/
TpBool MagCaliCompensate(const float bias_mag[3],const float mul_matrix[9],RM3100* rm3100)
{
	TpBool result = RESULT_ERROR;
	TpFloat  mag_comp[3];

	/* frist step: compensate bias */
	mag_comp[0] = rm3100->magx - bias_mag[0];
	mag_comp[1] = rm3100->magy - bias_mag[1];
	mag_comp[2] = rm3100->magz - bias_mag[2];
	
	/* second step: multiply */
  rm3100->magx = mul_matrix[0] * mag_comp[0] + mul_matrix[1] * mag_comp[1] + mul_matrix[2] * mag_comp[2];
	rm3100->magy = mul_matrix[3] * mag_comp[0] + mul_matrix[4] * mag_comp[1] + mul_matrix[5] * mag_comp[2];
	rm3100->magz = mul_matrix[6] * mag_comp[0] + mul_matrix[7] * mag_comp[1] + mul_matrix[8] * mag_comp[2];
	
	return result;

}

/******* return rm3100 address **********/
RM3100* ReturnRM3100Address()
{
   return &rm3100;
}

TpBool MagMulMatrixCalc(const float matrix_mag[9],const float rotation_mag[9],float mul_matrix[9])
{
	TpBool result = RESULT_ERROR;
  TpUchar i = 0,j = 0,k = 0;
	
	/* multi  */
  for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			mul_matrix[i*3 + j] = 0.0f;
			for (k = 0; k < 3; k++)
			{
				mul_matrix[i*3 + j] += rotation_mag[i*3 + k] * matrix_mag[k*3 + j];
			}
		}
	}
	
	
	
  return result;
}


TpBool ChangeMagSampleRate(TpUint16 sample_rate)
{
	TpBool result = RESULT_ERROR;
	
  	__disable_irq();
		
		SPI1_DMA_Dnit();		
		Rm3100Init(sample_rate, Rate_600Hz);		
		SPI1_DMA_Init();
		
		__enable_irq();
		
		Rm3100SetMagLsbToGs(sample_rate);
		
		result = RESULT_OK;
	
	return result;
}


//TpBool CombineMagBin(RM3100* pRm3100,UmiMagBin* pUmiMagBin)
//{
//	TpBool result = RESULT_ERROR;
//	
////	memset(pUmiMagBin,0,sizeof(UmiMagBin));
//	
//	pUmiMagBin->head = 0x23AC;
//	
//	pUmiMagBin->magx = pRm3100->magx;
//	pUmiMagBin->magy = pRm3100->magy;
//	pUmiMagBin->magz = pRm3100->magz;
//	
//	pUmiMagBin->check = CheckSumByte((uint8_t*)pUmiMagBin, sizeof(UmiMagBin));
//	
//  result = RESULT_OK;
//	return result;
//}
=======
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
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
