
#include "gnss.h"


NMEA Nmea;


//GNSS数据打包上传
void GNSS_Package(NMEA* Nmea)
{
	uint8_t u8Day;
  
	GNSS Gnss;
	uint8_t num;
	
	if(Nmea->Gngga.GPS_Status>0 && Nmea->Gnrmc.u8Data_valid==1)     // 位置和速度有效
	{
		Gnss.u16Week = Date2Week(Nmea->Gnrmc.UTC_Time, Nmea->Gnrmc.UTC_Date);
    u8Day = ReturnWeekDay(Nmea->Gnrmc.UTC_Date);
		
		Gnss.u8Start[0] = 0xAB;
		Gnss.u8Start[1] = 0x10;

    if(u8Day == 7)
      Gnss.u32UTC = hhmmss2ss(Nmea->Gngga.UTC_Time) + 17000;
    else
      Gnss.u32UTC = hhmmss2ss(Nmea->Gngga.UTC_Time) + u8Day * 24 * 3600 * 1000 + 17000;

		Gnss.dLatitude = Nmea->Gngga.Latitude;
		Gnss.dLongitude = Nmea->Gngga.Longitude;
		Gnss.fAltitude = Nmea->Gngga.Altitude;
		Gnss.fHeading =  Nmea->Gnrmc.Ground_Course;
		Gnss.fVgroud = Nmea->Gnrmc.Ground_Speed;
		Gnss.u16Hdop = Nmea->Gngga.u16Hdop;
		
		Gnss.u16Flag|=(1<<0);
		
		if(Nmea->Gngga.GPS_Status==1)    //// 单点
		{
			Gnss.u16Flag|=(1<<10);
		}
		if(Nmea->Gngga.GPS_Status==2)    //// 差分
		{
			Gnss.u16Flag|=(1<<11);
		}
		if(Nmea->Gngga.GPS_Status==5)    //// 浮点
		{
			Gnss.u16Flag|=(1<<12);
		}
		if(Nmea->Gngga.GPS_Status==4 || Nmea->Gngga.GPS_Status==5)    //// RTK
		{
			Gnss.u16Flag|=(1<<13);		
		}
		
		Gnss.u16Flag|=(1<<15);
		
		Gnss.u8CheckSum = check_sum((uint8_t*)&Gnss, sizeof(Gnss)-1);
		
		num = sizeof(Gnss);
		
		while(DMA_GetFlagStatus(DMA2_Stream6, DMA_FLAG_TCIF6)==0);
		
		memset(USART6_Buffer_Tx, 0, sizeof(USART6_Buffer_Tx));	//清空内存
		memcpy(USART6_Buffer_Tx, &Gnss, num);	//复制内存
		USART_DMA_TX(USART_6, num);
	}
	memset(Nmea, 0, sizeof(*Nmea));	//清空内存
}


//NMEA 解码
void NMEA_Decoding(uint8_t* data)
{
	uint8_t Data_Frame[100];
	uint16_t i=0, Frame_Flag=0, Start=0, End=0, geshu=0;
	
	geshu = USART1_BufferSize_Rx - DMA_GetCurrDataCounter(DMA2_Stream2);
	
	for(i=0; i<geshu; i++)
	{
		if(data[i]=='$')
		{
			Start = i;
			Frame_Flag=1;
		}
		
		if(Frame_Flag==1 && data[i]==0x0A)
		{
			End = i;
			Frame_Flag=2;
		}
		
		if(Frame_Flag==2)
		{
			memset(Data_Frame, 0, sizeof(Data_Frame));	//清空内存
			memcpy(Data_Frame, data+Start, End-Start+1);	//复制内存
			
			NMEA_Protocol(Data_Frame, &Nmea);
			
			Frame_Flag=0;
		}
	}
}


//NMEA 协议
void NMEA_Protocol(uint8_t* data, NMEA* Nmea)
{
	if(!memcmp("$GNGGA,", data, 7))
	{
		NMEA_GNGGA(data, &Nmea->Gngga);
	}
	else if(!memcmp("$GNRMC,", data, 7))
	{
		NMEA_GNRMC(data, &Nmea->Gnrmc);
	}
}


void NMEA_GNGGA(uint8_t* data, GNGGA* gngga)
{
	char Data_Section[20];
	uint16_t i=0, j=0, k=0;
	
	for(i=7; data[i-1]!=42; i++)
	{
		if(!(data[i]==44 || data[i]==42))
		{
			Data_Section[j++] = data[i];
		}
		else
		{
			j=0;
			k++;
			
			switch(k)
			{
				case 1: gngga->UTC_Time = atof(Data_Section); break;
				case 2: gngga->Latitude = Ddmm2dd(atof(Data_Section)); break;
				case 3:
				{
					gngga->N_or_S = Data_Section[0]; 
					if(gngga->N_or_S == 'S')
						gngga->Latitude = gngga->Latitude * (-1.0);
					break;
				}
				case 4: gngga->Longitude = Ddmm2dd(atof(Data_Section)); break;
				case 5:
				{
					gngga->E_or_W = Data_Section[0]; 
					if(gngga->E_or_W == 'W')
						gngga->Longitude = gngga->Longitude * (-1.0);
					break;
				}
				case 6:
				{
					gngga->GPS_Status = atoi(Data_Section);
					if(gngga->GPS_Status>0)
						gngga->u8GpggaDataFlag = 1;
					if(gngga->GPS_Status==6)
						gngga->u8GpggaDataFlag = 0;
					if(gngga->GPS_Status==4 || gngga->GPS_Status==5)
						gngga->u8RtkFlag = 1;
					else
						gngga->u8RtkFlag = 0;
					break;
				}
				case 7:
				{
					gngga->Satellite_Num = atoi(Data_Section);
					if(gngga->Satellite_Num<4)
					{
						gngga->u8GpggaDataFlag = 0;
						gngga->u8RtkFlag = 0;
					}
					break;
				}
				case 8:
				{
					gngga->HDOP = atof(Data_Section);
					gngga->u16Hdop = (uint16_t)(gngga->HDOP * 100);
					break;
				}
				case 9: gngga->Altitude = atof(Data_Section); break;
				case 10: break;
				case 11:
				{
					gngga->Geoid_Height = atof(Data_Section);
					gngga->Altitude += gngga->Geoid_Height;
					break;
				}
				case 12: break;
				case 13: gngga->Diff_Time = atoi(Data_Section); break;
				case 14: gngga->Diff_Base = atoi(Data_Section); break;
			}
			memset(Data_Section, 0, 20);	//清空内存
		}
	}
}


