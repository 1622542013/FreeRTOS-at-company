/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   protocol.c                                                    */
/* Date:        2016.12.09                                                    */
/* Description:                                                               */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"
#include "usart.h"
#include "flash.h"
#include "config.h"
/*============================================================================*/
/*                             Global variables                               */
/*============================================================================*/

Protocol protocol;
OutFlag  outflag;
Logout   logout;
LogFlag  logflag;
OutRate  outrate;

DataSendNav dataSendNav;


TpUint32 baudrate = 0;
TpUchar  buf_check[BUFFSIZE_LOG] = {0};

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

TpVoid ProtocolInit(Protocol *pt)
{
  pt->num = 0;
  pt->start = 0;
  pt->pt = 0;
  pt->flag = 0;
  memset(pt->buf,0,BUFFSIZE_PROTOCOL);
  LogInit(&logout);
  outflag.nav_out = 0;
  outflag.bin_out = 1;
  outflag.imu_out = 0;
  outflag.gnss_out = 0;
	outflag.pos_out = 1;
	
	logflag.nav_log = 0;
	logflag.bin_log = 1;
	logflag.imu_log = 0;
	logflag.gnss_log = 0;
	logflag.pos_log = 1;
	
	outrate.bin_rate = 100;
	outrate.pos_rate = 100;
	
	satComImuOut.info  = INFO_INIT;
	
}

TpVoid LogInit(Logout *lo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = 0;
  lo->index = LOG_BIN;
  lo->rate = 1;
  lo->timer = 0; 
}

/*   */
TpVoid ProtocolDecAscii(Protocol *pt,TpUchar *pBuf,TpUint16 len)
{
	TpUchar  state = 0;
	TpUchar  ch = 0;
	TpUint16 i = 0;
	TpUint16 num = 0;
 
	for(i=0;i<len;i++)
	{
    ch = pBuf[i];
    switch(ch)
    {
			case PROTOCOL_START:
      {
        pt->start = 1;
        pt->buf[0] = ch;
        pt->pt = 1;
        pt->num=0;
      }
      break;
      case PROTOCOL_END_2:
      {
        if(pt->start&&pt->buf[pt->pt-1]==PROTOCOL_END_1)
        {
          pt->buf[pt->pt] = ch;
          pt->num =pt->pt;
          pt->start = 0;
          ProtocolDec(pt);
        }
      }
      break;
      default:
      {
        if(pt->start)
        {
          pt->buf[pt->pt] = ch;
          pt->pt++;
        }
      }
      break;
		}
	}
	
}

TpVoid ProtocolDec(Protocol *pt)
{
  TpUchar j = 0;
  for(j=0;j<pt->num;j++)
  {
    if((pt->buf[j]>=LETTERS_CAPTIAL_A)&&(pt->buf[j]<=LETTERS_CAPTIAL_Z) )
    {
      pt->buf[j] += LETTERS_CAPTIAL_LEN;
    }
  }
  if(!memcmp(PROTOCOL_UMI_HEAD,pt->buf,sizeof(PROTOCOL_UMI_HEAD)-1))
  {
    ARM3Protocol(pt);
  }
  else if(!memcmp(PROTOCOL_UMI_ARM2_HEAD,pt->buf,sizeof(PROTOCOL_UMI_ARM2_HEAD)-1))
  {
    ARM2Protocol(pt,&dataSendNav);
  }
  else if(!memcmp(PROTOCOL_UMI_UBLOX_HEAD,pt->buf,sizeof(PROTOCOL_UMI_UBLOX_HEAD)-1))
  {
    UbloxProtocol(pt);
  }
  else if(!memcmp(PROTOCOL_UMI_ARM3_THROUGH_GNSS_ON,pt->buf,sizeof(PROTOCOL_UMI_ARM3_THROUGH_GNSS_ON)-1))
  {
   flag_throughgps = 1;
   memset(&outflag,0,sizeof(outflag));
   memset(&logout,0,sizeof(logout));
  }
  
  else if(!memcmp(PROTOCOL_UMI_ARM3_THROUGH_GNSS_OFF,pt->buf,sizeof(PROTOCOL_UMI_ARM3_THROUGH_GNSS_OFF)-1))
  {
   flag_throughgps = 0;
   memset(&outflag,0,sizeof(outflag));
  }
	else if(!memcmp(PROTOCOL_UMI_ARM3_SAVE, pt->buf, sizeof(PROTOCOL_UMI_ARM3_SAVE)-1))
  {
    SaveConfig();
  }
  else
  {
    Out_Command_Bad();
  }
 
}

