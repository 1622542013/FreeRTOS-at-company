#include <math.h>
#include <string.h>
#include "MagCali.h"


MCLibInstance mclib_instance;
Measure_in    mea_in;
MagCaliFlag   stMagCaliFlag;
GyoMagState   gmstate;

//unsigned char state_mag = 0;
//EllipFittingResult ell_result;

void MagCaliInit()
{
	/* init gmstate  */
	GyoMagStateInit(&gmstate);
	
	/* init instance */
	mclib_instance.index = 0;
	mclib_instance.magcali_num  = MAG_CALI_DATA_LEN;
  mclib_instance.magcali_type = MC_ELLIPSOID;
	CreatMCLib(&mclib_instance);
}


/*******************************************************************************************


*******************************************************************************************/
unsigned char RotCheck(const float gyox,const float gyoy,const float gyoz,float* theta)
{
	unsigned char result = RESULT_ERROR;
	float thetax = 0.0;
	float thetay = 0.0;
	float thetaz = 0.0;
	
  /*  angular velocity to angle increment,each axis */
	thetax = gyox*GYO_THETA_STEP;
	thetay = gyoy*GYO_THETA_STEP;
	thetaz = gyoz*GYO_THETA_STEP;
	
  /*	Angle increment */
	*theta = sqrtf(thetax*thetax+thetay*thetay+thetaz*thetaz);
	
	/*  Angle increment greater than 0 */
  if(*theta>F32_MACHEPS)
		result = RESULT_OK;
	
	return result;
}

/*******************************************************************************************


*******************************************************************************************/

TpUchar GyoMagStateInit(GyoMagState* gms)
{
	TpUchar result = RESULT_ERROR;

	memset(gms,0,sizeof(GyoMagState));
	
	result = RESULT_OK;
	return result;
}

/*******************************************************************************************


*******************************************************************************************/

//TpUchar IsSetMagAccData(const TpFloat gyo[3],GyoMagState* gms)
TpUchar IsSetMagAccData(const TpFloat gyox,const TpFloat gyoy,const TpFloat gyoz,GyoMagState* gms)
{
  TpUchar result = RESULT_ERROR;
	TpFloat theta = 0.0;
  static TpFloat theta_sum = 0.0;
	/*  if start check gyo theta */
	
	gmstate.theta_sum_cnt++;
	
	if(gmstate.theta_sum_cnt<=GYO_THETA_SUM_CNT)
	{
		RotCheck(gyox,gyoy,gyoz,&theta);
		gmstate.theta_sum+=theta;
		theta_sum = gmstate.theta_sum;
	}
	else if(gmstate.theta_sum_cnt>GYO_THETA_SUM_CNT)
	{
		gmstate.theta_check_start = 1;
		gmstate.theta_sum_cnt = 0;
		gmstate.theta_sum = 0.0;
	}
	
	/*  */
	
	if(gmstate.theta_check_start)
	{
		 gmstate.theta_check_start = 0;
		
	   if(theta_sum>=GYO_THETA_THRESHOLD)
		 { 
			 gmstate.theta_ok = 1;	
       result = RESULT_OK;			 
		 }
		 else
		 {
		   gmstate.theta_ok = 0;
		 }	
	}
	return result;

}


TpUchar IsVec3Zero(const TpFloat fVec[])
{
	 TpUchar result = RESULT_ERROR;
   TpFloat norm = 0.0;

   norm = sqrtf(fVec[0]*fVec[0]+fVec[1]*fVec[1]+fVec[1]*fVec[1]);
	
	 if(norm>F32_MACHEPS)
	    result = RESULT_OK;
	 return result;
}


unsigned char ooo[31] = "$cmd,Mag,cali,faile!!\r\n";
#include "delay.h"
extern float mag_cal_time;
unsigned char MagCaliOnline(unsigned char * pState_mag,EllipFittingResult * pEll_result)
{
	unsigned char result = 0;
	
		/*  mag cali online  */
		if(!stMagCaliFlag.flag_calidone)
		{
			if(stMagCaliFlag.flag_setmag)
			{
				stMagCaliFlag.flag_setmag = 0;
				MagCalibtation(&mclib_instance,&mea_in);			
			}
			*pState_mag = GetEllipFittingState();
			if(*pState_mag==2)
			{
					os_time_init();
							
					GetEllipFittingResult(pEll_result);
				  
				  stMagCaliFlag.flag_calidone = 1;
				  stMagCaliFlag.flag_magcali = 1;
				  if(pEll_result->is_ellipfitting_ok)
					{
            result = 1;		
					}
					else
					{		
						UsartPushMainBuf(GetUsartAddress(USART_2),ooo,26);
						mag_cal_time = os_time();	
					}
			}
		}
	
	return result;

}

TpBool OutMagCaliPara(EllipFittingResult* pResult)
{
	TpUchar result = RESULT_ERROR;
	TpUchar outbuf[100] = {0};
	TpUchar len = 0;
	

	
	return result;
}


TpBool CheckMagCaliOk(MagCaliFlag* pMagCaliFlag,UmiIgmBin* pUmiOutput,RM3100* pRm3100,Measure_in* pMeaIn)
{
	TpUchar result = RESULT_ERROR;
  TpFloat gyo[3];
	if(!pMagCaliFlag->flag_magcali&&!pMagCaliFlag->flag_calidone)
	{
			 gyo[0] = pUmiOutput->imu.gyox;
			 gyo[1] = pUmiOutput->imu.gyoy;
			 gyo[2] = pUmiOutput->imu.gyoz;
			 pMagCaliFlag->flag_setmag = IsSetMagAccData(gyo[0],gyo[1],gyo[2],&gmstate);
			 pMeaIn->mag[0] = pRm3100->magx;
			 pMeaIn->mag[1] = pRm3100->magy;
			 pMeaIn->mag[2] = pRm3100->magz;
	}
	if(pMagCaliFlag->flag_setmag)
		result = RESULT_OK;
	
	
	return result;
	
		 

}

