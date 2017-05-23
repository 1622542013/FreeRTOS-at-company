/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   gnss.c                                                      */
/* Date:        2016.7.25                                                     */
/* Description: gnss.c                                                       */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/
#include <math.h>
#include "gnss.h"
<<<<<<< HEAD
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
#include "command.h"
#include "config.h"
=======
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "usart.h"
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

GnssOut gnssout;
<<<<<<< HEAD
PackageGnss package;
=======
Package package;
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
Nmea    nmea;
GnssRec gnssrec;

TpUint32 old_time = 0;
TpUint16 diff_time = 0;
TpUint32 new_time = 0;

TpChar TempStr[50]={0};
TpDouble dd = 0.0;
TpDouble mm = 0.0;
TpUint32 u32Time1,u32Time2;
TpChar str_Temp[20] = {0};
TpUint32 u32CRC = 0;
TpUchar u8CheckNmea = 0;


TpUchar u8DayNum = 0;
TpUchar data_to_arm2[100];   /* send data to arm2 */
TpUchar  fix_cnt = 0;
TpUchar  pps_start = 0;

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/*****************************************************************************
* function name:  HardWare_Init
* description:    config systick,TIM and GPIO
* input:          none
* output:         none
******************************************************************************/

<<<<<<< HEAD
TpVoid PackageInit(PackageGnss *pa)
{
  pa->buff_len=0;
  pa->start=0;
=======
TpVoid PackageInit(Package *pa)
{
  pa->buff_len=0;
  pa->start=0;
 // pa->data_ptr = (TpUchar *)malloc(sizeof(TpUchar)*GNSS_PACK_SIZE);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  memset(pa->data_ptr,0,GNSS_PACK_SIZE);
  pa->pt=0;
}

TpVoid PackageRec(TpUchar *pbuf,TpUint16 num)
{
  TpUint16 i=0;
  TpUchar u8Byte;
  for(i=0;i<num;i++)
  {
    u8Byte = pbuf[i];
    switch(u8Byte)
    {
      case '$':
      case '#':
      {
        package.start = 1;
        package.data_ptr[0] = u8Byte;
        package.pt = 1;
        package.buff_len=0;
      }
      break;
      case 0x0A:
      {
<<<<<<< HEAD
        if(package.start)
=======
  //      if(package.data_ptr[package.pt]==0x0D&&package.start)
         if(package.start)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
        {
          package.start = 0;
          package.pt+=1;
          package.data_ptr[package.pt] = u8Byte;
          package.buff_len=package.pt;

<<<<<<< HEAD
          GnssDecode(&package,&gnssrec);	
          GnssCombine(&gnssout,&gnssrec);
					UsartPushMainBuf(GetUsartAddress(USART_1),(TpUchar*)&gnssout,sizeof(GnssOut)-1);			
=======
          GnssDecode(&package,&gnssrec);
    //      GnssCombine(&gnssout,&gnssrec);
       

>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
       }

      }
      default:
      {
        if(package.start)
        {
           package.data_ptr[package.pt] = u8Byte;
           package.pt+=1;
        }
      }
    }
  }
<<<<<<< HEAD
	
	
}

TpVoid GnssDecode(PackageGnss* pa,GnssRec *gr)
{
  TpUchar u8Result;

#if (UBLOX_OPEN)
=======
}

TpVoid GnssDecode(Package* pa,GnssRec *gr)
{
  TpUchar u8Result;

#ifdef UBLOX_ON
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  if(!memcmp("$GNGGA,",pa->data_ptr,7))
#else
  if(!memcmp("$GPGGA,",pa->data_ptr,7))
#endif
  {
    if(GPGGA_IN==GpggaDecode(pa,gr))
    {
      gr->flag |= GPGGA_FLAG;
    }
  }
<<<<<<< HEAD
#if (UBLOX_OPEN)
=======
#ifdef UBLOX_ON
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
  else if(!memcmp("$GNRMC,",pa->data_ptr,7))
#else
  else if(!memcmp("$GPRMC,",pa->data_ptr,7))
#endif
	{
		if(GPRMC_IN==GprmcDecode(pa,gr))
		{
			gr->flag |= GPRMC_FLAG;
		}
	}
  else if(!memcmp("$GPHDT,",pa->data_ptr,7))
	{
		if(GPHDT_IN==GphdtDecode(pa,gr))
		{
			gr->flag |= GPHDT_FLAG;
		}
	}
  else if(!memcmp("#BESTVELA,",pa->data_ptr,10))
	{
    u8Result = BestVelDec(pa,gr);
    if(BESTVELA_IN==u8Result)
    {
      gr->flag |= BESTVELA_FLAG;
    }
	}
  else if(!memcmp("#HEADINGA,",pa->data_ptr,10))
	{
    u8Result = HeadingaDec(pa,gr);
    if(HEADINGA_IN==u8Result)
    {
      gr->flag |= HEADINGA_FLAG;
    }
	}
}

<<<<<<< HEAD
TpUchar GpggaDecode(PackageGnss* pa,GnssRec *gr)
=======
TpUchar GpggaDecode(Package* pa,GnssRec *gr)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
{
  TpUchar u8DataSum =0;
  TpUint16 i=0;
  TpUint16 u16TempStrLeng = 0;

  if(!CheckSumNmea(pa->data_ptr,pa->buff_len))
  {
    return NONE_IN;
  }
  for(i=7;i<pa->buff_len-2;i++)
  {
    if(!((pa->data_ptr[i]==44)||(pa->data_ptr[i]==42)))  //,
    {
      TempStr[u16TempStrLeng]=pa->data_ptr[i];
      u16TempStrLeng++;
    }
    else
    {
      u8DataSum++;
      switch(u8DataSum)
      {
      case 1:
        gr->nmea.gpgga.time_utc = strtod(TempStr,0);  //UTC time
        break;
      case 2:
        gr->nmea.gpgga.lat  = Ddmm2dd(strtod(TempStr,0));
        break;
      case 3:
        if(TempStr[0]=='S')
        {
          gr->nmea.gpgga.lat=gr->nmea.gpgga.lat*(-1.0);
        }
        break;
      case 4:
        gr->nmea.gpgga.lon = Ddmm2dd(strtod(TempStr,0));
        break;
      case 5:
        if(TempStr[0]=='W')
        {
          gr->nmea.gpgga.lon = gr->nmea.gpgga.lon*(-1.0);
        }
        break;
      case 6:
        gr->nmea.gpgga.gps_state  = atoi(TempStr);
<<<<<<< HEAD
     //   if(atoi(TempStr)>0)
=======
        if(atoi(TempStr)>0)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
        {       
           gr->nmea.gpgga.data_flag =1;
        }       
        if(gr->nmea.gpgga.data_flag&&!pps_start)
        {
           fix_cnt++;
          if(5==fix_cnt)
          {
            pps_start = 1;
          }
        }
        if(atoi(TempStr)==6)
        {
           gr->nmea.gpgga.data_flag =0;
        }
        if((atoi(TempStr)==4)||(atoi(TempStr)==5))
        {
          gr->nmea.gpgga.rtk_flag =1;
        }
        else
        {
          gr->nmea.gpgga.rtk_flag =0;
        }
        break;
      case 7:
        gr->nmea.gpgga.sat_num =atoi(TempStr);
        if(gr->nmea.gpgga.sat_num<4)
        {
          gr->nmea.gpgga.data_flag =0;
          gr->nmea.gpgga.rtk_flag =0;
        }
        break;
      case 8:
        gr->nmea.gpgga.hdop = atof(TempStr);
        break;
      case 9:
        gr->nmea.gpgga.alt = atof(TempStr); /*  alt */
        break;
      case 10:
        break;
      case 11:
        /* Undulation - the relationship between the geoid and the WGS84 ellipsoid */
        gr->nmea.gpgga.altref =	atof(TempStr);
        gr->nmea.gpgga.alt += gr->nmea.gpgga.altref;
        break;
      case 12:
        break;
      case 13:
        /* age Age of Differential GPS data (in seconds) */
        gr->nmea.gpgga.diff_time = atoi(TempStr);
        break;
      case 14:
        /* stn ID Differential base station ID, 0000-1023 */
        gr->nmea.gpgga.diff_id = atoi(TempStr);
        break;
      }
      u16TempStrLeng =0;
      memset(TempStr,0,20);
    }
  }

	return GPGGA_IN;
}

static TpUchar CheckSumNmea(const TpUchar *buf,const TpUint16 count)
{
  TpUint16 i;
  TpUchar u8Sum=0;
  for(i=1;i<count-5;i++)
  {
    u8Sum ^= buf[i];
  }
  if(u8Sum==(Asc2Uchar(buf[count-4])*16+Asc2Uchar(buf[count-3])))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

TpUchar Asc2Uchar(TpUchar data)
{
  TpUchar  u8Temp=0;
  if((data>0x2f)&&((data<0x3a)))
  u8Temp = data - 0x30;
  if((data>0x40)&&((data<0x47)))
    u8Temp = data - 55;
  if((data>0x60)&&((data<0x67)))
    u8Temp = data - 87;
  return  u8Temp;
}


TpDouble Ddmm2dd(TpDouble ddmm) /////
{
  int tt =0;
  TpDouble d_in =0.0;
  TpDouble dd_out =0.0;
  tt = (int)(ddmm/100.0);
  d_in = ((ddmm/100 -tt)*100)/60;
  dd_out = tt + d_in;
  return dd_out;
}


<<<<<<< HEAD
TpUchar GprmcDecode(PackageGnss* pa,GnssRec *gr)
=======
TpUchar GprmcDecode(Package* pa,GnssRec *gr)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
{
	TpUchar datenum =0;
	TpUint16 i=0;
	TpChar TempStr[20] = {0};
	TpUint16 TempStrLeng = 0;

	if(!CheckSumNmea(pa->data_ptr,pa->buff_len))
	{
		return NONE_IN;
	}
	for(i=7;i<pa->buff_len-2;i++)
	{
		if(!((pa->data_ptr[i]==44)||(pa->data_ptr[i]==42)))  //,
		{
			TempStr[TempStrLeng]=pa->data_ptr[i];
			TempStrLeng++;
		}
		else
		{
			datenum++;
			switch(datenum)
			{
			case 1:
				gr->nmea.gprmc.time_utc = strtod(TempStr,0);  //UTC time

				break;
			case 2:
				if(TempStr[0]=='A')
        {
					gr->nmea.gprmc.data_valid = 1;
        }
				else if(TempStr[0]=='V')
        {
					gr->nmea.gprmc.data_valid = 0;
        }
				break;
			case 3:
				gr->nmea.gprmc.lat  = Ddmm2dd(strtod(TempStr,0));
				break;
			case 4:
				if(TempStr[0]=='S')
        {
          gr->nmea.gprmc.lat= gr->nmea.gprmc.lat*(-1.0);
        }
				break;
			case 5:
				gr->nmea.gprmc.lon = Ddmm2dd(strtod(TempStr,0));
				break;
			case 6:
				if(TempStr[0]=='W')
        {
          gr->nmea.gprmc.lon = gr->nmea.gprmc.lon*(-1.0);
        }
				break;
			case 7:
				 gr->nmea.gprmc.vg =  atof(TempStr)*MILE2KM;
				break;
			case 8:
			   gr->nmea.gprmc.heading = atof(TempStr);
				break;
			case 9:
			   gr->nmea.gprmc.date = atof(TempStr);
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			}
			TempStrLeng =0;
			memset(TempStr,0,20);
		}
	}
	return GPRMC_IN;
}

<<<<<<< HEAD
TpUchar GphdtDecode(PackageGnss* pa,GnssRec *gr)
=======
TpUchar GphdtDecode(Package* pa,GnssRec *gr)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
{
  TpUchar datenum =0;
  TpUint16 i=0;
  TpChar TempStr[20] = {0};
  TpUint16 TempStrLeng = 0;

  if(!CheckSumNmea(pa->data_ptr,pa->buff_len))
  {
    return NONE_IN;
  }
  for(i=7;i<pa->buff_len-2;i++)
  {
    if(!((pa->data_ptr[i]==44)||(pa->data_ptr[i]==42)))
    {
      TempStr[TempStrLeng]=pa->data_ptr[i];
      TempStrLeng++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
      case 1:
<<<<<<< HEAD
//        gr->nmea.gphdt.orient = atof(TempStr);
=======
        gr->nmea.gphdt.orient = atof(TempStr);
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
        break;
      case 2:
        gr->nmea.gphdt.true_flag = TempStr[0];
        break;
      case 3:
        break;
      }
      TempStrLeng =0;
      memset(TempStr,0,20);
    }
  }
	return GPHDT_IN;
}


<<<<<<< HEAD
static TpUchar BestVelDec(PackageGnss* pa,GnssRec *pstGnssIn)
=======
static TpUchar BestVelDec(Package* pa,GnssRec *pstGnssIn)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
{
  TpChar datenum =0;
  int i=0;
  int t=0;
  int TempStrLeng = 0;
  TpUchar str_len = 0;

  if(!CheckSumNovatel(pa->data_ptr,pa->buff_len))
  {
    return NONE_IN;
  }
  memset(TempStr,0,20);
  for(i=10;i<pa->buff_len-2;i++)
  {
    if(!((pa->data_ptr[i]==0x2A)||(pa->data_ptr[i]==0x2C)||(pa->data_ptr[i]==0x3B)))  //,
    {
      TempStr[TempStrLeng]=pa->data_ptr[i];
      TempStrLeng++;
      str_len++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
        case 1:/* port */
        {

          memcpy(&pstGnssIn->bestvela.loghead.port,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 2:
        {
          memcpy(&pstGnssIn->bestvela.loghead.seq,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 3:
        {
          memcpy(&pstGnssIn->bestvela.loghead.idle_time,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 4:
        {
          memcpy(&pstGnssIn->bestvela.loghead.time_status,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 5:
          pstGnssIn->bestvela.loghead.week = atof(TempStr);
          str_len = 0;
        break;/* GPS Time */
        case 6:
          pstGnssIn->bestvela.loghead.time_gps =  strtod(TempStr,0);
        str_len = 0;
        break;
        case 7:
        {
          memcpy(&pstGnssIn->bestvela.loghead.rec_status,TempStr,str_len);
          str_len = 0;
        }
          break;
        case 8:
        {
          memcpy(&pstGnssIn->bestvela.loghead.resv,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 9:
        {
          memcpy(&pstGnssIn->bestvela.loghead.version,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 10:
        {
           memcpy(&pstGnssIn->bestvela.sol_status,TempStr,str_len);
           str_len = 0;
        }break;
        case 11:  /*sol status */
        {
          if(!memcmp("NONE",TempStr,4))
          {
            pstGnssIn->bestvela.pv_type=0;
          }
          else if(!memcmp("PROPAGATED",TempStr,10))
          {
            pstGnssIn->bestvela.pv_type=0;
          }
          else
          {
            pstGnssIn->bestvela.pv_type=1;
            pstGnssIn->bestvela.vdata_flag =1;
          }

          memcpy(&pstGnssIn->bestvela.vel_type,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 12:
        {
          memcpy(&pstGnssIn->bestvela.latency,TempStr,str_len);
          str_len = 0;
        }
        break;
        case 13:
        {
          memcpy(&pstGnssIn->bestvela.age,TempStr,str_len);
          str_len = 0;
        }break;
        case 14:
        {
          pstGnssIn->bestvela.vg  = (float)atof(TempStr);
          str_len = 0;
        }
        break;
        case 15:
        {
          pstGnssIn->bestvela.track = (float)atof(TempStr);
          pstGnssIn->bestvela.ve = (float)sin(pstGnssIn->bestvela.track*D2R)*pstGnssIn->bestvela.vg;
          pstGnssIn->bestvela.vn = (float)cos(pstGnssIn->bestvela.track*D2R)*pstGnssIn->bestvela.vg;
          str_len = 0;
        }
        break;
        case 16:
        {
          pstGnssIn->bestvela.vu =  (float)atof(TempStr);
          str_len = 0;
        }
        break;
        case 17:
        {
          memcpy(&pstGnssIn->bestvela.loghead.resv,TempStr,str_len);
          str_len = 0;
        }
        break;
      }
      for(t=0;t<40;t++)
      {
         TempStr[t] =0x00;
      }
      TempStrLeng =0;
      memset(TempStr,0,40);
    }
  }
  if(pstGnssIn->bestvela.pv_type==1)
  {
    pstGnssIn->bestvela.vdata_flag =1;
  }
  return BESTVELA_IN;
}

<<<<<<< HEAD
static TpUchar HeadingaDec(PackageGnss* pa,GnssRec *gr)
=======
static TpUchar HeadingaDec(Package* pa,GnssRec *gr)
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
{
  TpChar datenum =0;
  int i=0;
  TpChar TempStr[40];
  int TempStrLeng = 0;
  TpUchar str_len = 0;

  if(!CheckSumNovatel(pa->data_ptr,pa->buff_len))
  {
    return NONE_IN;
  }

  memset(TempStr,0,20);
  for(i=10;i<pa->buff_len-2;i++)
  {

    if(!((pa->data_ptr[i]==0x2A)||(pa->data_ptr[i]==0x2C)||(pa->data_ptr[i]==0x3B)))  //,
    {
      TempStr[TempStrLeng]=pa->data_ptr[i];
      TempStrLeng++;
      str_len++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
      case 1:
      {
        memcpy(&gr->headinga.loghead.port,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 2:
      {
        memcpy(&gr->headinga.loghead.seq,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 3:
      {
        memcpy(&gr->headinga.loghead.idle_time,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 4:
      {
        memcpy(&gr->headinga.loghead.time_status,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 5:
      {
        gr->headinga.loghead.week = atof(TempStr);
        str_len = 0;
      }
      break;
      case 6:
      {
        gr->headinga.loghead.time_gps =  atof(TempStr);
        str_len = 0;
      }
      break;
      case 7:
      {
        memcpy(&gr->headinga.loghead.rec_status,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 8:
      {
        memcpy(&gr->headinga.loghead.resv,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 9:
      {
        memcpy(&gr->headinga.loghead.version,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 10:
      {
        gr->headinga.sol_st = (TpUint32)SolStatus(TempStr,TempStrLeng);
        memcpy(&gr->headinga.sol_sta,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 11:
      {
        gr->headinga.pv_type =PvType(TempStr,TempStrLeng);
        memcpy(&gr->headinga.pos_type,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 12:
      {
        gr->headinga.bs = atof(TempStr);
        memcpy(&gr->headinga.baseline,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 13:
      {
        gr->headinga.heading = atof(TempStr);
        str_len = 0;
      }
      break;
      case 14:
      {
        gr->headinga.pitch = atof(TempStr);
        str_len = 0;
      }
      break;
      case 15:
      {
        str_len = 0;
      }
      break;
      case 16:
      {
        gr->headinga.heading_std =  atof(TempStr);
        str_len = 0;
      }
      break;
      case 17:
      {
        gr->headinga.pitch_std =  atof(TempStr);
        str_len = 0;
      }
      break;
      case 18:
      {
        memcpy(&gr->headinga.stn_id,TempStr,str_len);
        str_len = 0;
      }
      break;
      case 19:
        gr->headinga.svs =  atof(TempStr);
      break;
      case 20:
        gr->headinga.sol_svs =  atof(TempStr);
      break;
      case 21:
        gr->headinga.obs =  atof(TempStr);
      break;
      case 22:
        gr->headinga.multi =  atof(TempStr);
      break;
      case 23:
      {
        gr->headinga.sol_source =  atof(TempStr);
      }
      break;
      case 24:
        gr->headinga.extsol = (TpUchar)atoi(TempStr);
      break;
      case 25:
      {
        gr->headinga.sigmask1 = (TpUchar)atoi(TempStr);
      }
      break;
      case 26:
      {
        gr->headinga.sigmask2 = (TpUchar)atoi(TempStr);
      }
      break;
    }
      TempStrLeng =0;
      memset(TempStr,0,40);
   }
 }

	return HEADINGA_IN;
}

TpInt32  Hhmmss2ss(TpDouble data)
{
  TpUint32 ddmm;
  int hh = 0;
  int mm = 0;
  TpUint32 ss = 0;

  ddmm = (TpUint32)((data+0.05)*10);
  ddmm  = ddmm*100;

  hh = (int)(ddmm/10000000);
  mm = (ddmm-hh*10000000)/100000;
  ss = ddmm-hh*10000000.0-mm*100000.0;
  ss = hh*3600000+mm*60000+ss;

  return ss;
 }
static TpUint16 Date2Week(TpFloat time,TpInt32 date)
{
  TpUint16 week = 0;
  TpUchar u8Month=0,u8Day=0,hour=0,minute=0,second=0;
  TpUint16 u16Year=0;
  float UT;
  int Y, M;
  TpDouble JD;
  TpUint32 u32Time;

  u32Time = (TpUint32)time;

  u8Day= date*0.0001f;
  u8Month = (date-u8Day*10000)*0.01f;
  u16Year = date-u8Day*10000-u8Month*100;
  u16Year +=2000;

  hour = (float)u32Time*0.0001f;
  minute = (float)(u32Time-hour*10000)*0.01f;
  second = u32Time-hour*10000-minute*100;

  hour+=8;

  UT = (float)hour + (float)minute/60 + (float)second/3600;
  if (u8Month<= 2)
  {
    Y = u16Year - 1;
    M = u8Month + 12;
  }
  else
  {
    Y = u16Year;
    M = u8Month;
  }

  JD = (TpDouble)Y*365.25+(30.6001 * (M + 1))+u8Day+UT/24+1720981.5;

  week = (TpUint16)((JD - 2444244.5) / 7);

  return week;
}

TpUchar ReturnDay(TpInt32 date)
{
  TpUchar result = 0;
  TpUint16 u16Year,u16Month,u16Day;
  TpUint16 y = 0, c = 0, m = 0, d = 0;

  u16Day= date*0.0001f;
  u16Month = (date-u16Day*10000)*0.01f;
  u16Year = date-u16Day*10000-u16Month*100;
  u16Year +=2000;

  if ( u16Month == 1 || u16Month == 2 )
  {
      c = ( u16Year - 1 ) / 100;
      y = ( u16Year - 1 ) % 100;
      m = u16Month + 12;
      d = u16Day;
  }
  else
  {
      c = u16Year / 100;
      y = u16Year % 100;
      m = u16Month;
      d = u16Day;
  }

  result = y + y / 4 + c / 4 - 2 * c + 26 * ( m + 1 ) / 10 + d - 1;
  result = result >= 0 ? ( result % 7 ) : ( result % 7 + 7 );
  if ( result == 0 )
  {
    result = 7;
  }
  return result;
}

static  TpChar CheckSumNovatel(TpUchar *buf,TpInt32 count)
{
  TpUchar Check_sum_char[8];
  TpUint32 sum_u32=0;
  memcpy(Check_sum_char,buf+count-10,8);
  sum_u32= Asc2Int(Check_sum_char);

  if(sum_u32==CalculateBlockCRC32(count-12,buf+1))
    return 1;
  else
    return 0;
}
TpInt32 Asc2Int(TpUchar* buf)
{
  unsigned int asc_0=0;
  asc_0 = ((unsigned int)Asc2Uchar(buf[0]))*16 + Asc2Uchar(buf[1]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)Asc2Uchar(buf[2]))*16 + Asc2Uchar(buf[3]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)Asc2Uchar(buf[4]))*16 + Asc2Uchar(buf[5]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)Asc2Uchar(buf[6]))*16 + Asc2Uchar(buf[7]);
  return asc_0;
}

TpInt32 CalculateBlockCRC32(TpInt32 count,TpUchar* buf ) /* Data block */
{
  TpUint32 ulTemp1;
  TpUint32 ulTemp2;
  TpUint32 ulCRC = 0;
  while ( count-- != 0 )
  {	ulTemp1 = ( ulCRC >> 8 ) & 0x00FFFFFFL;
    ulTemp2 = CRC32Value( ((int) ulCRC ^ *buf++ ) & 0xff );
    ulCRC = ulTemp1 ^ ulTemp2;
  }
  return( ulCRC );
}

TpInt32 CRC32Value(TpInt32 i)
{
  TpInt32 j;
  TpUint32 ulCRC;
  ulCRC = i;
  for(j=8;j>0;j--)
  {
    if(ulCRC&1)
    ulCRC=(ulCRC>>1)^CRC32_POLYNOMIAL;
    else
    ulCRC>>=1;
  }
  return ulCRC;
}

static TpChar PvType(TpChar* buf,TpUint32 len)
{
  if(!memcmp("NONE",buf,4))
  {
    return 0;					//No solution
  }
  else if(!memcmp("FIXEDPOS",buf,8))
  {
    return 1; 				//Position has been fixed by the FIX POSITION command
  }
  else if(!memcmp("FIXEDHEIGHT",buf,11))
  {
    return 2;				 //Position has been fixed by the FIX HEIGHT/AUTO command
  }
  else if(!memcmp("DOPPLER_VELOCITY",buf,16))
  {
    return 8;				 //	Velocity computed using instantaneous Doppler
  }
  else if(!memcmp("SINGLE",buf,6))
  {
    return 16; 				//Single point position
  }
  else if(!memcmp("PSRDIFF",buf,7))
  {
    return 17;				 //Pseudorange differential solution
  }
  else if(!memcmp("WAAS",buf,4))
  {
    return 18;				 //Solution calculated using corrections from an SBAS
  }
  else if(!memcmp("PROPAGATED",buf,10))
  {
    return 19;				 //Propagated by a Kalman filter without new observations
  }
  else if(!memcmp("OMNISTAR",buf,8))
  {
    return 20; 				//OmniSTAR VBS position (L1 sub-meter)
  }
  else if(!memcmp("L1_FLOAT",buf,8))
  {
    return 32;				//Floating L1 ambiguity solution
  }
  else if(!memcmp("IONOFREE_FLOAT",buf,14))
  {
    return 33;				//Floating ionospheric-free ambiguity solution
  }
  else if(!memcmp("NARROW_FLOAT",buf,12))
  {
    return 34;				//Floating narrow-lane ambiguity solution
  }
  else if(!memcmp("L1_INT",buf,6))
  {
    return 48; 				//Integer L1 ambiguity solution
  }
  else if(!memcmp("WIDE_INT",buf,7))
  {
    return 49;				//Integer wide-lane ambiguity solution
  }
  else if(!memcmp("NARROW_INT",buf,10))
  {
    return 50;				//Integer narrow-lane ambiguity solution
  }
  else if(!memcmp("CDGPS",buf,5))
  {
    return 66;				//Position solution using CDGPS correction
  }
  else
  {
    return 0;
  }

}

static TpChar SolStatus(TpChar* buf,TpUint32 len)
{
  if(!memcmp("SOL_COMPUTED"	,	buf,12))		return 0;
  else if(!memcmp("INSUFFICIENT_OBS"	,	buf,16))		return 1;
  else if(!memcmp("NO_CONVERGENCE"	,	buf,14))		return 2;
  else if(!memcmp("SINGULARITY"	,	buf,11))			return 3;
  else if(!memcmp("COV_TRACE"	,	buf,9))				return 4;
  else if(!memcmp("TEST_DIST"	,	buf,9))				return 5;
  else if(!memcmp("COLD_START",	buf,10))			return 6;
  else if(!memcmp("V_H_LIMIT"	,	buf,9))				return 7;
  else if(!memcmp("VARIANCE"	,	buf,8))				return 8;
  else if(!memcmp("RESIDUALS"	,	buf,9))				return 9;
  else if(!memcmp("DELTA_POS"	,	buf,9))				return 10;
  else if(!memcmp("NEGATIVE_VAR"	,buf,12))		return 11;
  else if(!memcmp("INTEGRITY_WARNING"	,	buf,17))		return 13;
  else if(!memcmp("PENDING"	,	buf,7))							return 18;
  else if(!memcmp("INVALID_FIX"	,	buf	,	11))			return 19;
  else if(!memcmp("UNAUTHORIZED",	buf	,	12))		return 20;
  else if(!memcmp("ANTENNA_WARNING",	buf	,	15))	return 21;
  else return 0;
}

TpVoid GnssCombine(GnssOut *gno,GnssRec *gr)
{
  TpUint32 u32Time;
  TpUchar day;

  gno->head = 0x23AB;

#ifdef NMEA_ON
    if((gr->flag&GPGGA_FLAG)&&(gr->flag&GPRMC_FLAG))
    {
      gr->nmea.flag=0;
      memset(gno,0,sizeof(gnssout));
   
      gno->head = 0x23AB;
      gno->week = Date2Week(gr->nmea.gprmc.time_utc,gr->nmea.gprmc.date);
      day = ReturnDay(gr->nmea.gprmc.date);

      
      old_time = new_time;
      
      if(7==day)
      {
         gno->time_utc = Hhmmss2ss(gr->nmea.gpgga.time_utc)+UTC2GPS;
      }
      else
      {
         gno->time_utc = Hhmmss2ss(gr->nmea.gpgga.time_utc)+day*DAY_NIGHT_MS + UTC2GPS;
      }

      new_time = gno->time_utc;
      diff_time = gno->time_utc - old_time;
      
      gno->lat = gr->nmea.gpgga.lat;
      gno->lon = gr->nmea.gpgga.lon;
      gno->alt = gr->nmea.gpgga.alt;
      gno->heading =  gr->nmea.gprmc.heading;
      gno->vg = gr->nmea.gprmc.vg;
      gno->hdop = (TpUint16)(gr->nmea.gpgga.hdop*HDOP_FAC);

      if(gr->nmea.gpgga.gps_state>0&&gr->nmea.gprmc.data_valid==1) /* pos and vel valid */
      {
        gno->flag|=GNSS_FIX_PV;
      }
      if(gr->nmea.gpgga.gps_state==1)
      {
        gno->flag|=GNSS_FIX_SPS;
      }
      if(gr->nmea.gpgga.gps_state==2)
      {
        gno->flag|=GNSS_FIX_DGPS;
      }
      if(gr->nmea.gpgga.gps_state==5)
      {
        gno->flag|=GNSS_FIX_FLOAT;
      }
      if(gr->nmea.gpgga.gps_state==4)
      {
        gno->flag|=GNSS_FIX_RTK;
      }
      
<<<<<<< HEAD
     
      gno->flag|=GNSS_FIX_DATA;
		  memset(&gr,0,sizeof(gr));
      
//      memset(data_to_arm2,0,sizeof(data_to_arm2));
//      memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
//      
//      gnssout.check = CheckSumByte(data_to_arm2,sizeof(gnssout)-1);
//      
//      memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
			
			gnssout.check = CheckSumByte((TpUchar*)&gnssout,sizeof(gnssout));
         
=======
      /*  add for satcom  */
			#ifdef UMI_SATCOM_FORMAT
      if(satComYawFlag.init_ok)
			{
			    satComYawFlag.init_ok = 0;
				  gno->flag|=GNSS_FIX_YAW_INIT;
				  gno->flag|=GNSS_FIX_ORT;
				  gno->orient = satComYawInit.yaw*ATT_INIT_FACTOR_MIN;
				  gno->orient_q = satComYawInit.yaw_q*ATT_INIT_FACTOR_MIN;
		  }
			if(satComYawFlag.update_ok)
			{
			    satComYawFlag.update_ok = 0;
				  gno->flag|=GNSS_FIX_YAW_UPDATE;
				  gno->flag|=GNSS_FIX_ORT;
				  gno->orient = satComYawUpdate.yaw*ATT_UP_FACTOR_MIN;
			    gno->orient_q = satComYawUpdate.yaw_q*ATT_UP_FACTOR_MIN;
		  }
			#endif
						
      gno->flag|=GNSS_FIX_DATA;
		  memset(&gr,0,sizeof(gr));
      
      memset(data_to_arm2,0,sizeof(data_to_arm2));
      memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
      
      gnssout.check = CheckSumByte(data_to_arm2,sizeof(gnssout)-1);
      
      memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
     
      UsartPushSendBuf(&usart6,data_to_arm2,sizeof(gnssout),0);
//      UsartSend(&usart6,sizeof(gnssout));
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
}
#endif
 if((gr->flag&GPGGA_FLAG)&&(gr->flag&BESTVELA_FLAG))
	{
    gno->week = gr->bestvela.loghead.week;

    u32Time = (TpUint32)((gr->bestvela.loghead.time_gps+0.05)*10);
    gno->time_utc  = u32Time*100;

    gno->lat =  gr->nmea.gpgga.lat;
    gno->lon =  gr->nmea.gpgga.lon;
    gno->alt =  gr->nmea.gpgga.alt;
    gno->vg = gr->bestvela.vg;
    gno->heading = gr->bestvela.track;
    gno->hdop = (TpUint16)(gr->nmea.gpgga.hdop*100.0f);

    if((gr->nmea.gpgga.gps_state)>0&&(1==gr->bestvela.vdata_flag))
    {
      gno->flag|=GNSS_FIX_PV;
     }
		/* single point */
    if(gr->nmea.gpgga.gps_state==1)
    {
      gno->flag|=GNSS_FIX_SPS;
    }
		/* differential */
    if(gr->nmea.gpgga.gps_state==2)
    {
      gno->flag|=GNSS_FIX_DGPS;
    }
		/*  float */
    if(gr->nmea.gpgga.gps_state==5)
    {
      gno->flag|=GNSS_FIX_FLOAT;
    }
		/* fixed */
    if(gr->nmea.gpgga.gps_state==4)
    {
      gno->flag|=GNSS_FIX_RTK;
    }
    gno->flag|=GNSS_FIX_DATA;
	}

  if(gr->flag&HEADINGA_FLAG)
  {
    gno->orient = gr->headinga.heading;
    if((48==gr->headinga.pv_type)||(50==gr->headinga.pv_type))
    {
      gno->flag|=GNSS_FIX_PV;
     }
  }
}
<<<<<<< HEAD
=======


TpUchar CheckSumByte(TpUchar* buf ,int length)
{
  TpUint16 sum = 0;
  TpUchar i;
  TpUchar sum_low;

  for(i=2;i<length-1;i++)
  {
    sum+=buf[i];
  }

  sum_low = sum&0x00ff;
  return sum_low;
}

#ifdef UMI_SATCOM_FORMAT
TpVoid SatComYawCombain(GnssOut *gno,SatComYawFlag *sy)
{

	 memset(gno,0,sizeof(gnssout));
   gno->head = 0x23AB;
	 if(satComYawFlag.init_ok)
		{
			satComYawFlag.init_ok = 0;
			gno->flag|=GNSS_FIX_YAW_INIT;
			gno->flag|=GNSS_FIX_ORT;
			gno->orient = satComYawInit.yaw*ATT_INIT_FACTOR_MIN;
			gno->orient_q = satComYawInit.yaw_q*ATT_INIT_FACTOR_MIN;
		}
		if(satComYawFlag.update_ok)
		{
			satComYawFlag.update_ok = 0;
			gno->flag|=GNSS_FIX_YAW_UPDATE;
			gno->flag|=GNSS_FIX_ORT;
			gno->orient = satComYawUpdate.yaw*ATT_UP_FACTOR_MIN;
			gno->orient_q = satComYawUpdate.yaw_q*ATT_UP_FACTOR_MIN;
		}
		
		memset(data_to_arm2,0,sizeof(data_to_arm2));
		memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
		
		gnssout.check = CheckSumByte(data_to_arm2,sizeof(gnssout)-1);
		
		memcpy(data_to_arm2,&gnssout,sizeof(gnssout));
	 
		UsartPushSendBuf(&usart6,data_to_arm2,sizeof(gnssout),0);
//		UsartSend(&usart6,sizeof(gnssout));

}
#endif
>>>>>>> b124b37e61948a38cca92d9a4f8f9a4cc8294dd6
