/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   gnss.c                                                      */
/* Date:        2016.5.18                                                     */
/* Description: gnss.c                                                       */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "gnss.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

stGnssOut m_stGnssOut;
stPackage m_stPackage;
stNMEA m_stNMEA;
stGnssIn m_stGnssIn;
stGnssIn m_stGnssModify;
stUtcData m_stUtcData;
stHeadinga m_stHeadingaSave;

double dTime;
uint8_t u8Day;
uint8_t u8DayCalc = 0;
char TempStr[50];
static uint16_t u16AsciiNum_Gpgga = 0,u16AsciiNum_Bestvela = 0, u16AsciiNum_Headinga = 0;
double dd=0.0;
double mm=0.0;
uint32_t dtemp;
uint8_t u8StrLen = 0;
uint32_t u32Time1,u32Time2;
char str_Temp[20] = {0};
uint32_t u32CRC = 0;
uint8_t u8CheckNmea = 0;

uint8_t u8DataSendARM2[100];   /* send data to arm2 */

/*============================================================================*/
/*                            Function definition                             */
/*============================================================================*/

/*****************************************************************************
* function name:  HW_Configuration
* description:    config systick,TIM and GPIO
* input:          none
* output:         none
******************************************************************************/

void Init_Package(stPackage *pstPackage)
{
  pstPackage->u16Num_Package=0;
  pstPackage->u8Start_Package=0;
  pstPackage->u16Pointer=0;
  memset(pstPackage->u8Vec_Package,0,_PACKAGESIZE);
}

void Package_Rec(uint8_t *pBuffer,uint16_t u16Num)
{
  uint16_t i=0;
  uint8_t u8Byte;
  for(i=0;i<u16Num;i++)
  {
    u8Byte = pBuffer[i];
    switch(u8Byte)
    {
      case '$':
      case '#':
      {
        m_stPackage.u8Start_Package = 1;
        m_stPackage.u8Vec_Package[0] = u8Byte;
        m_stPackage.u16Pointer = 1;
        m_stPackage.u16Num_Package=0;


      }
      break;
      case 0x0A:
      {
        if(m_stPackage.u8Start_Package)
        {
          m_stPackage.u8Start_Package = 0;
          m_stPackage.u16Pointer+=1;
          m_stPackage.u8Vec_Package[m_stPackage.u16Pointer] = u8Byte;
          m_stPackage.u16Num_Package=m_stPackage.u16Pointer;

          GNSS_Decode(&m_stPackage,&m_stGnssIn);
       

       }

      }
      default:
      {
        if(m_stPackage.u8Start_Package)
        {
           m_stPackage.u8Vec_Package[m_stPackage.u16Pointer] = u8Byte;
           m_stPackage.u16Pointer+=1;
        }
      }
    }
  }
}

static void GNSS_Decode(stPackage* pstPackage,stGnssIn *pstGNSSIn)
{
  uint8_t u8Result;

 // if(!memcmp("$GPGGA,",pstPackage->u8Vec_Package,7))
  if(!memcmp("$GNGGA,",pstPackage->u8Vec_Package,7))
  {
    if(_GPGGA==Decode_Gpgga(pstPackage,pstGNSSIn))
    {
      pstGNSSIn->u16Flag |= GPS_GPGGA_IN;
    }
  }
//	else if(!memcmp("$GPRMC,",pstPackage->u8Vec_Package,7))
   else if(!memcmp("$GNRMC,",pstPackage->u8Vec_Package,7))
	{
		if(_GPRMC==Decode_Gprmc(pstPackage,pstGNSSIn))
		{
			pstGNSSIn->u16Flag |= GPS_GPRMC_IN;
		}
	}
  else if(!memcmp("$GPHDT,",pstPackage->u8Vec_Package,7))
	{
		if(_GPHDT==Decode_Gphdt(pstPackage,pstGNSSIn))
		{
			pstGNSSIn->u16Flag |= GPS_GPHDT_IN;
		}
	}
  else if(!memcmp("#BESTVELA,",pstPackage->u8Vec_Package,10))
	{
    u8Result = Decode_BestVela(pstPackage,pstGNSSIn);
    if(_BESTVELA==u8Result)
    {
      pstGNSSIn->u16Flag |= GPS_BESTVELA_IN;
    }
	}
  else if(!memcmp("#HEADINGA,",pstPackage->u8Vec_Package,10))
	{
    u8Result = Decode_Headinga(pstPackage,pstGNSSIn);
    if(_HEADINGA==u8Result)
    {
      pstGNSSIn->u16Flag |= GPS_HEADINGA_IN;
    }
	}
}