TpVoid ARM2Protocol(Protocol *pt,DataSendNav* dn)
{
  TpBool   result = INLIB_OK;  
	TpUint32 len = 0;
	/* mis cali on */
	len = sizeof(PROTOCOL_UMI_ARM2_MIS_CALI_ON)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_MIS_CALI_ON,pt->buf,len))
  {
    outgps_flag = 0;
    outimu_flag = 1;
		
		outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,PROTOCOL_UMI_ARM2_MIS_CALI_ON);
		UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
    UsartSend(&usart6);
  }
	
	/* mis cali off */
	len = sizeof(PROTOCOL_UMI_ARM2_MIS_CALI_OFF)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_MIS_CALI_OFF,pt->buf,len))
  {
    outgps_flag = 0;
    outimu_flag = 0;
  }

	/* set mis  */
	len = sizeof(PROTOCOL_UMI_ARM2_SET_MIS)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_SET_MIS,pt->buf,len))
  {
    outmis_flag = 1;
    rec_reply = 1;
    
    SetMis(pt,dn);
    
    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,
			                    "$cmd,arm2,set,mis,%f,%f,%f*ff",dn->mis[0],dn->mis[1],dn->mis[2]);
		UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
    UsartSend(&usart6);
   
  }
	
	/* save mis */
	len = sizeof(PROTOCOL_UMI_ARM2_SAVE_MIS)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_SAVE_MIS,pt->buf,len))
  {	
    outmis_flag = 1;
    rec_reply = 1;

    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,PROTOCOL_UMI_ARM2_SAVE_MIS);
		UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
    UsartSend(&usart6);
  }
	
	/* get mis */
	len = sizeof(PROTOCOL_UMI_ARM2_GET_MIS)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_GET_MIS,pt->buf,len))
  {
    outmis_flag = 1;
    rec_reply = 1;

    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,PROTOCOL_UMI_ARM2_GET_MIS);
		UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
    UsartSend(&usart6);
		
  }
	/*  reset */
	len = sizeof(PROTOCOL_UMI_ARM2_RESET)-1;
  if(!memcmp(PROTOCOL_UMI_ARM2_RESET,pt->buf,len))
	{
		outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,PROTOCOL_UMI_ARM2_RESET);
		UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
    UsartSend(&usart6);
	}


}

TpVoid SetMis(Protocol *pt,DataSendNav* dn)
{
  TpChar Buf[3][30] = {0};
  TpUchar p1 = 0,p2 = 0;
  TpUchar offset = sizeof(PROTOCOL_UMI_ARM2_SET_MIS)-1; ;
  while((pt->buf[offset] != LETTERS_STAR))
  {
    if(pt->buf[offset] != LETTERS_COMMA)
    {
      Buf[p1][p2++] = pt->buf[offset];
    }
    else
    {
      p1++;
      p2=0;
    }
    offset++;
  }

  dn->mis[0] = atof(Buf[0]);
  dn->mis[1] = atof(Buf[1]);
  dn->mis[2] = atof(Buf[2]);
}

