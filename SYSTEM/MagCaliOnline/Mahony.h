/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   Mahony.h                                                    */
/* Date:        2017.6.27                                                  */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_MAHONY_H__
#define __UMI_MAHONY_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/


/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/


#define  LIB_RETURN_OK          ((unsigned char)1)
#define  LIB_RETURN_ERROR       ((unsigned char)0)
	
#define  MIN_GYO_NORM           (1.0f)
	

#define _D2R_F 	    0.017453292519943f	//Degree to Rad
#define _R2D_F		  57.29577951308232f
#define _G0_F       9.801275f

#define R_DEBUG
/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

#pragma pack(push)
#pragma pack(1)

// Mahony calc ahrs data
typedef struct _tagAhrsOut
{
	float quat[4];
	float cbn[9];
	float exyzInt[3];
	float Kp;
	float Ki;
	float tk;
	//
	float gyo_bias[3];
}AhrsOut;

#pragma pack(pop)


/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
	
extern AhrsOut stAhrsOut;	


void 	MahonyInit(const float tau,const float att0[3],AhrsOut* pstAhrsOutInit);
void  MahonyUpdate(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float ts);
void  MahonyUpdateGyoInte(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float ts);
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 	/* __USART_H */
