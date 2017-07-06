/*============================================================================*/
/* Copyright (C), 2017, Yagro Co., Ltd.                                       */
/* File name:   Mahony.c                                                       */
/* Date:        2017.6.27                                                     */
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "MagCaliOnline.h"
#include "matrix.h"
#include "MagPoint.h"
#include "sdet.h"
#include "eigcal.h"
#include "cholcal.h"


#ifdef R_DEBUG
#include "usart.h"
#include "delay.h"
#endif



/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/
/********* initial Eualr angle use *************/

static unsigned int align_accel_num = 0;
static unsigned char _flag_accel_sample_done = 0;
static unsigned char _flag_eular_init_done = 0;
static float acc_sum[3]  = {0.0f};
static float acc_mean[3] = {0.0f};

float gyo_bias[3] = {0.0};

/********** Ellipsoid fitting  **********/

/* malloc memory   */
//float* magx;
//float* magy;
//float* magz;

static float magx[MAG_DATA_LEN],magy[MAG_DATA_LEN],magz[MAG_DATA_LEN];
static unsigned char ellip_fitting_ok = 0;

/******** Find  Appropriate  Mag ***********/

static unsigned short int mag_index[MAG_DATA_LEN] = {0};
static float    mag_inclination[3] = {0.0f};             // mag  inclination
static unsigned short int index_max = 0;
static unsigned short int mag_use_cnt = 0;



/*************************** calc gyo bias  ******************************************/
unsigned int align_gyo_num = 0;
static float gyo_sum[3]  = {0.0f};
static float gyo_mean[3] = {0.0f};

static unsigned char _flag_mag_sample_done = 0;
static unsigned char _flag_cali_init_done = 0;
static unsigned char _flag_gyo_bias_done = 0;

/******************************* debug  *********************************************/

#ifdef R_DEBUG
float time_use = 0.0f;
unsigned char outputMag[100];
#endif

/********************************  result **************************************/

static float bias_mag[3] = { 0.0 };
static float matrix_mag[9] = { 0.0 };

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/************************************************************************
name:	  	InitEular
function: use acc data in 1sec to calculate initial eular
************************************************************************/

void InitEular(unsigned int index,const float acc[3],float eular0[3])
{
	// sample number less than ALIGN_ACCEL_NUM,accumulation
	if(align_accel_num < ALIGN_ACCEL_NUM)
	{
		align_accel_num++;		
		// calc acc sum
		acc_sum[0] = acc_sum[0] + acc[0];
		acc_sum[1] = acc_sum[1] + acc[1];
		acc_sum[2] = acc_sum[2] + acc[2];
	}
	else if(align_accel_num == ALIGN_ACCEL_NUM)
	{
		// set flag
		_flag_accel_sample_done = 1;
	}
	// initial eular angle
	if(_flag_accel_sample_done==1)
	{
		// calculate average
	  acc_mean[0] = acc_sum[0]*_G0_F/ALIGN_ACCEL_NUM;
		acc_mean[1] = acc_sum[1]*_G0_F/ALIGN_ACCEL_NUM;
		acc_mean[2] = acc_sum[2]*_G0_F/ALIGN_ACCEL_NUM;
		// calculate eular angle
		eular0[0] = asinf(acc_mean[1]/_G0_F);
		eular0[1] = atan2f(-acc_mean[0],acc_mean[2]);
		eular0[2] = 0.0f;	
		// 
		acc_sum[0] = 0.0f;
		acc_sum[1] = 0.0f;
		acc_sum[2] = 0.0f;		
		// set flag
		_flag_eular_init_done = 1;

	}	
}
/************************************************************************
name:	  	CheckEularInitDone
function: 
************************************************************************/
unsigned char CheckEularInitDone(void)
{
  return _flag_eular_init_done;
}

