/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
<<<<<<< HEAD
/* File name:   globals.c                                                     */
/* Date:        2017.4.29                                                     */
=======
/* File name:   user_define.c                                                         */
/* Date:        2016.7.21                                                     */
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/* Description:                                                              */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "globals.h"
#include "definition.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

<<<<<<< HEAD

#define NUM_MAX 							2e32-1

/*============================================================================*/
/*                              Global functions                              */
/*============================================================================*/

short int CheckSum(unsigned char *pinf, int len)
{
  unsigned short ss = 0;
  unsigned char  c1 = 0;
  unsigned char  c2 = 0;
  int            i  = 0;

  for (i = 2; i < len - 2; i = i + 2)
  {
    c1 += pinf[i];
  }

  for (i = 3; i < len - 2; i = i + 2)
  {
    c2 += pinf[i];
  }

  ss = (c1<<8) + c2;

  return ss;
}

TpUchar CheckSumByte(TpUchar* Buffer, TpUint16 Length)
{
  TpUint32 sum     = 0;
  TpUint16 i       = 0;
  TpUchar  sum_low = 0;

  for(i = 2; i < (Length - 1); i++)
  {
    sum += Buffer[i];
  }

  sum_low = sum & 0x00ff;
  
  return sum_low;
}


TpBool My_atoi(const char* buff,int32_t* num)
{
	TpBool  result = RESULT_ERROR;
	TpInt32  sign = 0;
	TpInt32 int_data = 0;
	
	const char *str;
	
	str = buff;
	
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	else
	{
		sign = 1;
	}
	
	while(*str != '\0')
	{	
		if( (*str >= '0')&&(*str <= '9') )
		{
			int_data = int_data * 10 + (*str - '0');
			if(int_data > NUM_MAX)
			{
		    result = RESULT_PARA_NOT_VALID;
				return result;
			}
			
			str++;
		}
		else
		{
		    result = RESULT_PARA_NOT_VALID;
				return result;
		}
	}
	
	if(sign == -1)
	{
		int_data = -int_data;
	}
	
	result = RESULT_OK;
	*num = int_data;
	
	return result;
	
}
=======
UmiOutput st_UmiOutput;
UmiOutIMU st_UmiOutIMU;
UmiMagSend    umiMagSend;

/*  add for 54 suo */
#ifdef UMI_SATCOM_FORMAT
SatComYawInit    satComYawInit;
SatComYawUpdate  satComYawUpdate;
SatComYawFlag    satComYawFlag;
SatComImuOut     satComImuOut;
SatComPosOut     satComPosOut;
SatComOverRange  satComOverRange;
#endif

/* out pitch and roll */
TpUchar outgps_flag = 1;
TpUchar outimu_flag = 0;
TpUchar outimu_len = 0;
TpUchar outimu_buf[50] = {0};

TpUchar outmis_flag = 0;
TpUchar rec_reply = 0;

TpUchar flag_throughgps = 0;
TpUint32 logtimer = 0;


/*============================================================================*/
/*                              Global functions                              */
/*============================================================================*/

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
