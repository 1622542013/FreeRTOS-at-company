/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   Mag.h                                                      */
/* Date:        2016.5.18                                                     */
/* Description: gnss.c                                                       */
/*============================================================================*/

#ifndef  __UMI_MAGCALI_H
#define  __UMI_MAGCALI_H

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "definition.h"
#include "mclib_api.h"
#include "globals.h"
#include "Rm3100.h"
#include "command.h"
/*============================================================================*/
/*                                   Macros                                   */
/*============================================================================*/

#define MAG_AVERAGE_CNT       ((TpUint16)7)
#define GYO_THETA_SUM_CNT     (30)
#define GYO_THETA_STEP        ((TpFloat)0.01)
#define GYO_THETA_THRESHOLD   ((TpFloat)1.0)



/*============================================================================*/
/*                             struct define                                  */
/*============================================================================*/

typedef struct _GyoMagState
{
	TpUchar  theta_check_start;
	TpUchar  theta_ok;     /* if gyro theta is ok */
	TpUint16 theta_sum_cnt;    /* theta cnt */
	TpFloat  theta_sum;    /* theta sum */

}GyoMagState;


typedef struct _MagCaliFlag
{
	TpUchar  flag_magcali;
	TpUchar  flag_calidone;
	TpUchar  flag_setmag;
	
}MagCaliFlag;

/*============================================================================*/
/*                               declaration                             */
/*============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
	
extern MCLibInstance mclib_instance;
extern Measure_in  mea_in;
extern GyoMagState   gmstate;
extern MagCaliFlag   stMagCaliFlag;
	
	
void    MagCaliInit(void);
unsigned char RotCheck(const float gyox,const float gyoy,const float gyoz,float* theta);
TpUchar GyoMagStateInit(GyoMagState* gms);
TpUchar IsSetMagAccData(const TpFloat gyox,const TpFloat gyoy,const TpFloat gyoz,GyoMagState* gms);
TpUchar IsVec3Zero(const TpFloat fVec[]);
TpBool CheckMagCaliOk(MagCaliFlag* pMagCaliFlag,UmiIgmBin* pUmiOutput,RM3100* pRm3100,Measure_in* pMeaIn);
	unsigned char MagCaliOnline(unsigned char * pState_mag,EllipFittingResult * pEll_result);
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