static uint8_t Decode_Gpgga(stPackage* pstPackage,stGnssIn *pstGNSSIn)
{
  uint8_t u8DataSum =0;
  uint16_t i=0;
  uint16_t u16TempStrLeng = 0;

  if(!CheckSum_NMEA(pstPackage->u8Vec_Package,pstPackage->u16Num_Package))
  {
    return _NONE;
  }
  for(i=7;i<pstPackage->u16Num_Package-2;i++)
  {
    if(!((pstPackage->u8Vec_Package[i]==44)||(pstPackage->u8Vec_Package[i]==42)))  //,
    {
      TempStr[u16TempStrLeng]=pstPackage->u8Vec_Package[i];
      u16TempStrLeng++;
    }
    else
    {
      u8DataSum++;
      switch(u8DataSum)
      {
      case 1:
        pstGNSSIn->m_stNMEA.m_stGpgga.dUtcTime = strtod(TempStr,0);  //UTC time
        break;
      case 2:
        pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude  = Ddmm2dd(strtod(TempStr,0));
        break;
      case 3:
        if(TempStr[0]=='S')
        {
          pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude=pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude*(-1.0);
        }
        break;
      case 4:
        pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude = Ddmm2dd(strtod(TempStr,0));
        break;
      case 5:
        if(TempStr[0]=='W')
        {
          pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude*(-1.0);
        }
        break;
      case 6:
        pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State  = atoi(TempStr);
        if(atoi(TempStr)>0)
        {
           pstGNSSIn->m_stNMEA.m_stGpgga.u8GpggaDataFlag =1;
        }
        if(atoi(TempStr)==6)
        {
           pstGNSSIn->m_stNMEA.m_stGpgga.u8GpggaDataFlag =0;
        }
        if((atoi(TempStr)==4)||(atoi(TempStr)==5))
        {
          pstGNSSIn->m_stNMEA.m_stGpgga.u8RtkFlag =1;
        }
        else
        {
          pstGNSSIn->m_stNMEA.m_stGpgga.u8RtkFlag =0;
        }
        break;
      case 7:
        pstGNSSIn->m_stNMEA.m_stGpgga.Num_Satellites =atoi(TempStr);
        if(pstGNSSIn->m_stNMEA.m_stGpgga.Num_Satellites<4)
        {
          pstGNSSIn->m_stNMEA.m_stGpgga.u8GpggaDataFlag =0;
          pstGNSSIn->m_stNMEA.m_stGpgga.u8RtkFlag =0;
        }
        break;
      case 8:
        pstGNSSIn->m_stNMEA.m_stGpgga.fHdop = atof(TempStr);
        break;
      case 9:
        pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude = atof(TempStr); /*  alt */
        break;
      case 10:
        break;
      case 11:
        /* Undulation - the relationship between the geoid and the WGS84 ellipsoid */
        pstGNSSIn->m_stNMEA.m_stGpgga.fAltref =	atof(TempStr);
        pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude += pstGNSSIn->m_stNMEA.m_stGpgga.fAltref;
        break;
      case 12:
        break;
      case 13:
        /* age Age of Differential GPS data (in seconds) */
        pstGNSSIn->m_stNMEA.m_stGpgga.u32DiffTime = atoi(TempStr);
        break;
      case 14:
        /* stn ID Differential base station ID, 0000-1023 */
        pstGNSSIn->m_stNMEA.m_stGpgga.u16DiffId = atoi(TempStr);
        break;
      }
      u16TempStrLeng =0;
      memset(TempStr,0,20);
    }
  }
	return _GPGGA;
}