/************************************************************************
name:	  	MagCaliOnlineInit
function: 
************************************************************************/
void MagCaliOnlineInit(unsigned int index,const float gyo[3],const float acc[3],AhrsOut* pstAhrsInit)
{
	static float eular0[3];
	// init eular angle
	if(!CheckEularInitDone())
	{
			InitEular(index,acc,eular0);
		  if(!CheckGyoBiasDone())
		     CalcGyoBias(pstAhrsInit,index,gyo);
	}
	else
	{
		// allocate space for mag data
		MagMemoryInit();
		// init mahony 
		MahonyInit(4,eular0,&stAhrsOut); 
		_flag_cali_init_done = 1;
		// calc mag inclination in ENU frame  
		InitMagInclinationNorm();        
	}
}

/************************************************************************
name:	  	CheckCaliInitDone
function: 
************************************************************************/
unsigned char CheckCaliInitDone(void)
{
  return _flag_cali_init_done;
}

/************************************************************************
name:	  	GetEuler
function: 
************************************************************************/
void GetEuler(AhrsOut* pstAhrsIn,float att[3])
{
	float cbn[9];
	unsigned char i = 0;
	float att_tmp[3];
	
	for(i = 0;i<9;i++)
	    cbn[i] = pstAhrsIn->cbn[i];
	
	att_tmp[0] = att[0];
	att_tmp[1] = att[1];
	att_tmp[2] = att[2];
	
	Dcm2Euler(cbn,att_tmp);
	
	att[0] = att_tmp[0]*_R2D_F;
	att[1] = att_tmp[1]*_R2D_F;
	att[2] = att_tmp[2]*_R2D_F;

}

/************************************************************************
name:	  	GetQuat
function: 
************************************************************************/
void GetQuat(AhrsOut* pstAhrsIn,float quat[4])
{
  quat[0] = pstAhrsIn->quat[0];
	quat[1] = pstAhrsIn->quat[1];
	quat[2] = pstAhrsIn->quat[2];
	quat[3] = pstAhrsIn->quat[3];	
}

/************************************************************************
name:	  	FindAppropriateMag
function: 
************************************************************************/
void FindAppropriateMag(AhrsOut* pstAhrsIn,float mag[3])
{
	unsigned short int i = 0;
	unsigned char j = 0;
	float mag_norm = 0.0f;
	float mag_table_norm = 0.0f;
	float mag_norm_n2b = 0.0f;
	
	float angle_vec = 0.0f;
	float angle_vec_max = 0.0f;

	//
	float mag_table[3] = {0.0f};
	float mag_n2b[3] = {0.0f};
	//
	float cbn[9] = {0.0f};
	float cnb[9] = {0.0f};
	// 
  unsigned char len = 0;
	
	// calc norm
	mag_norm = sqrtf(mag[0]*mag[0]+mag[1]*mag[1]+mag[2]*mag[2]);
	if(mag_norm > MIN_NOT_ZERO)
	{
		// cbn
		for(j = 0;j<9;j++)
		    cbn[j] = pstAhrsIn->cbn[j];
		RotMatxxf(3,3,cbn,cnb);
		MulCbnVec3(cnb,mag_inclination,mag_n2b);
		
		for(i = 0;i<NUM_MAG_POINT;i++)
		{
			mag_table[0] = MAG_COF[i][0];
			mag_table[1] = MAG_COF[i][1];
			mag_table[2] = MAG_COF[i][2];
			
			//
			mag_table_norm = sqrtf(mag_table[0]*mag_table[0] + mag_table[1]*mag_table[1] + mag_table[2]*mag_table[2]);
			mag_norm_n2b   = sqrtf(mag_n2b[0]*mag_n2b[0] + mag_n2b[1]*mag_n2b[1] + mag_n2b[2]*mag_n2b[2]);
		
			angle_vec = mag_table[0]*mag_n2b[0] + mag_table[1]*mag_n2b[1] + mag_table[2]*mag_n2b[2];
			angle_vec = angle_vec/mag_norm_n2b;
			angle_vec = angle_vec/mag_table_norm;
      
			if(angle_vec>angle_vec_max)
			{
			  angle_vec_max = angle_vec;
				index_max = i;
			}		
		}
		
		if(mag_index[index_max]<POINT_EVERY_ZOEN)
		{
		   mag_index[index_max]++;
			 magx[mag_use_cnt] = mag[0];
			 magy[mag_use_cnt] = mag[1];
			 magz[mag_use_cnt] = mag[2];
			 mag_use_cnt++;	

			#ifdef R_DEBUG
			float ratio_mag = 0.0;
			unsigned char ratio_mag_out = 0;
			ratio_mag = mag_use_cnt - 1;
			ratio_mag = ratio_mag/MAG_DATA_LEN;
			ratio_mag_out = ratio_mag*100;
			len = snprintf((char*)outputMag,200,"%f %f %f %d\r\n",magx[mag_use_cnt-1],magy[mag_use_cnt-1],magz[mag_use_cnt-1],ratio_mag_out);
      UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)outputMag,(TpUint16)len);
		  #endif
			/********************* RLS **************************/		
		}
		// Reach the coverage
		if(mag_use_cnt==MAG_DATA_LEN)
		{
			 _flag_mag_sample_done = 1;   // sample enough mag data	
			 ellip_fitting_ok = MagEllipFitting();		
		}
	}
	else
		return;
}