TpBool ARM3Protocol(Protocol *pt)
{
  TpBool   result = INLIB_OK;
	TpUint32 len     = 0;
	
  len = sizeof(PROTOCOL_UMI_ARM3_OUTPUT_HEAD)-1;
  if(!memcmp(PROTOCOL_UMI_ARM3_OUTPUT_HEAD,pt->buf,len))	
	{
	  OutputProtocol(pt);	
	}
  len = sizeof(PROTOCOL_UMI_ARM3_SET_HEAD)-1;
	if(!memcmp(PROTOCOL_UMI_ARM3_SET_HEAD,pt->buf,len))	
  {
    SetProtocol(pt);
  }
	len = sizeof(PROTOCOL_UMI_ARM3_GET_HEAD)-1;
	if(!memcmp(PROTOCOL_UMI_ARM3_GET_HEAD,pt->buf,len))	
  {
  //  GetProtocol(pt);
  }
	len = sizeof(PROTOCOL_UMI_ARM3_RESET)-1;
  if(!memcmp(PROTOCOL_UMI_ARM3_RESET,pt->buf,len))
  {
    SoftReset();
  }	
else	
 {
    result = INLIB_ERROR;
 }

  return result;
}

TpVoid SetProtocol(Protocol *pt)
{
	if(!memcmp(PROTOCOL_UMI_ARM3_SET_BAUDRATE,pt->buf,sizeof(PROTOCOL_UMI_ARM3_SET_BAUDRATE)-1))
  {
    memset(&outflag,0,sizeof(outflag));
    SetBaudRate(pt->buf, &(syspara.baud_usart2));
  }
}


TpVoid OutputProtocol(Protocol *pt)
{
  TpUchar count = 0;
  TpUchar i=0,j = 0;
  TpFloat temp = 0.0;
  TpChar  buffer[3][10] = {0};
	TpUint32 len = 0;
  
  count = sizeof(PROTOCOL_UMI_ARM3_OUTPUT_HEAD)-1;
  while((pt->buf[count]!=LETTERS_STAR)&&(j<3))
  {
     if(LETTERS_COMMA==pt->buf[count])
     {
       j++;
       i=0;
     }
     else
     {
       buffer[j][i] = pt->buf[count];
       i++;
     }
     count++;
  }
	if(!memcmp(LETTERS_OUTPUT_NULL,buffer[0],4))
	{
		logout.rate = 0;
	}
	else
	{
    logout.rate = (atof(buffer[2]));
	}
  /* nav output */
	len = sizeof(LETTERS_OUTPUT_NAV)-1;
  if(!memcmp(LETTERS_OUTPUT_NAV,buffer[1],len))
  {
    logout.index = LOG_NAV;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.nav_out = 1;
		logflag.nav_log = 1;
  }
	/* nav output */
	len = sizeof(LETTERS_OUTPUT_IMU)-1;
 if(!memcmp(LETTERS_OUTPUT_IMU,buffer[1],len))
  {
    logout.index = LOG_IMU;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.imu_out = 1;
		logflag.imu_log = 1;
  }
	/* bin output */
  if(!memcmp(LETTERS_OUTPUT_BIN,buffer[1],len))
  {
    logout.index = LOG_BIN;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.bin_out = 1;
		logflag.bin_log = 1;
		outrate.bin_rate = logout.rate;
		outrate.pos_rate = LOG_MAXRATE/logout.rate;
  }
	/* gnss output  */
	len = sizeof(LETTERS_OUTPUT_GNSS)-1;
  if(!memcmp(LETTERS_OUTPUT_GNSS,buffer[1],len))
  {
    logout.index = LOG_GNSS;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.gnss_out = 1;
		logflag.gnss_log = 1;
  }
#ifdef UMI_SATCOM_FORMAT	
	len = sizeof(LETTERS_OUTPUT_POS)-1;
  if(!memcmp(LETTERS_OUTPUT_POS,buffer[1],len))
  {
    logout.index = LOG_POS;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.pos_out = 1;
		logflag.pos_log = 1;
  }
#endif
 
  
}