static uint8_t CheckSum_NMEA(const uint8_t *u8Buffer,const uint16_t u16Count)
{
  uint16_t i;
  uint8_t u8Sum=0;
  for(i=1;i<u16Count-5;i++)
  {
    u8Sum ^= u8Buffer[i];
  }
  if(u8Sum==(ASCII2u8(u8Buffer[u16Count-4])*16+ASCII2u8(u8Buffer[u16Count-3])))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

uint8_t ASCII2u8(uint8_t u8Data)
{
  uint8_t  u8Temp=0;
  if((u8Data>0x2f)&&((u8Data<0x3a)))
  u8Temp = u8Data - 0x30;
  if((u8Data>0x40)&&((u8Data<0x47)))
    u8Temp = u8Data - 55;
  if((u8Data>0x60)&&((u8Data<0x67)))
    u8Temp = u8Data - 87;
  return  u8Temp;
}


double Ddmm2dd(double ddmm) /////
{
  int tt =0;
  double d_in =0.0;
  double dd_out =0.0;
  tt = (int)(ddmm/100.0);
  d_in = ((ddmm/100 -tt)*100)/60;
  dd_out = tt + d_in;
  return dd_out;
}


static uint8_t Decode_Gprmc(stPackage* pstPackage,stGnssIn *pstGNSSIn)
{
	uint8_t datenum =0;
	uint16_t i=0;
	char TempStr[20] = {0};
	uint16_t TempStrLeng = 0;

	if(!CheckSum_NMEA(pstPackage->u8Vec_Package,pstPackage->u16Num_Package))
	{
		return _NONE;
	}
	for(i=7;i<pstPackage->u16Num_Package-2;i++)
	{
		if(!((pstPackage->u8Vec_Package[i]==44)||(pstPackage->u8Vec_Package[i]==42)))  //,
		{
			TempStr[TempStrLeng]=pstPackage->u8Vec_Package[i];
			TempStrLeng++;
		}
		else
		{
			datenum++;
			switch(datenum)
			{
			case 1:
				pstGNSSIn->m_stNMEA.m_stGprmc.dUtcTime = strtod(TempStr,0);  //UTC time

				break;
			case 2:
				if(TempStr[0]=='A')
        {
					pstGNSSIn->m_stNMEA.m_stGprmc.u8Data_valid = 1;
        }
				else if(TempStr[0]=='V')
        {
					pstGNSSIn->m_stNMEA.m_stGprmc.u8Data_valid = 0;
        }
				break;
			case 3:
				pstGNSSIn->m_stNMEA.m_stGprmc.dLatitude  = Ddmm2dd(strtod(TempStr,0));
				break;
			case 4:
				if(TempStr[0]=='S')
        {
          pstGNSSIn->m_stNMEA.m_stGprmc.dLatitude= pstGNSSIn->m_stNMEA.m_stGprmc.dLatitude*(-1.0);
        }
				break;
			case 5:
				pstGNSSIn->m_stNMEA.m_stGprmc.dLongitude = Ddmm2dd(strtod(TempStr,0));
				break;
			case 6:
				if(TempStr[0]=='W')
        {
          pstGNSSIn->m_stNMEA.m_stGprmc.dLongitude = pstGNSSIn->m_stNMEA.m_stGprmc.dLongitude*(-1.0);
        }
				break;
			case 7:
				 pstGNSSIn->m_stNMEA.m_stGprmc.fVgoroud =  atof(TempStr)*MILE2KM;
				break;
			case 8:
			   pstGNSSIn->m_stNMEA.m_stGprmc.fHeading = atof(TempStr);
				break;
			case 9:
			   pstGNSSIn->m_stNMEA.m_stGprmc.u32Date = atof(TempStr);
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
	return _GPRMC;
}

static uint8_t Decode_Gphdt(stPackage* pstPackage,stGnssIn *pstGNSSIn)
{
  uint8_t datenum =0;
  uint16_t i=0;
  char TempStr[20] = {0};
  uint16_t TempStrLeng = 0;

  if(!CheckSum_NMEA(pstPackage->u8Vec_Package,pstPackage->u16Num_Package))
  {
    return _NONE;
  }
  for(i=7;i<pstPackage->u16Num_Package-2;i++)
  {
    if(!((pstPackage->u8Vec_Package[i]==44)||(pstPackage->u8Vec_Package[i]==42)))
    {
      TempStr[TempStrLeng]=pstPackage->u8Vec_Package[i];
      TempStrLeng++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
      case 1:
        pstGNSSIn->m_stNMEA.m_stGphdt.fAzi = atof(TempStr);
        break;
      case 2:
        pstGNSSIn->m_stNMEA.m_stGphdt.uTrue = TempStr[0];
        break;
      case 3:
        break;
      }
      TempStrLeng =0;
      memset(TempStr,0,20);
    }
  }
	return _GPHDT;
}


static uint8_t Decode_BestVela(stPackage* pstPackage,stGnssIn *pstGnssIn)
{
  char datenum =0;
  int i=0;
  int t=0;
  int TempStrLeng = 0;
  u8StrLen = 0;

  if(!Checmsum_Novtel(pstPackage->u8Vec_Package,pstPackage->u16Num_Package))
  {
    return _NONE;
  }
  memset(TempStr,0,20);
  for(i=10;i<pstPackage->u16Num_Package-2;i++)
  {
    if(!((pstPackage->u8Vec_Package[i]==0x2A)||(pstPackage->u8Vec_Package[i]==0x2C)||(pstPackage->u8Vec_Package[i]==0x3B)))  //,
    {
      TempStr[TempStrLeng]=pstPackage->u8Vec_Package[i];
      TempStrLeng++;
      u8StrLen++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
        case 1:/* port */
        {

          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8Port,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 2:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8Sequence,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 3:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8IdleTime,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 4:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8TimeStatus,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 5:
          pstGnssIn->m_stBestVela.m_stLogHeader.u16Week = atof(TempStr);
          u8StrLen = 0;
        break;/* GPS Time */
        case 6:
          pstGnssIn->m_stBestVela.m_stLogHeader.dGpsSec =  strtod(TempStr,0);
        u8StrLen = 0;
        break;
        case 7:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8ReceiverStatus,TempStr,u8StrLen);
          u8StrLen = 0;
        }
          break;
        case 8:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8Reserved,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 9:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8Version,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 10:
        {
           memcpy(&pstGnssIn->m_stBestVela.u8SolStatus,TempStr,u8StrLen);
           u8StrLen = 0;
        }break;
        case 11:  /*sol status */
        {
          if(!memcmp("NONE",TempStr,4))
          {
            pstGnssIn->m_stBestVela.u8P_VType=0;
          }
          else if(!memcmp("PROPAGATED",TempStr,10))
          {
            pstGnssIn->m_stBestVela.u8P_VType=0;
          }
          else
          {
            pstGnssIn->m_stBestVela.u8P_VType=1;
            pstGnssIn->m_stBestVela.u8VDataFlag =1;
          }

          memcpy(&pstGnssIn->m_stBestVela.u8VelType,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 12:
        {
          memcpy(&pstGnssIn->m_stBestVela.u8Latency,TempStr,u8StrLen);
          u8StrLen = 0;
        }
        break;
        case 13:
        {
          memcpy(&pstGnssIn->m_stBestVela.u8Age,TempStr,u8StrLen);
          u8StrLen = 0;
        }break;
        case 14:
        {
          pstGnssIn->m_stBestVela.fVGround  = (float)atof(TempStr);
          u8StrLen = 0;
        }
        break;
        case 15:
        {
          pstGnssIn->m_stBestVela.fTrack = (float)atof(TempStr);
          pstGnssIn->m_stBestVela.fVe = (float)sin(pstGnssIn->m_stBestVela.fTrack*_D2R)*pstGnssIn->m_stBestVela.fVGround;
          pstGnssIn->m_stBestVela.fVn = (float)cos(pstGnssIn->m_stBestVela.fTrack*_D2R)*pstGnssIn->m_stBestVela.fVGround;
          u8StrLen = 0;
        }
        break;
        case 16:
        {
          pstGnssIn->m_stBestVela.fVu =  (float)atof(TempStr);
          u8StrLen = 0;
        }
        break;
        case 17:
        {
          memcpy(&pstGnssIn->m_stBestVela.m_stLogHeader.u8Reserved,TempStr,u8StrLen);
          u8StrLen = 0;
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
  if(pstGnssIn->m_stBestVela.u8P_VType==1)
  {
    pstGnssIn->m_stBestVela.u8VDataFlag =1;
  }
  
 return _BESTVELA;
}

static uint8_t Decode_Headinga(stPackage* pstPackage,stGnssIn *pstGNSSIn)
{
  char datenum =0;
  int i=0;
  char TempStr[40];
  int TempStrLeng = 0;
  u8StrLen = 0;

  if(!Checmsum_Novtel(pstPackage->u8Vec_Package,pstPackage->u16Num_Package))
  {
    return _NONE;
  }

  memset(TempStr,0,20);
  for(i=10;i<pstPackage->u16Num_Package-2;i++)
  {

    if(!((pstPackage->u8Vec_Package[i]==0x2A)||(pstPackage->u8Vec_Package[i]==0x2C)||(pstPackage->u8Vec_Package[i]==0x3B)))  //,
    {
      TempStr[TempStrLeng]=pstPackage->u8Vec_Package[i];
      TempStrLeng++;
      u8StrLen++;
    }
    else
    {
      datenum++;
      switch(datenum)
      {
      case 1:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8Port,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 2:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8Sequence,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 3:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8IdleTime,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 4:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8TimeStatus,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 5:
      {
        pstGNSSIn->m_stHeadinga.m_stLogHeader.u16Week = atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 6:
      {
        pstGNSSIn->m_stHeadinga.m_stLogHeader.dGpsSec =  atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 7:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8ReceiverStatus,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 8:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8Reserved,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 9:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.m_stLogHeader.u8Version,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 10:
      {
        pstGNSSIn->m_stHeadinga.u32SolStat = (uint32_t)Test_SolStat(TempStr,TempStrLeng);
        memcpy(&pstGNSSIn->m_stHeadinga.strSolStat,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 11:
      {
        pstGNSSIn->m_stHeadinga.uP_VType =Test_P_V_Type(TempStr,TempStrLeng);
        memcpy(&pstGNSSIn->m_stHeadinga.strPosType,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 12:
      {
        pstGNSSIn->m_stHeadinga.fBaseline = atof(TempStr);
        memcpy(&pstGNSSIn->m_stHeadinga.strBaseLine,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 13:
      {
        pstGNSSIn->m_stHeadinga.fHeading = atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 14:
      {
        pstGNSSIn->m_stHeadinga.fPitch = atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 15:
      {
        u8StrLen = 0;
      }
      break;
      case 16:
      {
        pstGNSSIn->m_stHeadinga.fHdg_std =  atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 17:
      {
        pstGNSSIn->m_stHeadinga.fPtch_std =  atof(TempStr);
        u8StrLen = 0;
      }
      break;
      case 18:
      {
        memcpy(&pstGNSSIn->m_stHeadinga.cStnID,TempStr,u8StrLen);
        u8StrLen = 0;
      }
      break;
      case 19:
        pstGNSSIn->m_stHeadinga.uSVs =  atof(TempStr);
      break;
      case 20:
        pstGNSSIn->m_stHeadinga.uSolnSVs =  atof(TempStr);
      break;
      case 21:
        pstGNSSIn->m_stHeadinga.uObs =  atof(TempStr);
      break;
      case 22:
        pstGNSSIn->m_stHeadinga.uMulti =  atof(TempStr);
      break;
      case 23:
      {
        pstGNSSIn->m_stHeadinga.u8SolSource =  atof(TempStr);
      }
      break;
      case 24:
        pstGNSSIn->m_stHeadinga.ucExtSolStat = (uc8)atoi(TempStr);
      break;
      case 25:
      {
        pstGNSSIn->m_stHeadinga.u8SigMask_1 = (uc8)atoi(TempStr);
      }
      break;
      case 26:
      {
        pstGNSSIn->m_stHeadinga.u8SigMask_2 = (uc8)atoi(TempStr);
      }
      break;
    }
      TempStrLeng =0;
      memset(TempStr,0,40);
   }
 }

	return _HEADINGA;
}

/*
static void Package_GNSS(stGnssOut *pstGNSSOut,stGnssIn *pstGNSSIn)
{
  uint32_t u32Time;

  if(NMEA_USE)
  {
    if((pstGNSSIn->m_stNMEA.u16Flag&GPS_GPGGA_IN)&&(pstGNSSIn->m_stNMEA.u16Flag&GPS_GPRMC_IN))
    {
      pstGNSSIn->m_stNMEA.u16Flag=0;
      memset(pstGNSSOut,0,sizeof(m_stGnssOut));

      pstGNSSOut->u8Start[0] = 0xAB;
      pstGNSSOut->u8Start[1] = 0x10;

      pstGNSSOut->u16Week = Date2Week(pstGNSSIn->m_stNMEA.m_stGprmc.dUtcTime,pstGNSSIn->m_stNMEA.m_stGprmc.u32Date);
      u8Day = ReturnWeekDay(pstGNSSIn->m_stNMEA.m_stGprmc.u32Date);

      if(7==u8Day)
      {
         pstGNSSOut->u32UTC = hhmmss2ss(pstGNSSIn->m_stNMEA.m_stGpgga.dUtcTime)+_UTC2GPS;
      }
      else
      {
         pstGNSSOut->u32UTC = hhmmss2ss(pstGNSSIn->m_stNMEA.m_stGpgga.dUtcTime)+u8Day*24*3600*1000+ _UTC2GPS;
      }

      pstGNSSOut->dLatitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude;
      pstGNSSOut->dLongitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude;
      pstGNSSOut->fAltitude = pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude;
      pstGNSSOut->fHeading =  pstGNSSIn->m_stNMEA.m_stGprmc.fHeading;
      pstGNSSOut->fVgroud = pstGNSSIn->m_stNMEA.m_stGprmc.fVgoroud;
      pstGNSSOut->u16Hdop = (uint16_t)(pstGNSSIn->m_stNMEA.m_stGpgga.fHdop*100.0f);


      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State>0&&pstGNSSIn->m_stNMEA.m_stGprmc.u8Data_valid==1)
      {
        pstGNSSOut->u16Flag|=(1<<0);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==1)
      {
        pstGNSSOut->u16Flag|=(1<<10);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==2)
      {
        pstGNSSOut->u16Flag|=(1<<11);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==5)
      {
        pstGNSSOut->u16Flag|=(1<<12);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==4)
      {
        pstGNSSOut->u16Flag|=(1<<13);
      }

      pstGNSSOut->u16Flag|=(1<<15);

      memset(&pstGNSSIn,0,sizeof(pstGNSSIn));
   }
  }
	else if((pstGNSSIn->u16Flag&GPS_GPGGA_IN)&&(pstGNSSIn->u16Flag&GPS_BESTVELA_IN)&&(pstGNSSIn->u16Flag&GPS_HEADINGA_IN))
	{
    pstGNSSOut->u8Start[0] = 0xAB;
    pstGNSSOut->u8Start[1] = 0x10;

    pstGNSSOut->u16Week = pstGNSSIn->m_stBestVela.m_stLogHeader.u16Week;
    u32Time = (uint32_t)((pstGNSSIn->m_stBestVela.m_stLogHeader.dGpsSec+0.05)*10);
    pstGNSSOut->u32UTC  = u32Time*100;

    pstGNSSOut->dLatitude =  pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude;
    pstGNSSOut->dLongitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude;
    pstGNSSOut->fAltitude =  pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude;

    pstGNSSOut->fVgroud = pstGNSSIn->m_stBestVela.fVGround;
    pstGNSSOut->fHeading = pstGNSSIn->m_stBestVela.fTrack;

    if(pstGNSSIn->u16Flag&GPS_HEADINGA_IN)
    {
      pstGNSSOut->fAzi = pstGNSSIn->m_stHeadinga.fHeading;
    }

	  pstGNSSOut->u16Hdop = (uint16_t)(pstGNSSIn->m_stNMEA.m_stGpgga.fHdop*100.0f);

    if((pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State)>0&&(1==pstGNSSIn->m_stBestVela.u8VDataFlag))
    {
      pstGNSSOut->u16Flag|=(1<<0);
    }
    if((48==pstGNSSIn->m_stHeadinga.uP_VType)||(50==pstGNSSIn->m_stHeadinga.uP_VType))
    {
       pstGNSSOut->u16Flag|=(1<<1);
    }
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==1)
    {
       pstGNSSOut->u16Flag|=(1<<10);
    }
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==2)
    {
       pstGNSSOut->u16Flag|=(1<<11);
    }
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==5)
    {
       pstGNSSOut->u16Flag|=(1<<12);
    }
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==4)
    {
       pstGNSSOut->u16Flag|=(1<<13);
    }
		pstGNSSOut->u16Flag|=(1<<15);

		memset(&m_stGnssIn,0,sizeof(m_stGnssIn));
	}
}
*/
uint32_t hhmmss2ss(double fddmm)
{
  uint32_t ddmm;
  int hh = 0;
  int mm = 0;
  uint32_t ss = 0;

  ddmm = (uint32_t)((fddmm+0.05)*10);
  ddmm  = ddmm*100;

  hh = (int)(ddmm/10000000);
  mm = (ddmm-hh*10000000)/100000;
  ss = ddmm-hh*10000000.0-mm*100000.0;
  ss = hh*3600000+mm*60000+ss;

  return ss;
 }

 static uint16_t Date2Week(float fTime,uint32_t u32Data)
{
  uint16_t u16Week = 0;
  uint8_t u8Month=0,u8Day=0,u8Hour=0,u8Minute=0,u8Second=0;
  uint16_t u16Year=0;
  float UT;
  int Y, M;
  double JD;
  uint32_t u32Time;

  u32Time = (uint32_t)fTime;

  u8Day= u32Data*0.0001f;
  u8Month = (u32Data-u8Day*10000)*0.01f;
  u16Year = u32Data-u8Day*10000-u8Month*100;
  u16Year +=2000;

  u8Hour = (float)u32Time*0.0001f;
  u8Minute = (float)(u32Time-u8Hour*10000)*0.01f;
  u8Second = u32Time-u8Hour*10000-u8Minute*100;

  u8Hour+=8;

  UT = (float)u8Hour + (float)u8Minute/60 + (float)u8Second/3600;
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

  JD = (double)Y*365.25+(30.6001 * (M + 1))+u8Day+UT/24+1720981.5;

  u16Week = (uint16_t)((JD - 2444244.5) / 7);

  return u16Week;
}

 uint8_t ReturnWeekDay( uint32_t u32Date)
{
  uint8_t result = 0;
  uint16_t u16Year,u16Month,u16Day;
  uint16_t y = 0, c = 0, m = 0, d = 0;

  u16Day= u32Date*0.0001f;
  u16Month = (u32Date-u16Day*10000)*0.01f;
  u16Year = u32Date-u16Day*10000-u16Month*100;
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

static char Checmsum_Novtel(uint8_t *ucBuffer,uint32_t ulCount)
{
  unsigned char Check_sum_char[8];
  uint32_t sum_u32=0;
  memcpy(Check_sum_char,ucBuffer+ulCount-10,8);
  sum_u32= Asc_Int2Int(Check_sum_char);

  if(sum_u32==CalculateBlockCRC32(ulCount-12,ucBuffer+1))
    return 1;
  else
    return 0;
}
uint32_t  Asc_Int2Int(unsigned char*Buffer)
{
  unsigned int asc_0=0;
  asc_0 = ((unsigned int)ASCII2u8(Buffer[0]))*16 + ASCII2u8(Buffer[1]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)ASCII2u8(Buffer[2]))*16 + ASCII2u8(Buffer[3]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)ASCII2u8(Buffer[4]))*16 + ASCII2u8(Buffer[5]);
  asc_0 = asc_0<<8;
  asc_0 += ((unsigned int)ASCII2u8(Buffer[6]))*16 + ASCII2u8(Buffer[7]);
  return asc_0;
}

uint32_t CalculateBlockCRC32(uint32_t ulCount,uint8_t *ucBuffer ) /* Data block */
{
  uint32_t ulTemp1;
  uint32_t ulTemp2;
  uint32_t ulCRC = 0;
  while ( ulCount-- != 0 )
  {	ulTemp1 = ( ulCRC >> 8 ) & 0x00FFFFFFL;
    ulTemp2 = CRC32Value( ((int) ulCRC ^ *ucBuffer++ ) & 0xff );
    ulCRC = ulTemp1 ^ ulTemp2;
  }
  return( ulCRC );
}

uint32_t CRC32Value(int32_t i)
{
  int32_t j;
  uint32_t ulCRC;
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

static char Test_P_V_Type(const char* DataBuffer,unsigned Length)
{
  if(!memcmp("NONE",DataBuffer,4))
  {
    return 0;					//No solution
  }
  else if(!memcmp("FIXEDPOS",DataBuffer,8))
  {
    return 1; 				//Position has been fixed by the FIX POSITION command
  }
  else if(!memcmp("FIXEDHEIGHT",DataBuffer,11))
  {
    return 2;				 //Position has been fixed by the FIX HEIGHT/AUTO command
  }
  else if(!memcmp("DOPPLER_VELOCITY",DataBuffer,16))
  {
    return 8;				 //	Velocity computed using instantaneous Doppler
  }
  else if(!memcmp("SINGLE",DataBuffer,6))
  {
    return 16; 				//Single point position
  }
  else if(!memcmp("PSRDIFF",DataBuffer,7))
  {
    return 17;				 //Pseudorange differential solution
  }
  else if(!memcmp("WAAS",DataBuffer,4))
  {
    return 18;				 //Solution calculated using corrections from an SBAS
  }
  else if(!memcmp("PROPAGATED",DataBuffer,10))
  {
    return 19;				 //Propagated by a Kalman filter without new observations
  }
  else if(!memcmp("OMNISTAR",DataBuffer,8))
  {
    return 20; 				//OmniSTAR VBS position (L1 sub-meter)
  }
  else if(!memcmp("L1_FLOAT",DataBuffer,8))
  {
    return 32;				//Floating L1 ambiguity solution
  }
  else if(!memcmp("IONOFREE_FLOAT",DataBuffer,14))
  {
    return 33;				//Floating ionospheric-free ambiguity solution
  }
  else if(!memcmp("NARROW_FLOAT",DataBuffer,12))
  {
    return 34;				//Floating narrow-lane ambiguity solution
  }
  else if(!memcmp("L1_INT",DataBuffer,6))
  {
    return 48; 				//Integer L1 ambiguity solution
  }
  else if(!memcmp("WIDE_INT",DataBuffer,7))
  {
    return 49;				//Integer wide-lane ambiguity solution
  }
  else if(!memcmp("NARROW_INT",DataBuffer,10))
  {
    return 50;				//Integer narrow-lane ambiguity solution
  }
  else if(!memcmp("CDGPS",DataBuffer,5))
  {
    return 66;				//Position solution using CDGPS correction
  }
  else
  {
    return 0;
  }

}

static char Test_SolStat(const char* DataBuffer,unsigned Length)
{
  if(!memcmp("SOL_COMPUTED"	,	DataBuffer,12))		return 0;
  else if(!memcmp("INSUFFICIENT_OBS"	,	DataBuffer,16))		return 1;
  else if(!memcmp("NO_CONVERGENCE"	,	DataBuffer,14))		return 2;
  else if(!memcmp("SINGULARITY"	,	DataBuffer,11))			return 3;
  else if(!memcmp("COV_TRACE"	,	DataBuffer,9))				return 4;
  else if(!memcmp("TEST_DIST"	,	DataBuffer,9))				return 5;
  else if(!memcmp("COLD_START"	,	DataBuffer,10))			return 6;
  else if(!memcmp("V_H_LIMIT"	,	DataBuffer,9))				return 7;
  else if(!memcmp("VARIANCE"	,	DataBuffer,8))				return 8;
  else if(!memcmp("RESIDUALS"	,	DataBuffer,9))				return 9;
  else if(!memcmp("DELTA_POS"	,	DataBuffer,9))				return 10;
  else if(!memcmp("NEGATIVE_VAR"	,DataBuffer,12))		return 11;
  else if(!memcmp("INTEGRITY_WARNING"	,	DataBuffer,17))		return 13;
  else if(!memcmp("PENDING"	,	DataBuffer,7))							return 18;
  else if(!memcmp("INVALID_FIX"	,	DataBuffer	,	11))			return 19;
  else if(!memcmp("UNAUTHORIZED"	,	DataBuffer	,	12))		return 20;
  else if(!memcmp("ANTENNA_WARNING"	,	DataBuffer	,	15))	return 21;
  else		return 0;
}

extern void Combain_GNSS(stGnssOut *pstGNSSOut,stGnssIn *pstGNSSIn)
{
  uint32_t u32Time;

  pstGNSSOut->u8Start[0] = 0xAB;
  pstGNSSOut->u8Start[1] = 0x33;

  if(NMEA_USE)
  {
    if((pstGNSSIn->u16Flag&GPS_GPGGA_IN)&&(pstGNSSIn->u16Flag&GPS_GPRMC_IN))
    {
      pstGNSSIn->m_stNMEA.u16Flag=0;
      memset(pstGNSSOut,0,sizeof(m_stGnssOut));

      pstGNSSOut->u8Start[0] = 0xAB;
      pstGNSSOut->u8Start[1] = 0x23;

      pstGNSSOut->u16Week = Date2Week(pstGNSSIn->m_stNMEA.m_stGprmc.dUtcTime,pstGNSSIn->m_stNMEA.m_stGprmc.u32Date);
      u8Day = ReturnWeekDay(pstGNSSIn->m_stNMEA.m_stGprmc.u32Date);

      if(7==u8Day)
      {
         pstGNSSOut->u32UTC = hhmmss2ss(pstGNSSIn->m_stNMEA.m_stGpgga.dUtcTime)+_UTC2GPS;
      }
      else
      {
         pstGNSSOut->u32UTC = hhmmss2ss(pstGNSSIn->m_stNMEA.m_stGpgga.dUtcTime)+u8Day*24*3600*1000+ _UTC2GPS;
      }

      pstGNSSOut->dLatitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude;
      pstGNSSOut->dLongitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude;
      pstGNSSOut->fAltitude = pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude;
      pstGNSSOut->fHeading =  pstGNSSIn->m_stNMEA.m_stGprmc.fHeading;
      pstGNSSOut->fVgroud = pstGNSSIn->m_stNMEA.m_stGprmc.fVgoroud;
      pstGNSSOut->u16Hdop = (uint16_t)(pstGNSSIn->m_stNMEA.m_stGpgga.fHdop*100.0f);

      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State>0&&pstGNSSIn->m_stNMEA.m_stGprmc.u8Data_valid==1)     ///// 位置和速度有效
      {
        pstGNSSOut->u16Flag|=(1<<0);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==1)
      {
        pstGNSSOut->u16Flag|=(1<<10);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==2)
      {
        pstGNSSOut->u16Flag|=(1<<11);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==5)
      {
        pstGNSSOut->u16Flag|=(1<<12);
      }
      if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==4)
      {
        pstGNSSOut->u16Flag|=(1<<13);
      }
      pstGNSSOut->u16Flag|=(1<<15);
		  memset(&pstGNSSIn,0,sizeof(pstGNSSIn));
      
      memset(u8DataSendARM2,0,sizeof(u8DataSendARM2));
      memcpy(u8DataSendARM2,&m_stGnssOut,sizeof(m_stGnssOut));
      
      m_stGnssOut.u8Check = Check_Out(u8DataSendARM2,sizeof(m_stGnssOut)-1);
      
      memcpy(u8DataSendARM2,&m_stGnssOut,sizeof(m_stGnssOut));
      
      
      
	 }
}
  else if((pstGNSSIn->u16Flag&GPS_GPGGA_IN)&&(pstGNSSIn->u16Flag&GPS_BESTVELA_IN))
	{
    pstGNSSOut->u16Week = pstGNSSIn->m_stBestVela.m_stLogHeader.u16Week;

    u32Time = (uint32_t)((pstGNSSIn->m_stBestVela.m_stLogHeader.dGpsSec+0.05)*10);
    pstGNSSOut->u32UTC  = u32Time*100;

    pstGNSSOut->dLatitude =  pstGNSSIn->m_stNMEA.m_stGpgga.dLatitude;
    pstGNSSOut->dLongitude = pstGNSSIn->m_stNMEA.m_stGpgga.dLongitude;
    pstGNSSOut->fAltitude =  pstGNSSIn->m_stNMEA.m_stGpgga.fAltitude;
    pstGNSSOut->fVgroud = pstGNSSIn->m_stBestVela.fVGround;
    pstGNSSOut->fHeading = pstGNSSIn->m_stBestVela.fTrack;
    pstGNSSOut->u16Hdop = (uint16_t)(pstGNSSIn->m_stNMEA.m_stGpgga.fHdop*100.0f);

    if((pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State)>0&&(1==pstGNSSIn->m_stBestVela.u8VDataFlag))
    {
      pstGNSSOut->u16Flag|=(1<<0);
      memcpy(&m_stGnssModify,pstGNSSIn,sizeof(m_stGNSSIn));
     }
		/* single point */
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==1)
    {
      pstGNSSOut->u16Flag|=(1<<10);
    }
		/* differential */
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==2)
    {
      pstGNSSOut->u16Flag|=(1<<11);
    }
		/*  float */
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==5)
    {
      pstGNSSOut->u16Flag|=(1<<12);
    }
		/* fixed */
    if(pstGNSSIn->m_stNMEA.m_stGpgga.u8GPS_State==4)
    {
      pstGNSSOut->u16Flag|=(1<<13);
    }
    pstGNSSOut->u16Flag|=(1<<15);
	}

  if(pstGNSSIn->u16Flag&GPS_HEADINGA_IN)
  {
    pstGNSSOut->fAzi = pstGNSSIn->m_stHeadinga.fHeading;
    if((48==pstGNSSIn->m_stHeadinga.uP_VType)||(50==pstGNSSIn->m_stHeadinga.uP_VType))
    {
      pstGNSSOut->u16Flag|=(1<<1);
      memcpy(&m_stHeadingaSave,&pstGNSSIn->m_stHeadinga,sizeof(m_stGNSSIn.m_stHeadinga));
    }
  }
}

static uint8_t Check_Out(uint8_t* Buffer ,int length)
{
  uint16_t sum = 0;
  uint8_t i;
  uint8_t sum_low;

  for(i=2;i<length;i++)
  {
    sum+=Buffer[i];
  }

  sum_low = sum&0x00ff;
  return sum_low;

}
