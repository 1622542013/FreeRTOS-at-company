/****************************************************************
 * Copyright (C) 2016, Yagro, all right reserved.
 * File name:    RM3100.h
 * Date:         2016.08.04
 * Description:  RM3100 Driver, SPI Communication Interface
*****************************************************************/

#ifndef __UMI_RM3100_H
#define __UMI_RM3100_H

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "SPI1.h"
#include "globals.h"
/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define MAG_LSB_TO_GS_Counts_50 (1.0f/1985.714285714284f) /* Counts_50 */
#define MAG_LSB_TO_GS_Counts_100 (1.0f/3821.428571428569f) /* Counts_100 */
#define MAG_LSB_TO_GS_Counts_200 (1.0f/7492.857142857140f) /* Counts_200 */
#define MAG_LSB_TO_GS_Counts_400 (1.0f/14835.71428571428f) /* Counts_400 */
#define MAG_LSB_TO_GS_Counts_800 (1.0f/29521.42857142856f) /* Counts_800 */
#define MAG_LSB_TO_GS_Counts_1600 (1.0f/58892.85714285712f) /* Counts_1600 */
#define MAG_LSB_TO_GS_Counts_3200 (1.0f/117635.7142857143f) /* Counts_3200 */
#define MAG_LSB_TO_GS_Counts_6400 (1.0f/235121.4285714285f) /* Counts_6400 */
#define MAG_LSB_TO_GS_Counts_12800 (1.0f/470092.8571428570f) /* Counts_12800 */
#define MAG_LSB_TO_GS_Counts_25600 (1.0f/940035.7142857140f) /* Counts_25600 */


/********** RM3100 Register ***********/

#define RM3100_POLL   ((TpUchar)0x00) /* Single measurement */
#define RM3100_CMM    ((TpUchar)0x01) /* Continuous measurement */

#define RM3100_CCX    ((TpUchar)0x04) /* Timer register£¨uint16_t£© */
#define RM3100_CCY    ((TpUchar)0x06)
#define RM3100_CCZ    ((TpUchar)0x08)

#define RM3100_TMRC   ((TpUchar)0x0B) /* Set the data output rate in continuous mode */

#define RM3100_ALLX   ((TpUchar)0x0C) /* Alarm limit X-axis£¨uint24_t£© */
#define RM3100_AULX   ((TpUchar)0x0F) /* Alarm limit X-axis */

#define RM3100_ALLY   ((TpUchar)0x12) /* Alarm limit Y-axis */
#define RM3100_AULY   ((TpUchar)0x15) /* Alarm limit Y-axis */

#define RM3100_ALLZ   ((TpUchar)0x18) /* Alarm limit Z-axis */
#define RM3100_AULZ   ((TpUchar)0x1B) /* Alarm limit Z-axis */

#define RM3100_ADLX   ((TpUchar)0x1E) /* Alarm hysteresis register£¨uint16_t£© */
#define RM3100_ADLY   ((TpUchar)0x20)
#define RM3100_ADLZ   ((TpUchar)0x22)

#define RM3100_MX     ((TpUchar)0x24) /* Measurement results output register£¨uint24_t£© */
#define RM3100_MY     ((TpUchar)0x27)
#define RM3100_MZ     ((TpUchar)0x2A)

#define RM3100_BIST   ((TpUchar)0x33) /* Self-Test Register */

#define RM3100_STATUS ((TpUchar)0x34) /* DRDY Status Register */

#define RM3100_HSHAKE ((TpUchar)0x35)

#define RM3100_REVID  ((TpUchar)0x36)

/******* Cycle Counts *************/

#define Counts_50     ((uint16_t)0x0032)  /* Probably 530Hz */
#define Counts_100    ((uint16_t)0x0064)  /* Probably 280Hz */
#define Counts_200    ((uint16_t)0x00C8)  /* Probably 140Hz */
#define Counts_400    ((uint16_t)0x0190)  /* Probably 70Hz */
#define Counts_800    ((uint16_t)0x0320)  /* Probably 35Hz */
#define Counts_1600   ((uint16_t)0x0640)  /* Probably 16Hz */
#define Counts_3200   ((uint16_t)0x0C80)  /* Probably 8Hz */
#define Counts_6400   ((uint16_t)0x1900)  /* Probably 4Hz */
#define Counts_12800  ((uint16_t)0x3200)  /* Probably 2Hz */
#define Counts_25600  ((uint16_t)0x6400)  /* Probably 1Hz */

/******* Sample Rate **************/

#define Rate_600Hz    ((TpUchar)0x92)
#define Rate_300Hz    ((TpUchar)0x93)
#define Rate_150Hz    ((TpUchar)0x94)
#define Rate_75Hz     ((TpUchar)0x95)
#define Rate_37Hz     ((TpUchar)0x96)
#define Rate_18Hz     ((TpUchar)0x97)
#define Rate_9Hz      ((TpUchar)0x98)
#define Rate_4_5Hz    ((TpUchar)0x99)
#define Rate_2_3Hz    ((TpUchar)0x9A)
#define Rate_1_2Hz    ((TpUchar)0x9B)
#define Rate_0_6Hz    ((TpUchar)0x9C)
#define Rate_0_3Hz    ((TpUchar)0x9D)
#define Rate_0_15Hz   ((TpUchar)0x9E)
#define Rate_0_075Hz  ((TpUchar)0x9F)

/************************************/

#define RM3100_DRDY   GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)


/*============================================================================*/
/*                             struct define                                 */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

typedef struct tagRM3100
{
	/* reg data  */
	TpInt32   magx_reg;
	TpInt32   magy_reg;
	TpInt32   magz_reg;
	/* mag data */
  TpFloat magx;
	TpFloat magy;
	TpFloat magz;
}RM3100;



typedef struct _tagMagSend
{
	TpUint16 head;
	float magx;
	float magy;
	float magz;
	TpUchar check;
	 
}MagSend;


#pragma pack(pop)

/*============================================================================*/
/*                              declarations                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	
/*============================================================================*/
/*                             User defined                                 */
/*============================================================================*/
	
	
	
TpUchar  Rm3100ReadData(TpUchar addr);
TpVoid   Rm3100WriteData(TpUchar addr, TpUchar data);
TpVoid   Rm3100DRDYInit(TpVoid);
TpVoid   Rm3100Init(TpUint16 counts, TpUchar rate);
TpBool   Rm3100Read(RM3100* rm);
TpBool Rm3100DataConversion(RM3100* rm);
TpBool RM3100Config(TpUint16 rate);

TpVoid   Rm3100SetMagLsbToGs(TpUint32 mag_rate);	
TpUint16 Rm3100ReadFreq(TpUint32 Mag_rate);
	
TpBool DecodeMagData(TpUint16* mag_data_buff,RM3100* pRm3100);
RM3100* ReturnRM3100Address(void);
TpBool MagCaliCompensate(const float bias_mag[3],const float mul_matrix[],RM3100* rm3100);
TpBool MagMulMatrixCalc(const float matrix_mag[],const float rotation_mag[],float mul_matrix[]);
TpBool ChangeMagSampleRate(TpUint16 rate);
//TpBool CombineMagBin(RM3100* pRm3100,UmiMagBin* pUmiMagBin);	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

