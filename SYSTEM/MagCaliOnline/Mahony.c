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
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "Mahony.h"



AhrsOut stAhrsOut;
/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

void 	MahonyInit(const float tau,const float att0[3],AhrsOut* pstAhrsOutInit)
{
	//
	float quat[4];
	float beta;
	float cbn[9];
	
	//
	Att2Quat(att0,quat);	
	//
	memcpy(pstAhrsOutInit->quat,quat,sizeof(quat));
	//
	Quat2Dcm(quat,cbn);
	memcpy(pstAhrsOutInit->cbn,cbn,sizeof(cbn));
	//
	beta = 2.146f/tau;
	pstAhrsOutInit->Kp = 2.0f*beta;
	pstAhrsOutInit->Ki = beta*beta;
	pstAhrsOutInit->tk = 0;
}

void  MahonyUpdate(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float ts)
{
	unsigned char i = 0;
	float norm = 0.0f;
	float cbn[9] = {0.0f};
	float cnb[9] = {0.0f};
	float bxyz[3] = {0.0f};
	float wxyz[3] = {0.0f};
	float exyz[3] = {0.0f};
	
	float acc_z[3] = {0.0f};
	float cross_cbn_acc[3] = {0.0f};
	float cross_wxyz_mag[3] = {0.0f};
	
	float temp_rv[3] = {0.0f};
	float gyo_rad[3] = {0.0f};
	float quat1_temp[4] = {0.0f};
	float quat2_temp[4] = {0.0f};
	float quat_out[4] = {0.0f};
	
	float mag_norm[3] = {0.0};
		
	acc[0] = acc[0]*_G0_F;
	acc[1] = acc[1]*_G0_F;
	acc[2] = acc[2]*_G0_F;
	
	norm = LengthVec3f(acc);
	if(norm>0)
	{
		acc[0] = acc[0]/norm;
		acc[1] = acc[1]/norm;
		acc[2] = acc[2]/norm;
	}
	else
	{
		memset(acc,0,sizeof(acc[3]));
	}
	// mag norm
	
	mag_norm[0] = mag[0];
	mag_norm[1] = mag[1];
	mag_norm[2] = mag[2];
	

  norm = LengthVec3f(mag_norm);
	if(norm>0)
	{
		mag_norm[0] = mag_norm[0]/norm;
		mag_norm[1] = mag_norm[1]/norm;
		mag_norm[2] = mag_norm[2]/norm;
	}
	else
	{
		memset(mag_norm,0,sizeof(mag_norm[3]));
	}
 // bxyz
	memcpy(cbn,pstAhrsIn->cbn,sizeof(cbn));
 //	MulMatxxf(3,3,1,cbn,mag,bxyz);
	MulCbnVec3(cbn,mag_norm,bxyz);
	// 
	norm = sqrtf(bxyz[0]*bxyz[0]+bxyz[1]*bxyz[1]);
	bxyz[0] = 0;
	bxyz[1] = norm;
	// wxyz
	RotMatxxf(3,3,cbn,cnb);
	MulCbnVec3(cnb,bxyz,wxyz);
	
	// acc_z = cbn(3,:);
	acc_z[0] = cbn[6];
	acc_z[1] = cbn[7];
	acc_z[2] = cbn[8];
	// cross(ahrs.Cnb(3,:)',acc)
	VecCross(acc_z,acc,cross_cbn_acc);
	VecCross(wxyz,mag_norm,cross_wxyz_mag);
	exyz[0] = cross_cbn_acc[0] + cross_wxyz_mag[0];
	exyz[1] = cross_cbn_acc[1] + cross_wxyz_mag[1];
	exyz[2] = cross_cbn_acc[2] + cross_wxyz_mag[2];
	// ahrs.exyzInt = ahrs.exyzInt + exyz*ahrs.Ki*ts;
	pstAhrsIn->exyzInt[0] = pstAhrsIn->exyzInt[0] + exyz[0]*pstAhrsIn->Ki*ts;
	pstAhrsIn->exyzInt[1] = pstAhrsIn->exyzInt[1] + exyz[1]*pstAhrsIn->Ki*ts;
	pstAhrsIn->exyzInt[2] = pstAhrsIn->exyzInt[2] + exyz[2]*pstAhrsIn->Ki*ts;	
	
	//ahrs.q = qmul(ahrs.q, rv2q((gyro*(pi/180)-ahrs.Kp*exyz-ahrs.exyzInt)*ts));
	
	gyo_rad[0] = gyo[0]*_D2R_F;
	gyo_rad[1] = gyo[1]*_D2R_F;
	gyo_rad[2] = gyo[2]*_D2R_F;
	//
	temp_rv[0] = (gyo_rad[0] - pstAhrsIn->Kp*exyz[0] - pstAhrsIn->exyzInt[0])*ts;
	temp_rv[1] = (gyo_rad[1] - pstAhrsIn->Kp*exyz[1] - pstAhrsIn->exyzInt[1])*ts;
	temp_rv[2] = (gyo_rad[2] - pstAhrsIn->Kp*exyz[2] - pstAhrsIn->exyzInt[2])*ts;
	
	//
	quat1_temp[0] = pstAhrsIn->quat[0];
	quat1_temp[1] = pstAhrsIn->quat[1];
	quat1_temp[2] = pstAhrsIn->quat[2];
	quat1_temp[3] = pstAhrsIn->quat[3];
	//
	RotVec2Quat(temp_rv,quat2_temp);
	//
	MulQuatf(quat1_temp,quat2_temp,quat_out);
	//
	pstAhrsIn->quat[0] = quat_out[0];
	pstAhrsIn->quat[1] = quat_out[1];
	pstAhrsIn->quat[2] = quat_out[2];
	pstAhrsIn->quat[3] = quat_out[3];
	//
	Quat2Dcm(quat_out,cbn);
	for(i = 0;i<9;i++)
	   pstAhrsIn->cbn[i] = cbn[i];
		 
	pstAhrsIn->tk = pstAhrsIn->tk + ts;	
	
}

