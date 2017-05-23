/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   protocol.c                                                    */
/* Date:        2016.7.20                                                     */
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
#include "globals.h"
#include "usart.h"
#include "ublox.h"
#include "Flash.h"
#include "config.h"
/*============================================================================*/
/*                             Global variables                               */
/*============================================================================*/

Protocol protocol;
OutFlag  outflag;
Logout   logout;
LogFlag  logflag;
TpFloat mis[3] = {0};
TpUint32 logtimer = 0;

TpUint32  baudrate = 0;


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
	
	logflag.nav_log = 0;
	logflag.bin_log = 1;
	logflag.imu_log = 0;
	logflag.gnss_log = 0;
}

TpVoid LogInit(Logout *lo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = 0;
  lo->index = LOG_BIN;
  lo->rate = 1;
  lo->timer = 0;
  
  
  
}

TpVoid ProtocolDecAsc(Protocol *pt,TpUchar *pBuff,TpUchar u8num)
{
  TpUchar i=0;
  TpUchar u8Byte;
 
	for(i=0;i<u8num;i++)
	{
    u8Byte = pBuff[i];
    switch(u8Byte)
    {
      case '$':
      case '#':
      {
        pt->start = 1;
        pt->buf[0] = u8Byte;
        pt->pt = 1;
        pt->num=0;
      }
      break;
      case 0x0A:
      {
        if(pt->start)
        {
          pt->buf[pt->pt] = u8Byte;
          pt->num =pt->pt;
          pt->start = 0;
          DecodeProtocol(pt);
        }
      }
      break;
      default:
      {
        if(pt->start)
        {
          pt->buf[pt->pt] = u8Byte;
          pt->pt++;
        }
      }
      break;
		}
	}
}

TpVoid DecodeProtocol(Protocol *pt)
{
  TpUchar j=0;
  
  for(j=0;j<pt->num;j++)
  {
    if( (pt->buf[j]>=0x41)&&(pt->buf[j]<=0x5a) )
    {
      pt->buf[j] += 0x20;
    }
  }
  
  if(!memcmp("$cmd,umi,",pt->buf,sizeof("$cmd,umi,")-1))
  {
    UmiProtocol(pt);
  }
  else if(!memcmp("$cmd,nav,",pt->buf,sizeof("$cmd,nav,")-1))
  {
    NavProtocol(pt);
  }
  else if(!memcmp("$cmd,ublox,",pt->buf,sizeof("$cmd,ublox,")-1))
  {
    UbloxProtocol(pt);
  }
  else if(!memcmp("$cmd,through,gps,on",pt->buf,sizeof("$cmd,through,gps,on")-1))
  {
   flag_throughgps = 1;
   memset(&outflag,0,sizeof(outflag));
   memset(&logout,0,sizeof(logout));
  }
  
  else if(!memcmp("$cmd,through,gps,off",pt->buf,sizeof("$cmd,through,gps,off")-1))
  {
   flag_throughgps = 0;
   memset(&outflag,0,sizeof(outflag));
  }
	else if(!memcmp("$cmd,save", pt->buf, sizeof("$cmd,save")-1))
  {
    SaveConfig();
  }
  else
  {
    Out_Command_Bad();
  }
 
}

TpVoid NavProtocol(Protocol *pt)
{   
  if(!memcmp("$cmd,nav,mis,cali",pt->buf,sizeof("$cmd,nav,mis,cali")-1))
  {
    outgps_flag = 0;
    outimu_flag = 1;
  }
  else if(!memcmp("$cmd,nav,mis,cali,off",pt->buf,sizeof("$cmd,nav,mis,cali,off")-1))
  {
    outgps_flag = 0;
    outimu_flag = 0;
  }

  else if(!memcmp("$cmd,nav,set,mis",pt->buf,sizeof("$cmd,nav,set,mis")-1))
  {
    outmis_flag = 1;
    rec_reply = 1;
    
    Set_Mis(pt);
    
    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,"$cmd,arm2,set,mis,%f,%f,%f*ff",mis[0],mis[1],mis[2]);
   
  }
  else if(!memcmp("$cmd,nav,savemis",pt->buf,sizeof("$cmd,nav,savemis")-1))
  {
    outmis_flag = 1;
    rec_reply = 1;

    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,"$cmd,arm2,savemis*ff");
  }
  else if(!memcmp("$cmd,nav,get,mis",pt->buf,sizeof("$cmd,nav,get,mis")-1))
  {
    outmis_flag = 1;
    rec_reply = 1;

    outimu_len = 0;
    memset(outimu_buf,0,sizeof(outimu_buf));
    outimu_len = snprintf((char*)outimu_buf,sizeof(outimu_buf)-1,"$cmd,arm2,get,mis*ff");
  }


}