TpVoid LogProtocol(Logout* lo,UmiOutput* uo)
{
  if(lo->rate)
  {
    switch(lo->index)
    {
      case LOG_NAV:
      {
         if(!(logtimer%lo->rate)&&logflag.nav_log)
         {
            outflag.nav_out = 1;
         }
      }
      break;
      case LOG_IMU:
      {
         if(!(logtimer%lo->rate)&&logflag.imu_log)
         {
            outflag.imu_out = 1;
         }
      
      }
      break;
      case LOG_BIN:
      {    
        if((logtimer%lo->rate==0)&&logflag.bin_log)
         {
           outflag.bin_out = 1;
         }
      
      }
      break;
     case LOG_GNSS:
      {    
        if(!(logtimer%lo->rate)&&logflag.gnss_log)
         {
            outflag.gnss_out = 1;
         }
      
      }
      break;
		 case LOG_POS:
		 {
		    if(!(logtimer%lo->rate)&&logflag.pos_log)
         {
            outflag.pos_out = 1;
         }
      
		 }
		 break;
    }
  }
 
  
    
}


TpVoid LogNav(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$nav,%d,%.8f,%.8f,%.4f,%.4f,%.4f,%.4f\r\n",uo->tow_imu,uo->nav.lat,uo->nav.lon,uo->nav.alt,uo->nav.pitch,uo->nav.roll,uo->nav.heading);
  UsartPushSendBuf(&usart2,lo->buf,lo->buf_len,0);
  UsartSend(&usart2);
}

TpVoid LogImu(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$imu,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\r\n",uo->imuv.gyox,uo->imuv.gyoy,uo->imuv.gyoz,uo->imuv.accx,uo->imuv.accy,uo->imuv.accz);
  UsartPushSendBuf(&usart2,lo->buf,lo->buf_len,0);
  UsartSend(&usart2);
}

TpVoid LogGnss(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$gnss,%d,%.8f,%.8f,%.4f,%.4f,%.4f\r\n",uo->gnss.tow_pps,uo->gnss.lat,uo->gnss.lon,uo->gnss.alt,uo->gnss.spd,uo->gnss.heading);
  UsartPushSendBuf(&usart2,lo->buf,lo->buf_len,0);
  UsartSend(&usart2);
}

TpVoid LogBin(Logout* lo,UmiOutput* uo)
{
  
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = sizeof(st_UmiOutput);
  memcpy(lo->buf,&st_UmiOutput,sizeof(st_UmiOutput));
  UsartPushSendBuf(&usart2,lo->buf,lo->buf_len,0);
  UsartSend(&usart2);
}

TpBool UbloxProtocol(Protocol *pt)
{
  TpBool resutlt = INLIB_ERROR;
  
  Ublox_Config(pt->buf,&syspara.ub);

  resutlt = INLIB_OK;
  return resutlt;
}

TpVoid SetBaudRate(uint8_t* data, TpUint32* baudrate)
{
  char Temp_Buffer[30] = {0};
  uint8_t Buffer_P = 0;
  uint8_t P_Offset = sizeof(PROTOCOL_UMI_ARM3_SET_BAUDRATE)-1;
  uint32_t BaudRate = 0;
  
  while((data[P_Offset] != LETTERS_STAR))
  {
    Temp_Buffer[Buffer_P++] = data[P_Offset++];
  }

  BaudRate = atoi(Temp_Buffer);
  
  if( (BaudRate == BAUDRATE_921600) || (BaudRate == BAUDRATE_460800) || (BaudRate == BAUDRATE_230400) ||
      (BaudRate == BAUDRATE_115200) || (BaudRate == BAUDRATE_9600) )
  {
    Out_Config_OK();
    
    if( (*baudrate == BAUDRATE_921600) || (*baudrate == BAUDRATE_460800) || (*baudrate == BAUDRATE_230400) )
    {
      Delay_ms(5);
    }
    else if( (*baudrate == BAUDRATE_115200) )
    {
      Delay_ms(10);
    }
    else if((*baudrate == BAUDRATE_9600) )
    {
      Delay_ms(50);
    }
    else
    {
      Delay_ms(100);
    }
    
    *baudrate = BaudRate;
		
		UsartParaConfig(&usart2,INDEX_USART2,BaudRate);
    
  }
  else
  {
    Out_Command_Bad();
  }
}