void NMEA_GNRMC(uint8_t* data, GNRMC* gnrmc)
{
	char Data_Section[20];
	uint16_t i=0, j=0, k=0;
	
	for(i=7; data[i-1]!=42; i++)
	{
		if(!(data[i]==44 || data[i]==42))
		{
			Data_Section[j++] = data[i];
		}
		else
		{
			j=0;
			k++;
			
			switch(k)
			{
				case 1: gnrmc->UTC_Time = atof(Data_Section); break;
				case 2:
				{
					gnrmc->Location_State = Data_Section[0];
					if(gnrmc->Location_State == 'A')
						gnrmc->u8Data_valid = 1;
					else
						gnrmc->u8Data_valid = 0;
					break;
				}
				case 3: gnrmc->Latitude = Ddmm2dd(atof(Data_Section)); break;
				case 4:
				{
					gnrmc->N_or_S = Data_Section[0]; 
					if(gnrmc->N_or_S == 'S')
						gnrmc->Latitude = gnrmc->Latitude * (-1.0);
					break;
				}
				case 5: gnrmc->Longitude = Ddmm2dd(atof(Data_Section)); break;
				case 6:
				{
					gnrmc->E_or_W = Data_Section[0]; 
					if(gnrmc->E_or_W == 'W')
						gnrmc->Longitude = gnrmc->Longitude * (-1.0);
					break;
				}
				case 7: gnrmc->Ground_Speed = atof(Data_Section) * (1852.0/3600.0); break;	//把 地速 转换为 m/s
				case 8: gnrmc->Ground_Course = atof(Data_Section); break;
				case 9: gnrmc->UTC_Date = atoi(Data_Section); break;
				case 10: gnrmc->Mag_Declination = atof(Data_Section); break;
				case 11: gnrmc->Mag_Direction = Data_Section[0]; break;
				case 12: gnrmc->Mode_Indicator = Data_Section[0]; break;
			}
			memset(Data_Section, 0, 20);	//清空内存
		}
	}
}


double Ddmm2dd(double ddmm) ///// ddmm_mm转换为 dd_dd,用于GPGGA中的经纬度格式转换
{
	int tt =0;
	double d_in =0.0;
	double dd_out =0.0;
	tt = (int)(ddmm/100.0);
	d_in = ((ddmm/100 -tt)*100)/60;
	dd_out = tt + d_in; 
	return dd_out;
}


uint16_t Date2Week(float fTime, uint32_t u32Data)
{
	uint16_t u16Week = 0;
	uint8_t u8Month=0,u8Day=0,u8Hour=0,u8Minute=0,u8Second=0;
	uint16_t u16Year=0;
	float UT;
	int Y, M;
	float JD;
	uint32_t u32Time;

	u32Time = (uint32_t)fTime;

	//////  year,month,day

	u8Day= u32Data*0.0001f;  
	u8Month = (u32Data-u8Day*10000)*0.01f;
	u16Year = u32Data-u8Day*10000-u8Month*100;
	u16Year +=2000;



	//// hour,minute,second
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

	u16Week = (int)((JD - 2444244.5)/7);

	return u16Week;
}


uint32_t hhmmss2ss(double fddmm) ///// ddmm_mm转换
{
	uint32_t ddmm;

	int hh = 0;
	int mm = 0;
	uint32_t ss = 0;
	
 	ddmm = (uint32_t)((fddmm+0.05)*10);
 	
 	ddmm  = ddmm*100;
	
//	ddmm = (uint32_t)((fddmm+0.0005)*1000);

	hh = (int)(ddmm/10000000);
	mm = (ddmm-hh*10000000)/100000;
	
	ss = ddmm-hh*10000000.0-mm*100000.0;
	
	ss = hh*3600000+mm*60000+ss;
	
	return ss;	
}


uint8_t check_sum(uint8_t* Buffer, int length)
{
	uint16_t sum = 0;
	uint8_t i;
	uint8_t sum_low;
	
	for(i=0;i<length;i++)
	{
		sum+=Buffer[i];
	}
	
	sum_low = sum&0x00ff;
	return sum_low;
}


uint8_t ReturnWeekDay(uint32_t u32Date)
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
