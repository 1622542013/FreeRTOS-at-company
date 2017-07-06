#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_bin.h"
#include "send_message.h"
#include "command.h"
#include "usart.h"

Commond_ACC_GYRO_PARA  cal_para;
Commond_Bin commond_bin;

TpChar* PackAccPara(TpChar* buff_processed[],TpUint16 command_id)
{	
    cal_para.head[0] 		= COMMAND_BIN_HEAD0;
		cal_para.head[1] 		= COMMAND_BIN_HEAD1;
		cal_para.frame_id 	= FRAME_ID_SET;
		cal_para.command_id = command_id;
		cal_para.length     = sizeof(cal_para);
		
		cal_para.ks0[0] = 	atof(buff_processed[ks0_location]);
		cal_para.ks0[1] = 	atof(buff_processed[ks0_location + 1]);
		cal_para.ks0[2] = 	atof(buff_processed[ks0_location + 2]);
	
		cal_para.ks1[0] = 	atof(buff_processed[ks1_location]);
		cal_para.ks1[1] = 	atof(buff_processed[ks1_location + 1]);
		cal_para.ks1[2] = 	atof(buff_processed[ks1_location + 2]);
		
		cal_para.kz0[0] = 	atof(buff_processed[kz0_location]);
		cal_para.kz0[1] = 	atof(buff_processed[kz0_location + 1]);
		cal_para.kz0[2] = 	atof(buff_processed[kz0_location + 2]);
	
		cal_para.kz1[0] = 	atof(buff_processed[kz1_location]);
		cal_para.kz1[1] = 	atof(buff_processed[kz1_location + 1]);
		cal_para.kz1[2] = 	atof(buff_processed[kz1_location + 2]);
			
		cal_para.n0[0] 	= 	atof(buff_processed[n0_location]);
		cal_para.n0[1] 	= 	atof(buff_processed[n0_location + 1]);
		cal_para.n0[2] 	= 	atof(buff_processed[n0_location + 2]);
		
		cal_para.n1[0] 	= 	atof(buff_processed[n1_location]);
		cal_para.n1[1]  = 	atof(buff_processed[n1_location + 1]);
		cal_para.n1[2]  = 	atof(buff_processed[n1_location + 2]);
		
		cal_para.n2[0]  = 	atof(buff_processed[n2_location]);
		cal_para.n2[1]  = 	atof(buff_processed[n2_location + 1]);
		cal_para.n2[2]  = 	atof(buff_processed[n2_location + 2]);
			
		cal_para.check = CheckSumByte((unsigned char *)&cal_para,cal_para.length -1);
		cal_para.end   = COMMAND_BIN_END;
		
		return (TpChar*)&cal_para;
}

TpChar* CommondBin(TpChar frame_id,TpUint16 command_id,TpUint32 data)
{
	commond_bin.head[0] = COMMAND_BIN_HEAD0;
	commond_bin.head[1] = COMMAND_BIN_HEAD1;
	
	commond_bin.frame_id = frame_id;
	commond_bin.command_id = command_id;
	commond_bin.length = sizeof(commond_bin);
	commond_bin.data.udata = data;
	
	commond_bin.check = CheckSumByte((unsigned char *)&commond_bin,commond_bin.length -1);
	commond_bin.end = COMMAND_BIN_END;
	
	return (TpChar*)&commond_bin;
}


char freed_back_buff[512];
TpVoid DecodeCommondBin(TpUchar* commnd_bin,TpUint16 length)
{
	Decode_Commond_Bin commond_upper_half;
	Commond_ACC_GYRO_PARA CAL_PARA;
	Commond_Bin   common_bin;

	TpUint16 out_len;
//	TpUchar  check = 0;

	memcpy(&commond_upper_half,commnd_bin,sizeof(commond_upper_half));
	
	switch(commond_upper_half.command_id)
	{ 
		case COMMAND_ID_ACC_PARA :
				{
					memcpy(&CAL_PARA,commnd_bin,sizeof(CAL_PARA));
					//AccCalPara(&CAL_PARA);
				}
				break;
		case COMMAND_ID_GYRO_PARA :
				{
					memcpy(&CAL_PARA,commnd_bin,sizeof(CAL_PARA));
				//	GyroCalPara(&CAL_PARA);
				}
				break;
		case COMMAND_ID_NAV_MODE :
					memcpy(&common_bin,commnd_bin,sizeof(common_bin));
					switch(common_bin.data.udata)
					{
						case DATA_LAND_MODE:
						{							
							 out_len = snprintf(freed_back_buff,sizeof(NAV_LAND_MODE_OUT),NAV_LAND_MODE_OUT);
							 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)freed_back_buff,out_len);
							 break;
						}
						case DATA_AIR_MODE:
						{
							 out_len = snprintf(freed_back_buff,sizeof(NAV_AIR_MODE_OUT),NAV_AIR_MODE_OUT);
							 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)freed_back_buff,out_len);
							 break;
						}
						case DATA_OCEAN_MODE:
						{
							 out_len = snprintf(freed_back_buff,sizeof(NAV_OCEAN_MODE_OUT),NAV_OCEAN_MODE_OUT);
							 UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)freed_back_buff,out_len);
							 break;		
						}
							default :  break;
					}
					break;
		
		case COMMAND_ID_LEVEARM :
			
		case COMMAND_ID_CONFIG_OK :
		UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)FREEDBACK_OK,sizeof(FREEDBACK_OK)-1);
		break;
		
		case COMMAND_ID_CONFIG_ERROR :			
		UsartPushMainBuf(GetUsartAddress(USART_2),(TpUchar*)NOT_A_VALID_COMMAND,sizeof(NOT_A_VALID_COMMAND)-1);
		break;
			
	  default :break;		
	}

}