TpVoid SaveConfig(TpVoid)
{ 
	__disable_irq() ;
  FlashWrite(&syspara);
	Delay_ms(50);
	 Out_Config_OK();
	__enable_irq() ;
 
}

TpVoid SoftReset(TpVoid)
{
  __set_FAULTMASK(1);
  NVIC_SystemReset();
}

#ifdef UMI_SATCOM_FORMAT

TpUint16 YawDataInitControl(SatComYawInit* yi,SatComYawFlag* yf)
{
	 TpUint16 result = FALSE;
	 yf->init_rec = 1;
   if(yi->yaw_q<=QUALITY_YAW_INIT)
	 {
	    yf->init_ok = 1;
	 }
	 else
	 {
	    yf->init_ok = 0;
	 }


   result = TRUE;
   return result;	

}
TpUint16 YawDataUpdateControl(SatComYawUpdate* yu,SatComYawFlag* yf)
{
	 TpUint16 result = FALSE;
	 yf->update_rec = 1;

	 if(yu->yaw_q<=QUALITY_YAW_UPDATE)
	 {
	    yf->update_ok = 1;
	 }
	 else
	 {
	    yf->update_ok = 0;
	 }


   result = TRUE;
   return result;	

}

#endif

TpVoid UsartDataDec(TpUchar index,TpUchar *pb,TpUint16 num)
{
	switch(index)
	{
		case INDEX_USART2:
		{
		#ifdef 	UMI_SATCOM_FORMAT			
		   if((HEADER_BYTE_FIRST==pb[0])&&(HEADER_BYTE_SECOND==pb[1])&&pb[num-1]==SatComCheckSum(pb,num))
			 {
			    if(MSG_ID_YAW_INIT==pb[2])
					{
					   memcpy(&satComYawInit,pb,sizeof(satComYawInit));
						 YawDataInitControl(&satComYawInit,&satComYawFlag);
					}
					else if(MSG_ID_YAW_UPDATE==pb[2])
					{
					   memcpy(&satComYawUpdate,pb,sizeof(satComYawUpdate));
						 YawDataUpdateControl(&satComYawUpdate,&satComYawFlag);
					}
			 }
			 else if((HEADER_BYTE_FIRST==pb[0])&&(HEADER_BYTE_RESET==pb[1])&&pb[num-1]==SatComCheckSum(pb,num))
			 {
				 if((MSG_ID_ARM3_RESET_1==pb[2])&&(MSG_ID_ARM3_RESET_2==pb[3])&&(MSG_ID_ARM3_RESET_3==pb[4]))
				{	
					   outmis_flag = 1;
						 outimu_len = 0;
						 memset(outimu_buf,0,sizeof(outimu_buf));
						 outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,"$cmd,arm2,reset*ff");
						 UsartPushSendBuf(&usart6,outimu_buf,outimu_len,0);
//             UsartSend(&usart6,outimu_len);
					   Delay_ms(10);
						SoftReset();

				}
			}
		#endif
		
			
		   ProtocolDecAscii(&protocol,pb,num);
			 
		}
		break;
		case INDEX_USART6:
		{
		   ProtocolDecAscii(&protocol,pb,num);
		}
		break;
	}
  
}


#ifdef UMI_FORMAT
TpInt16 UmiCheckSum(TpUchar *pinf, TpInt32 len)
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
#endif

#ifdef UMI_SATCOM_FORMAT
TpUchar SatComCheckSum(TpUchar *pinf, TpInt32 len)
{
  TpUint16 ss = 0;
	TpUchar  check = 0;
  TpUint32 i  = 0;
	
  ss = pinf[0];
  for (i = 1; i < len-1; i++)
  {
    ss ^= pinf[i];
  }

  check = ss&0xff;

  return check;
}
#endif