TpVoid Set_Mis(Protocol *pt)
{
  char Temp_Buffer[3][30]={0};
  TpUchar Buffer_P1=0,Buffer_P2=0;
  TpUchar P_Offset=17;
  while((pt->buf[P_Offset] != '*'))
  {
    if(pt->buf[P_Offset] != ',')
    {
      Temp_Buffer[Buffer_P1][Buffer_P2++] = pt->buf[P_Offset];
    }
    else
    {
      Buffer_P1++;
      Buffer_P2=0;
    }
    P_Offset++;
  }

  mis[0] = atof(Temp_Buffer[0]);
  mis[1] = atof(Temp_Buffer[1]);
  mis[2] = atof(Temp_Buffer[2]);
}


/*  set mag para  */

TpVoid Set_MagPara(Protocol *pt)
{
	unsigned char i,j = 0;
	
	
  char Temp_Buffer[12][30]={0};
  TpUchar Buffer_P1=0,Buffer_P2=0;
  TpUchar P_Offset=21;
	
  while((pt->buf[P_Offset] != '*'))
  {
    if(pt->buf[P_Offset] != ',')
    {
      Temp_Buffer[Buffer_P1][Buffer_P2++] = pt->buf[P_Offset];
    }
    else
    {
      Buffer_P1++;
      Buffer_P2=0;
    }
    P_Offset++;
  }

//  mis[0] = atof(Temp_Buffer[0]);
//  mis[1] = atof(Temp_Buffer[1]);
//  mis[2] = atof(Temp_Buffer[2]);
	
	for(i = 0;i < 3;i++)
	  for(j = 0;j<3;j++)
	    {
				syspara.mag.k_mag[i][j] = atof(Temp_Buffer[i*3+j]);			
			}
	
	for(i = 0;i < 3;i++)
			syspara.mag.bias_mag[i] = atof(Temp_Buffer[9+i]);
}


TpVoid Get_MagPara(Protocol *pt)
{

}
/////////////////////////////////////////////////////////////////////////

TpBool UmiProtocol(Protocol *pt)
{
  TpBool resutlt = INLIB_ERROR;
  
  if(!memcmp("$cmd,umi,output,",pt->buf,sizeof("$cmd,umi,output,")-1))	
	{
    pt->flag = 1;
	  OutputProtocol(pt);	
	}
  else if(!memcmp("$cmd,umi,set,",pt->buf,sizeof("$cmd,umi,set,")-1))	
  {
    SetProtocol(pt);
  }
	 else if(!memcmp("$cmd,umi,get,magpara*ff",pt->buf,sizeof("$cmd,umi,get,magpara*ff")-1))	
  {
    Get_MagPara(pt);
  }
	
  else if(!memcmp("$cmd,umi,arm3,reset",pt->buf,sizeof("$cmd,umi,arm3,reset")-1))
  {
    SoftReset();
  }	
	else if(!memcmp("$cmd,umi,magcali,on*ff",pt->buf,sizeof("$cmd,umi,magcali,on*ff")-1))
	{
	   flag_magcali = 1;
	}
else	
 {
    pt->flag = 0;
 }

  resutlt = INLIB_OK;
  return resutlt;
}

TpVoid SetProtocol(Protocol *pt)
{
	if(!memcmp("$cmd,umi,set,baudrate,",pt->buf,sizeof("$cmd,umi,set,baudrate,")-1))
  {
    outflag.bin_out = 0;
		outflag.gnss_out = 0;
		outflag.imu_out = 0;
		outflag.nav_out = 0;
    SetBaudRate(pt->buf, &(syspara.baud_usart2));
  }
	
	if(!memcmp("$cmd,umi,set,magpara,",pt->buf,sizeof("$cmd,umi,set,magpara,")-1))
  {
    outflag.bin_out = 0;
		outflag.gnss_out = 0;
		outflag.imu_out = 0;
		outflag.nav_out = 0;
    Set_MagPara(pt);
		SaveConfig();
  }
	
	
}