/************************************************************************
name:	  	CheckMagSampleDone
function:  
************************************************************************/

unsigned char CheckMagSampleDone(void)
{
  return _flag_mag_sample_done;
}

/************************************************************************
name:	  	InitMagInclinationNorm
function: calc 
************************************************************************/
void InitMagInclinationNorm(void)
{
   mag_inclination[0] =  0.0f;
	 mag_inclination[1] =  cosf(INCLINATION_MAG*_D2R_F);
	 mag_inclination[2] = -sinf(INCLINATION_MAG*_D2R_F);
}

/************************************************************************
name:	  	GetMagCaliResult
function: return mag calibration result,including mag bias and k matrix
************************************************************************/
//void GetMagCaliResult(float bias[3],float k_matrix[3])
//{	 

//	 mag[0] = magx[mag_use_cnt-1];
//	 mag[1] = magy[mag_use_cnt-1];
//	 mag[2] = magz[mag_use_cnt-1];

//}

void CalcGyoBias(AhrsOut* pstAhrsIn,unsigned int index,const float gyo[3])
{
   	// sample number less than ALIGN_ACCEL_NUM,accumulation
	if(align_gyo_num < ALIGN_ACCEL_NUM)
	{
		align_gyo_num++;		
		// calc acc sum
		gyo_sum[0] = gyo_sum[0] + gyo[0];
		gyo_sum[1] = gyo_sum[1] + gyo[1];
		gyo_sum[2] = gyo_sum[2] + gyo[2];
	}
	else if(align_accel_num == ALIGN_ACCEL_NUM)
	{
		gyo_mean[0] = gyo_sum[0]/ALIGN_ACCEL_NUM;
		gyo_mean[1] = gyo_sum[1]/ALIGN_ACCEL_NUM;
		gyo_mean[2] = gyo_sum[2]/ALIGN_ACCEL_NUM;
				
		pstAhrsIn->gyo_bias[0]  = gyo_mean[0];
		pstAhrsIn->gyo_bias[1]  = gyo_mean[1];
		pstAhrsIn->gyo_bias[2]  = gyo_mean[2];
			
		_flag_gyo_bias_done = 1;
	}
}


unsigned char MagMemoryInit(void)
{
//	magx = (float*)malloc(MAG_DATA_LEN*sizeof(float));
//	magy = (float*)malloc(MAG_DATA_LEN*sizeof(float));
//	magz = (float*)malloc(MAG_DATA_LEN*sizeof(float));

	/* reserved */
	return LIB_RETURN_OK;
}