TpVoid LogSatComImu(Logout* lo,UmiOutput* uo,SatComImuOut* so,SatComOverRange* sr)
{
  TpFloat temp = 0.0;
	TpUchar result = FALSE;
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = sizeof(satComImuOut);
	 
	so->header_first  = HEADER_BYTE_FIRST;
	so->header_second = HEADER_BYTE_SECOND;
	so->msg_id        = MSG_ID_AHRS_IMU_OUT;
	so->roll          = (TpInt16)(uo->nav.roll*FACTOR_ATT);
	so->pitch         = (TpInt16)(uo->nav.pitch*FACTOR_ATT);
	so->yaw           = (TpInt16)(uo->nav.heading*FACTOR_ATT);
	if((uo->nav.fsm_state&FSM_STATE_AHRS)||(uo->nav.fsm_state&FSM_STATE_NAV))
	{
		so->ack         = uo->gnss.ack;
	}
	else
	{
	  so->ack         = 0; 
	}
	so->mode          = MODE_VEHICLE;
	so->debug1        = DEBUG1_DEFAULT;	
	
	result = CheckOverRange(uo,so,sr);
	
	temp = (TpFloat)uo->imuv.tmpx/FACTOR_TMEP_OLD;
	
	
	so->temp          = (TpInt16)temp*FACTOR_TEMP;
	so->timestamp     = uo->nav.timestamp;
	

	if(result==FALSE)
	{
	     so->info = so->info|0x01;
	}
	else if(result==TRUE&&sr->no_over_cnt==INFO_NO_OVER_CNT)
	{
		so->info          = INFO_INIT;
	   sr->no_over_cnt = 0;
		so->info = so->info&(~INFO_OVER_RANGE);
	}
	
	
	memcpy(buf_check,so,sizeof(satComImuOut));
	so->check = SatComCheckSum(buf_check,sizeof(satComImuOut));
	memcpy(lo->buf,so,sizeof(satComImuOut));
	
  UsartPushSendBuf(&usart2,lo->buf,lo->buf_len,0);
 // UsartSend(&usart2,lo->buf_len);
}

TpVoid LogSatComPos(Logout* lo,UmiOutput* uo,SatComPosOut* so)
{
	memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = sizeof(satComPosOut);
  
	so->header_first  = HEADER_BYTE_FIRST;
	so->header_second = HEADER_BYTE_SECOND;
	so->msg_id        = MSG_ID_AHRS_POS_OUT;
	
	so->lat           = uo->nav.lat;
	so->lon           = uo->nav.lon;
	so->alt           = uo->nav.alt;
	so->ve            = uo->nav.ve;
	so->vn            = uo->nav.vn;
  so->vu            = uo->nav.vu;
	
	memcpy(buf_check,so,sizeof(satComPosOut));
	so->check = SatComCheckSum(buf_check,sizeof(satComPosOut));
	memcpy(buf_check,so,sizeof(satComPosOut));
	memcpy(lo->buf,buf_check,lo->buf_len);
	
  UsartPushSendBuf(&usart2,buf_check,lo->buf_len,sizeof(satComImuOut));
//  UsartSend(&usart2,lo->buf_len);
}

TpVoid  StartPrint()
{
	uint16_t num = 0;
  TpChar   buf[300] = {0};
  num =  snprintf(buf,sizeof(buf)-1,"\nYagro UMI-1-G:    Built on  %s  %s\n",__DATE__,__TIME__);
  num += snprintf(buf+num,sizeof(buf)-1,"Version:   %d.%03d.%03d.%03d\n\n",syspara.id[3],syspara.id[2],syspara.id[1],syspara.id[0]);
  num += snprintf(buf+num,sizeof(buf)-1,"Configuration\n");
  num += snprintf(buf+num,sizeof(buf)-1,"COM baud rate:    %dbps\n",syspara.baud_usart2);
  num += snprintf(buf+num,sizeof(buf)-1,"IMU output rate:   %dHz\n",syspara.imu_freq);
  num += snprintf(buf+num,sizeof(buf)-1,"POS output rate: %dHz\n\n",syspara.pos_freq);
 
	UsartPushMainBuf(&usart2,(TpUchar*)buf,num);
  UsartSend(&usart2);

}

