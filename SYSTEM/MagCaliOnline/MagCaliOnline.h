/*=========================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                    */
/* File name:   Mahony.h                                                    */
/* Date:        2017.6.27                                                  */
/* Description:                                                            */
/*=========================================================================*/

#ifndef __UMI_MAGCALI_ONLINE_H__
#define __UMI_MAGCALI_ONLINE_H__

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "Mahony.h"

#define  ALIGN_ACCEL_NUM        ((unsigned int)100)
#define  INCLINATION_MAG        (59.0407982f)
#define  MIN_NOT_ZERO           (1e-7f)

#define  RATIO_SAMPLE_DONE      ((unsigned int)80)
#define  POINT_EVERY_ZOEN       ((unsigned int)3)
#define  MAG_DATA_LEN           ((unsigned int)RATIO_SAMPLE_DONE*POINT_EVERY_ZOEN)

/******************* macro about mag ******************************/
#define MAG_DATA_AXIS            ((unsigned int)3)

/******************  Ellipsoid fitting  ***********/
#define MAG_EIGEN_OUT_DIM        ((unsigned int)6)
#define MAG_EIGEN_OUT_DIM_ROW    ((unsigned char)4)	
#define MAG_ELLIP_ROW            ((unsigned char)10)	

/*============================================================================*/
/*                             struct define                             */
/*============================================================================*/

/*============================================================================*/
/*                               declaration                                  */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**** init eular angle *****/
void InitEular(unsigned int index,const float acc[3],float eular0[3]);
unsigned char CheckEularInitDone(void);
	
void MagCaliOnlineInit(unsigned int index,const float gyo[3],const float acc[3],AhrsOut* pstAhrsInit);
unsigned char CheckCaliInitDone(void);

void GetEuler(AhrsOut* pstAhrsIn,float att[3]);
void GetQuat(AhrsOut* pstAhrsIn,float quat[4]);
	
void FindAppropriateMag(AhrsOut* pstAhrsIn,float mag[3]);
unsigned char CheckMagSampleDone(void);
	
void InitMagInclinationNorm(void);	
void GetMagCaliResult(float bias[3],float k_matrix[3]);	
void CalcGyoBias(AhrsOut* pstAhrsIn,unsigned int index,const float gyo[3]);
unsigned char CheckGyoBiasDone(void);
	
void  MagCaliOnline(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float dt);

void StartMagCali(void);

/*******************************  ellip fitting  *******************************************/
unsigned char MagEllipFitting(void);
void D_EllipCalc(float D_ellip[MAG_ELLIP_ROW*MAG_DATA_LEN]);
void resolve_eigen(const float k,const float D_ellip[MAG_ELLIP_ROW*MAG_DATA_LEN],float v_out[MAG_ELLIP_ROW],float L_out,float* J_out,float* IK_out);
unsigned char MagMemoryInit(void);
void GetEllipFittingPara(float bias[3],float k_matrix[9]);
unsigned char CheckEllipFittingOk(void);

	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 	/* __USART_H */