TpVoid OutputProtocol(Protocol *pt)
{
  TpUchar count = 0;
  TpUchar i=0,j = 0;
  float temp = 0.0;
  TpChar buffer[3][10] = {0};
  
  count = sizeof("$cmd,umi,output,")-1;
  while((pt->buf[count]!='*')&&(j<3))
  {
     if(','==pt->buf[count])
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
	if(!memcmp("null",buffer[1],4))
	{
		logout.rate = 0;
	}
	else
	{
		temp = (1/atof(buffer[1]));
    logout.rate = LOG_MAXRATE / temp;
	}
  
  if(!memcmp("nav",buffer[0],sizeof("nav")-1))
  {
    logout.index = LOG_NAV;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.nav_out = 1;
		logflag.nav_log = 1;
  }
  else if(!memcmp("imu",buffer[0],sizeof("imu")-1))
  {
    logout.index = LOG_IMU;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.imu_out = 1;
		logflag.imu_log = 1;
  }
  else if(!memcmp("bin",buffer[0],sizeof("bin")-1))
  {
    logout.index = LOG_BIN;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.bin_out = 1;
		logflag.bin_log = 1;
  }
  else if(!memcmp("gnss",buffer[0],sizeof("gnss")-1))
  {
    logout.index = LOG_GNSS;
		memset(&outflag,0,sizeof(outflag));
		memset(&logflag,0,sizeof(logflag));
		outflag.gnss_out = 1;
		logflag.gnss_log = 1;
  }
 
  
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
        if(!(logtimer%lo->rate)&&logflag.bin_log)
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
    }
  }
 
  
    
}


TpVoid LogNav(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$nav,%d,%.8f,%.8f,%.4f,%.4f,%.4f,%.4f\r\n",uo->tow_imu,uo->nav.lat,uo->nav.lon,uo->nav.alt,uo->nav.pitch,uo->nav.roll,uo->nav.heading);
  UsartPushBuf(&usart2,lo->buf,lo->buf_len);
  UsartSendBuf(&usart2,lo->buf_len);
}

TpVoid LogImu(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$imu,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\r\n",uo->imuv.gyox,uo->imuv.gyoy,uo->imuv.gyoz,uo->imuv.accx,uo->imuv.accy,uo->imuv.accz);
  UsartPushBuf(&usart2,lo->buf,lo->buf_len);
  UsartSendBuf(&usart2,lo->buf_len);
}

TpVoid LogGnss(Logout* lo,UmiOutput* uo)
{
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = snprintf((TpChar*)lo->buf,BUFFSIZE_LOG-1,"$gnss,%d,%.8f,%.8f,%.4f,%.4f,%.4f\r\n",uo->gnss.tow_pps,uo->gnss.lat,uo->gnss.lon,uo->gnss.alt,uo->gnss.spd,uo->gnss.heading);
  UsartPushBuf(&usart2,lo->buf,lo->buf_len);
  UsartSendBuf(&usart2,lo->buf_len);
}

TpVoid LogBin(Logout* lo,UmiOutput* uo)
{
  
  memset(lo->buf,0,BUFFSIZE_LOG);
  lo->buf_len = sizeof(st_UmiOutput);
  memcpy(lo->buf,&st_UmiOutput,sizeof(st_UmiOutput));
  UsartPushBuf(&usart2,lo->buf,lo->buf_len);
  UsartSendBuf(&usart2,lo->buf_len);
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
  uint8_t P_Offset = sizeof("$cmd,umi,set,baudrate,")-1;
  uint32_t BaudRate = 0;
  
  while((data[P_Offset] != '*'))
  {
    Temp_Buffer[Buffer_P++] = data[P_Offset++];
  }

  BaudRate = atoi(Temp_Buffer);
  
  if( (BaudRate == BAUD_RATE_921600) || (BaudRate == BAUD_RATE_460800) || (BaudRate == BAUD_RATE_230400) ||
      (BaudRate == BAUD_RATE_115200) || (BaudRate == BAUD_RATE_57600)  || (BaudRate == BAUD_RATE_38400)  ||
      (BaudRate == BAUD_RATE_19200)  || (BaudRate == BAUD_RATE_9600)   || (BaudRate == BAUD_RATE_4800)   ||
      (BaudRate == BAUD_RATE_2400) )
  {
    Out_Config_OK();
    
    if( (*baudrate == BAUD_RATE_921600) || (*baudrate == BAUD_RATE_460800) || (*baudrate == BAUD_RATE_230400) )
    {
      Delay_ms(5);
    }
    else if( (*baudrate == BAUD_RATE_115200) || (*baudrate == BAUD_RATE_57600) || (*baudrate == BAUD_RATE_38400) )
    {
      Delay_ms(10);
    }
    else if( (*baudrate == BAUD_RATE_19200) || (*baudrate == BAUD_RATE_9600) || (*baudrate == BAUD_RATE_4800) )
    {
      Delay_ms(50);
    }
    else
    {
      Delay_ms(100);
    }
    
    *baudrate = BaudRate;
		
		UsartParaConfig(&usart2,BaudRate);
    
  }
  else
  {
    Out_Command_Bad();
  }
}


TpVoid SaveConfig(TpVoid)
{ 
	__disable_irq() ;
 // FlashWrite(&syspara);
	Delay_ms(50);
	 Out_Config_OK();
	__enable_irq() ;
 
}

TpVoid SoftReset(TpVoid)
{
  __set_FAULTMASK(1);
  NVIC_SystemReset();
}