TpUchar CheckOverRange(UmiOutput* uo,SatComImuOut* so,SatComOverRange* sr)
{
	TpUchar result = FALSE;
	
	/* gyox */	
	if(uo->imuv.gyox>=INFO_RANGE_GYO)
	{
		so->gyox  = INFO_RANGE_FACTOR-1;
		sr->over_gyox = 1;
	}
	else if(uo->imuv.gyox<=-INFO_RANGE_GYO)
	{
		so->gyox  = -INFO_RANGE_FACTOR+1;
		sr->over_gyox = 1;
	}
	else	
	{
		sr->over_gyox = 0;
	  so->gyox      = (TpInt16)(uo->imuv.gyox*FACTOR_GYO);
	}
	
	/* gyoy */	
	if(uo->imuv.gyoy>=INFO_RANGE_GYO)
	{
		so->gyoy  = INFO_RANGE_FACTOR-1;
		sr->over_gyoy = 1;
	}
	else if(uo->imuv.gyoy<=-INFO_RANGE_GYO)
	{
		so->gyoy  = -INFO_RANGE_FACTOR+1;
		sr->over_gyoy = 1;
	}
	else	
	{
		sr->over_gyoy = 0;
	  so->gyoy          = (TpInt16)(uo->imuv.gyoy*FACTOR_GYO);
	}
	
		/* gyoz */	
	if(uo->imuv.gyoz>=INFO_RANGE_GYO)
	{
		so->gyoz  = INFO_RANGE_FACTOR-1;
		sr->over_gyoz = 1;
	}
	else if(uo->imuv.gyoy<=-INFO_RANGE_GYO)
	{
		so->gyoz  = -INFO_RANGE_FACTOR+1;
		sr->over_gyoz = 1;
	}
	else	
	{
		sr->over_gyoz = 0;
	  so->gyoz          = (TpInt16)(uo->imuv.gyoz*FACTOR_GYO);
	}
	
		/* accx */	
	if(uo->imuv.accx>=INFO_RANGE_ACC)
	{
		so->accx  = INFO_RANGE_FACTOR-1;
		sr->over_accx = 1;
	}
	else if(uo->imuv.accx<=-INFO_RANGE_ACC)
	{
		so->accx  = -INFO_RANGE_FACTOR+1;
		sr->over_accx = 1;
	}
	else	
	{
		sr->over_accx = 0;
	  so->accx          = (TpInt16)(uo->imuv.accx*FACTOR_ACC);
	}
	
	/* accy */	
	if(uo->imuv.accy>=INFO_RANGE_ACC)
	{
		so->accy  = INFO_RANGE_FACTOR-1;
		sr->over_accy = 1;
	}
	else if(uo->imuv.accy<=-INFO_RANGE_ACC)
	{
		so->accy  = -INFO_RANGE_FACTOR+1;
		sr->over_accy = 1;
	}
	else	
	{
		sr->over_accy = 0;
	  so->accy          = (TpInt16)(uo->imuv.accy*FACTOR_ACC);
	}
	
		/* accz */	
	if(uo->imuv.accz>=INFO_RANGE_ACC)
	{
		so->accz  = INFO_RANGE_FACTOR-1;
		sr->over_accz = 1;
	}
	else if(uo->imuv.accy<=-INFO_RANGE_ACC)
	{
		so->accz  = -INFO_RANGE_FACTOR+1;
		sr->over_accz = 1;
	}
	else	
	{
		sr->over_accz = 0;
	  so->accz          = (TpInt16)(uo->imuv.accz*FACTOR_ACC);
	}
	
	
	if(sr->over_gyox||sr->over_gyoy
	 ||sr->over_gyoz||sr->over_accx
	 ||sr->over_accy||sr->over_accz)
	{
	  sr->over_flag = 1;
		sr->no_over_cnt = 0;
	}
	else
	{
		sr->over_flag = 0;
	  sr->no_over_cnt++;
		result = TRUE;
	}
	
	
	return result;
}

TpVoid ThroughProtocol(Protocol *pt)
{


}