void  MahonyUpdateGyoInte(AhrsOut* pstAhrsIn,float gyo[3],float acc[3],float mag[3],const float ts)
{
	unsigned char i = 0;
	float norm = 0.0f;
	float cbn[9] = {0.0f};
	float exyz[3] = {0.0f};
	
	float acc_z[3] = {0.0f};
	float cross_cbn_acc[3] = {0.0f};
	
	float temp_rv[3] = {0.0f};
	float gyo_rad[3] = {0.0f};
	float quat1_temp[4] = {0.0f};
	float quat2_temp[4] = {0.0f};
	float quat_out[4] = {0.0f};
	
	float gyo_norm = 0.0f;
	
//	gyo[0] = gyo[0]-pstAhrsIn->gyo_bias[0];
//	gyo[1] = gyo[1]-pstAhrsIn->gyo_bias[1];
//	gyo[2] = gyo[2]-pstAhrsIn->gyo_bias[2];
	
	// gyo norm
	gyo_norm = sqrtf(gyo[0]*gyo[0]+gyo[1]*gyo[1]+gyo[2]*gyo[2]);
	
	if(gyo_norm<MIN_GYO_NORM)
	{
			return;
	}
	
	// acc_norm
	acc[0] = acc[0]*_G0_F;
	acc[1] = acc[1]*_G0_F;
	acc[2] = acc[2]*_G0_F;
	
	norm = LengthVec3f(acc);
	if(norm>0)
	{
		acc[0] = acc[0]/norm;
		acc[1] = acc[1]/norm;
		acc[2] = acc[2]/norm;
	}
	else
	{
		memset(acc,0,sizeof(acc[3]));
	}
	memcpy(cbn,pstAhrsIn->cbn,sizeof(cbn));
	// acc_z = cbn(3,:);
	acc_z[0] = cbn[6];
	acc_z[1] = cbn[7];
	acc_z[2] = cbn[8];
	// cross(ahrs.Cnb(3,:)',acc)
	VecCross(acc_z,acc,cross_cbn_acc);
	exyz[0] = cross_cbn_acc[0];
	exyz[1] = cross_cbn_acc[1];
	exyz[2] = cross_cbn_acc[2];
	// ahrs.exyzInt = ahrs.exyzInt + exyz*ahrs.Ki*ts;
	pstAhrsIn->exyzInt[0] = pstAhrsIn->exyzInt[0] + exyz[0]*pstAhrsIn->Ki*ts;
	pstAhrsIn->exyzInt[1] = pstAhrsIn->exyzInt[1] + exyz[1]*pstAhrsIn->Ki*ts;
	pstAhrsIn->exyzInt[2] = pstAhrsIn->exyzInt[2] + exyz[2]*pstAhrsIn->Ki*ts;	
	
	//ahrs.q = qmul(ahrs.q, rv2q((gyro*(pi/180)-ahrs.Kp*exyz-ahrs.exyzInt)*ts));

	/*****************************************/
	gyo_rad[0] = gyo[0]*_D2R_F;
	gyo_rad[1] = gyo[1]*_D2R_F;
	gyo_rad[2] = gyo[2]*_D2R_F;
	
	//
	temp_rv[0] = (gyo_rad[0] - pstAhrsIn->Kp*exyz[0] - pstAhrsIn->exyzInt[0])*ts;
	temp_rv[1] = (gyo_rad[1] - pstAhrsIn->Kp*exyz[1] - pstAhrsIn->exyzInt[1])*ts;
	temp_rv[2] = (gyo_rad[2] - pstAhrsIn->Kp*exyz[2] - pstAhrsIn->exyzInt[2])*ts;
	
	//
	quat1_temp[0] = pstAhrsIn->quat[0];
	quat1_temp[1] = pstAhrsIn->quat[1];
	quat1_temp[2] = pstAhrsIn->quat[2];
	quat1_temp[3] = pstAhrsIn->quat[3];
	//
	RotVec2Quat(temp_rv,quat2_temp);
	//
	MulQuatf(quat1_temp,quat2_temp,quat_out);
	//
	pstAhrsIn->quat[0] = quat_out[0];
	pstAhrsIn->quat[1] = quat_out[1];
	pstAhrsIn->quat[2] = quat_out[2];
	pstAhrsIn->quat[3] = quat_out[3];
	//
	Quat2Dcm(quat_out,cbn);
	for(i = 0;i<9;i++)
	   pstAhrsIn->cbn[i] = cbn[i];
		 
	pstAhrsIn->tk = pstAhrsIn->tk + ts;	

}