void  MagCaliOnline(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float dt)
{
     // MahonyUpdate(pstAhrsIn,gyo,acc,mag,0.01);
	    MahonyUpdateGyoInte(pstAhrsIn,gyo,acc,mag,0.01);
}



/********************************************************************* ellip fitting  ***********************************************/

unsigned char MagEllipFitting(void)
{
	double k = 0.0;
	unsigned int i, j = 0;

	float* D_ellip;
	float* V_out;
	float* V_e;
	float L_out = 0.0;
	float J_out = 0.0;
	float IK_out = 0.0;
	
	// A,center0
	float* A;
	float* A_sub1;
	float* A_sub2;
	float* center0;
	float* center;
	float* A_sub3;
	float* A_sub4;
	float* alfa;
	float* A_sub5;
	float* A_sub6;
	float alfa_value = 0.0;
	float* chol_delta;
	float D0m_inv[9];
	
	/*********************** calc  D_ellip  *************************/ 
	
	k = 15000.0;
	
	D_ellip = (float*)malloc(MAG_ELLIP_ROW*MAG_DATA_LEN*sizeof(float));
	V_out = (float*)malloc(MAG_ELLIP_ROW*sizeof(float));

	D_EllipCalc(D_ellip);
	resolve_eigen(k, D_ellip, V_out, L_out, &J_out, &IK_out);

	//V_e
   V_e = (float*)malloc(MAG_ELLIP_ROW*sizeof(float));

	if (J_out > 0 && IK_out > 0)
	{
		for (i = 0; i < 10; i++)
			V_e[i] = V_out[i];
		ellip_fitting_ok = 1;
	}
	else
	{
	    return LIB_RETURN_ERROR;
	}

	
	free(D_ellip);
	
	// A
	A = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM_ROW*sizeof(float));

 // coefficient matrix
  A[0]  = V_e[0];
  A[5] = V_e[1];
  A[10] = V_e[2];
  A[15] = V_e[9];
  A[1] = A[4] = V_e[5];
  A[2] = A[8] = V_e[4];
  A[3] = A[12] = V_e[6];
  A[6] = A[9]  = V_e[3];
  A[7] = A[13] = V_e[7];
  A[11] = A[14] = V_e[8];

  // A_sub1
  A_sub1 = (float*)malloc(3*3*sizeof(float));

  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++)
	  {
		  A_sub1[i * 3 + j] = A[i*4+j];
	  }
  // inv(A_sub1)
  InvMatxf(3,A_sub1);

  // A_sub2;
  A_sub2 = (float*)malloc(3 * sizeof(float));
  A_sub3 = (float*)malloc(3 * sizeof(float));

  for (i = 0; i < 3; i++)
	  {
		  A_sub2[i] = A[i*4 + 3];
	  }
  RotMatxxf(3, 1, A_sub2, A_sub3);
  // center0
  center0 = (float*)malloc(3 * sizeof(float));
  center = (float*)malloc(3 * sizeof(float));
  MulMatxxf(3, 3, 1, A_sub1, A_sub2, center0);

  for (i = 0; i < 3; i++)
  {
	  center[i] = center0[i];
	  center0[i] = -center0[i];
  }
 
  // A(1:3,4)'
  A_sub4 = (float*)malloc(sizeof(float));
  MulMatxxf(1, 3, 1, A_sub3, center, A_sub4);
  
  // 
  alfa = (float*)malloc(sizeof(float));
  SubMatxxf(1, 1, A_sub4, &A[15], alfa);
  InvMatxf(1, alfa);

  //
  A_sub5 = (float*)malloc(3 * 3 * sizeof(float));

  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++)
	  {
		  A_sub5[i * 3 + j] = A[i * 4 + j];
	  }
  // 
  alfa_value = *alfa;
  A_sub6 = (float*)malloc(3 * 3 * sizeof(float));
  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++)
		  A_sub6[i * 3 + j] = alfa_value*A_sub5[i * 3 + j];

  chol_delta = (float*)malloc(sizeof(float));
  cholcal(A_sub6, 3, chol_delta);

  RotMatxxf(3, 3, A_sub6, D0m_inv);

  for (i = 0; i < 3;i++)
	{
    bias_mag[i]    = center0[i];
	}


  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3;j++)
	{
		  matrix_mag[i*3+j] = D0m_inv[i*3+j];
	}

  free(V_out);
  free(V_e);
  free(A);
  free(A_sub1);
  free(A_sub2);
  free(A_sub3);
  free(A_sub4);
  free(A_sub5);
  free(A_sub6);
  free(center0);
  free(center);
  free(alfa);
  free(chol_delta);
	
  return LIB_RETURN_OK;

}


/*********************** calc  D_ellip  *************************/ 
void D_EllipCalc(float D_ellip[MAG_ELLIP_ROW*MAG_DATA_LEN])
{
	unsigned int i = 0;
	// D(1,) = mx.*mx;   D(2,) = my.*my;   D(3,) = my.*my;
	// D(4,) = 2*my.*mz; D(5,) = 2*mx.*mz; D(6,) = 2*mx.*my;
	// D(7,) = 2*mx;     D(8,) = 2*my;     D(9,) = 2*mz;
	// D(10,) = 1.0;
	for (i = 0; i < MAG_DATA_LEN; i++)
	{
		D_ellip[i] = magx[i] * magx[i];
		D_ellip[i + MAG_DATA_LEN * 1] = magy[i] * magy[i];
		D_ellip[i + MAG_DATA_LEN * 2] = magz[i] * magz[i];
		D_ellip[i + MAG_DATA_LEN * 3] = 2.0f*magy[i] * magz[i];
		D_ellip[i + MAG_DATA_LEN * 4] = 2.0f*magx[i] * magz[i];
		D_ellip[i + MAG_DATA_LEN * 5] = 2.0f*magx[i] * magy[i];
		D_ellip[i + MAG_DATA_LEN * 6] = 2.0f*magx[i];
		D_ellip[i + MAG_DATA_LEN * 7] = 2.0f*magy[i];
		D_ellip[i + MAG_DATA_LEN * 8] = 2.0f*magz[i];
		D_ellip[i + MAG_DATA_LEN * 9] = 1.0f;
	}

}

void resolve_eigen(const float k,const float D_ellip[MAG_ELLIP_ROW*MAG_DATA_LEN],float v_out[MAG_ELLIP_ROW],float L_out,float* J_out,float* IK_out)
{
	unsigned int i, j = 0;
	float* S;
	float* D_ellip_trans;
	float* S11;
	float* S12;
	float* S22;
	float* S22_inv;
	float* S12_trans;
	float* mul_temp1;
	float* mul_temp2;
	float* mul_temp3;
	float* mul_temp4;
	float* sub_temp1;
	
	// C11
	float* C11;
	float* C11_inv;
	float* eig_in;

	// L,V
	float* L_calc;
	float* V_calc;

	unsigned int m1 = 0;
	float* Vector_max;
	float lamda = 0.0;
	unsigned char count = 0;
	float mod_v = 0.0;

	// v_eigen
	float* v_eigen;
	float I = 0.0;
	float* det_eigen;
	float  K_value = 0.0;
	// 
  S = (float*)malloc(MAG_ELLIP_ROW*MAG_ELLIP_ROW*sizeof(float));
	D_ellip_trans = (float*)malloc(MAG_DATA_LEN*MAG_ELLIP_ROW*sizeof(float));
	
	// D_ellip'
	RotMatxxf(MAG_ELLIP_ROW, MAG_DATA_LEN, D_ellip, D_ellip_trans);
	// S = D*D'
	MulMatxxf(MAG_ELLIP_ROW, MAG_DATA_LEN, MAG_ELLIP_ROW, D_ellip, D_ellip_trans, S);
	// free D'
	free(D_ellip_trans);

	// S11 = S(1:6,1:6)
	S11 = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM; j++)
			S11[i*MAG_EIGEN_OUT_DIM + j] = S[i*MAG_ELLIP_ROW + j];
	// S12 = S(1:6,7:10)
	S12= (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM_ROW*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM_ROW; j++)
			S12[i*MAG_EIGEN_OUT_DIM_ROW + j] = S[i*MAG_ELLIP_ROW + MAG_EIGEN_OUT_DIM + j];
	// S22 = S(1:6,7:10)
	S22 = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM_ROW*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM_ROW; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM_ROW; j++)
		  S22[i*MAG_EIGEN_OUT_DIM_ROW + j] = S[(i+ MAG_EIGEN_OUT_DIM)*MAG_ELLIP_ROW + MAG_EIGEN_OUT_DIM + j];

	// free
	free(S);

	// S12'
	S12_trans = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM*sizeof(float));
	RotMatxxf(MAG_EIGEN_OUT_DIM, MAG_EIGEN_OUT_DIM_ROW, S12, S12_trans);
	// inv(S22)
	S22_inv = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM_ROW*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM_ROW; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM_ROW; j++)
			S22_inv[i*MAG_EIGEN_OUT_DIM_ROW + j] = S22[i*MAG_EIGEN_OUT_DIM_ROW + j];
	InvMatxf(MAG_EIGEN_OUT_DIM_ROW, S22_inv);
	// inv(S22)*S12'
	mul_temp1 = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM*sizeof(float));
	MulMatxxf(MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM, S22_inv, S12_trans, mul_temp1);
	// S12*inv(S22)*S12'
	mul_temp2 = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	MulMatxxf(MAG_EIGEN_OUT_DIM, MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM, S12, mul_temp1, mul_temp2);
	// S11 - S12*inv(S22)*S12'
	sub_temp1 = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	SubMatxxf(MAG_EIGEN_OUT_DIM, MAG_EIGEN_OUT_DIM,S11, mul_temp2, sub_temp1);
	// C11
	C11 = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	/*** calc c11 ***/
	for (i = 0; i < MAG_EIGEN_OUT_DIM; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM; j++)
			C11[i*MAG_EIGEN_OUT_DIM + j] = 0.0;
	C11[0] = C11[7] = C11[14] = -1.0;
	C11[1] = C11[2] = C11[6] = C11[8] = C11[12] = C11[13] = k*0.5f - 1.0f;
	C11[21] = C11[28] = C11[35] = -k;

	// inv(C11)
	C11_inv = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM; i++)
		for (j = 0; j < MAG_EIGEN_OUT_DIM; j++)
			C11_inv[i*MAG_EIGEN_OUT_DIM + j] = C11[i*MAG_EIGEN_OUT_DIM + j];
	InvMatxf(MAG_EIGEN_OUT_DIM, C11_inv);

	// inv(C11)*(S11 - S12*inv(S22)*S12')
	eig_in = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
	MulMatxxf(MAG_EIGEN_OUT_DIM, MAG_EIGEN_OUT_DIM, MAG_EIGEN_OUT_DIM, C11_inv, sub_temp1, eig_in);

	// free
	free(S11);
	free(S22);
	free(sub_temp1);
	free(C11);
	free(C11_inv);

	//
	L_calc= (float*)malloc(MAG_EIGEN_OUT_DIM*sizeof(float));
	V_calc = (float*)malloc(MAG_EIGEN_OUT_DIM*MAG_EIGEN_OUT_DIM*sizeof(float));
 
 eigcal(eig_in,L_calc,V_calc);


	lamda = L_calc[0];
	count = 0;
	for (m1 = 1; m1 < N_EIG; m1++)
	{
		if (L_calc[m1] > lamda)
		{
			lamda = L_calc[m1];
			count = m1;
		}

	}

	Vector_max = (float*)malloc(MAG_EIGEN_OUT_DIM*sizeof(float));

	for (m1 = 0; m1 < N_EIG; m1++)
		Vector_max[m1] = V_calc[count*N_EIG + m1];

	for (m1 = 0; m1 < N_EIG; m1++)
	{
		mod_v += Vector_max[m1] * Vector_max[m1];
	}

	for (m1 = 0; m1 < N_EIG; m1++)
	{
		Vector_max[m1] /= sqrt(mod_v);
	}
	// free
	free(mul_temp1);
	free(mul_temp2);

	// -inv(S22)*S12'
	mul_temp3 = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*MAG_EIGEN_OUT_DIM*sizeof(float));
	MulMatxxf(MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM, S22_inv, S12_trans, mul_temp3);
	//
	mul_temp4 = (float*)malloc(MAG_EIGEN_OUT_DIM_ROW*sizeof(float));
	MulMatxxf(MAG_EIGEN_OUT_DIM_ROW, MAG_EIGEN_OUT_DIM, 1, mul_temp3, Vector_max, mul_temp4);
	for (i = 0; i < MAG_EIGEN_OUT_DIM_ROW; i++)
		mul_temp4[i] = -mul_temp4[i];
	// v_eigen
	v_eigen = (float*)malloc(MAG_ELLIP_ROW*sizeof(float));
	for (i = 0; i < MAG_EIGEN_OUT_DIM; i++)
		v_eigen[i] = Vector_max[i];
	for (i = 0; i < MAG_EIGEN_OUT_DIM_ROW; i++)
		v_eigen[i + 6] = mul_temp4[i];

	I = v_eigen[0] + v_eigen[1] + v_eigen[2];
	*J_out = v_eigen[0] * v_eigen[1] + v_eigen[1] * v_eigen[2] + v_eigen[0] * v_eigen[2] - v_eigen[3] * v_eigen[3] - v_eigen[4] * v_eigen[4] - v_eigen[5] * v_eigen[5];

	// det
	det_eigen = (float*)malloc(3*3*sizeof(float));
	det_eigen[0] = v_eigen[0];
	det_eigen[4] = v_eigen[1];
	det_eigen[8] = v_eigen[2];
	det_eigen[1] = det_eigen[3] = v_eigen[5];
	det_eigen[2] = det_eigen[6] = v_eigen[4];
	det_eigen[5] = det_eigen[7] = v_eigen[3];

	K_value = sdet(det_eigen, 3);
	*IK_out = I*K_value;
	for (i = 0; i < 10; i++)
		v_out[i] = v_eigen[i];


	// free
	free(S12);
	free(S22_inv);
	free(S12_trans);
	free(mul_temp3);
	free(mul_temp4);

	free(eig_in);
	free(L_calc);
	free(V_calc);
	free(Vector_max);

	free(v_eigen);
	free(det_eigen);

}


void GetEllipFittingPara(float bias[3],float k_matrix[9])
{
	unsigned char i = 0;
	for(i = 0;i<3;i++)
	{
	  bias[i] = bias_mag[i];
	}
	for(i = 0;i<9;i++)
	{
	  k_matrix[i] = matrix_mag[i];
	}

}


unsigned char CheckEllipFittingOk(void)
{
   return ellip_fitting_ok;
}

/************************************************************************
name:	  	GetMagCaliResult
function: return mag calibration result,including mag bias and k matrix
************************************************************************/

void StartMagCali(void)
{
	unsigned short int i = 0;
	_flag_cali_init_done = 0; 
	_flag_eular_init_done = 0;
	_flag_accel_sample_done = 0;
	_flag_mag_sample_done = 0;

	align_accel_num = 0;
	mag_use_cnt = 0;
	ellip_fitting_ok = 0;
	
	memset(&stAhrsOut,0,sizeof(stAhrsOut));
	index_max = 0;
	for(i = 0;i<MAG_DATA_LEN;i++)
	{
     mag_index[i] = 0;
		 
	}


}

unsigned char CheckGyoBiasDone(void)
{
   return _flag_gyo_bias_done;
}
