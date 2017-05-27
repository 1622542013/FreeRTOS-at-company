#include "Decode_Ublox.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GPGGA_DATA gpgga;
GPRMC_DATA gprmc;

void PackGgaData(GPGGA_DATA* gga,const TpChar* data_buff[]);
void PackRmcData(GPRMC_DATA* rmc,const TpChar* data_buff[]);
TpUchar CheckNmea(const TpUchar *buf,const TpUint16 count);
TpVoid TimeChange(TpUint16 * week,TpUint32 * time_week_s);
TpDouble Ddmmtodegree(TpDouble dm_degree);


TpVoid AsciiDivision(TpChar* pBuf,TpUint32 length,TpChar* Processed[])
{
	TpChar i = 0;
	TpChar valu_num = 0;
	
	Processed[valu_num] = &pBuf[i];
	valu_num++;
	
  for(i = 0;i < length;i++)
	{
		if(pBuf[i] == *COMMA_ASCII_DIVISION)
		{
			if(pBuf[i+1] == *COMMA_ASCII_DIVISION)
			{
				Processed[valu_num] = NULL;
				pBuf[i] = NULL;
			}
			else
			{
				Processed[valu_num] = &pBuf[i+1];
				pBuf[i] = NULL;
			}
			
			valu_num++;
		}	
	}
}

TpUchar Acsii16IntoUchar(TpUchar check_buff[])
{
	TpUchar check[2] = {0};
	TpUchar check_U16;
	
	for(TpUchar i = 0;i < 2;i++)
	{
		if((check_buff[i] >= 'A') && ((check_buff[i] <= 'Z')))
		{
			check[i] = check_buff[i] - 'A' + 0x0A;
		}
		else if((check_buff[i] >= 'a') && ((check_buff[i] <= 'z')))
		{
			check[i] = check_buff[i] - 'a' + 0x0a;
		}
		else if((check_buff[i] >= '0') && ((check_buff[i] <= '9')))
		{
			check[i] = check_buff[i] - '0'+ 0x00;
		}
	}
	
	check_U16 = (check[0] << 4) + check[1];
	
	return check_U16;
}

TpVoid Nema0183Decode(TpUchar *buf,TpUint16 length)
{
	static TpUchar* temp_buff[20];
	TpUchar  check = 0;
		
  check = Acsii16IntoUchar(&buf[length - 4]);
	
	if(CheckNmea(buf,length) != check)
	{
		return ;
	}
	
	if(!memcmp(HEAD_GGA,buf,sizeof(HEAD_GGA)-1))
	{
			AsciiDivision((TpChar*)buf,length,(TpChar**)temp_buff);	
			PackGgaData(&gpgga,(const TpChar**)temp_buff);		
	}
	else if(!memcmp(HEAD_RMC,buf,sizeof(HEAD_RMC)-1))
	{
			AsciiDivision((TpChar*)buf,length,(TpChar**)temp_buff);
			PackRmcData(&gprmc,(const TpChar**)temp_buff);		
	}
}

TpVoid DecodeUblox(TpUchar *buf,TpUint16 length)
{
	static TpUchar temp_buff[100];
	static TpUchar  start_flag = 0;
	
	TpUint16 i = 0;
	TpUint16 one_command_num = 0;

	for(i = 0;i < length;i++)
	{
		switch(buf[i])
		{
			case '$'	:
								 start_flag = 1;
								 temp_buff[one_command_num] = buf[i];
								 one_command_num++;
								 break;
			case '\n'	:
								if((start_flag == 1)&&(buf[i - 1] == '\r'))
								{
									temp_buff[one_command_num] = buf[i];
									one_command_num++;
									Nema0183Decode(temp_buff,one_command_num);
									start_flag = 0;
									one_command_num = 0;
									memset(temp_buff,0,100);
								}	
								break;
			default 	:
								if(start_flag == 1)
								{
									temp_buff[one_command_num] = buf[i];
									one_command_num++;
								}
								break;
		}
	}
}


TpUchar CheckSumNmea(const TpUchar *buf,const TpUint16 count)
{
  TpUint16 i;
  TpUchar check=0;
  for(i=1;i<count-5;i++)/*except '*' 'check'(1 byte) '\r' '\n'*/
  {
    check ^= buf[i];
  }
	
	return check;
}


void PackGgaData(GPGGA_DATA* gga,const TpChar* data_buff[])
{
	gga->time_utc = atof(data_buff[1]);
	
	gga->lat 			= atof(data_buff[2]);
	gga->lat_dir  = *data_buff[3];
	gga->lon 			= atof(data_buff[4]);
	gga->lon_dir 	= *data_buff[5];
	
	gga->quality  = atoi(data_buff[6]);
	gga->numsv    = atoi(data_buff[7]);
	gga->hdop     = atof(data_buff[8]);
	gga->alt			= atof(data_buff[9]);
	
}

void PackRmcData(GPRMC_DATA* rmc,const TpChar* data_buff[])
{
	rmc->time_utc = atof(data_buff[1]);
	rmc->status   = *data_buff[2];
	
	rmc->lat 			= atof(data_buff[3]);
	rmc->lat_dir  = *data_buff[4];
	rmc->lon 			= atof(data_buff[5]);
	rmc->lon_dir 	= *data_buff[6];
	
	rmc->spd      = atof(data_buff[7]);
	rmc->cog      = atof(data_buff[8]);
	rmc->date     = atof(data_buff[9]);
}

TpUchar CheckNmea(const TpUchar *buf,const TpUint16 count)
{
  TpUint16 i;
  TpUchar check_sum=0;
  for(i=1;i<count-5;i++)
  {
    check_sum ^= buf[i];
  }
	
	return check_sum;
}

/*--------------------------------------------------------*/
TpUchar Gnss_not_already_flag;
TpVoid PackGnssData(GnssOutPut* gnss)
{
	if(gpgga.time_utc != gprmc.time_utc)
	{
		Gnss_not_already_flag = 1;
		memset(gnss,0xff,sizeof(GnssOutPut));
		gnss->head = 0xFEDC;
		gnss->flag = GNSS_INCOMPLETE;
		return ;
	}
	else
	{
		Gnss_not_already_flag = 0;
	}
	
	gnss->head = 0xFEDC;

	
	TimeChange((TpUint16 *)&gnss->week_num,(TpUint32 *)&gnss->week_second);
	
	
	switch(gpgga.quality)
	{
		case 1 : gnss->flag |= GNSS_FIX_SPS;	gnss->flag |= GNSS_FIX_PV | GNSS_FIX_DATA;break; 
		case 2 : gnss->flag |= GNSS_FIX_DGPS;	gnss->flag |= GNSS_FIX_PV | GNSS_FIX_DATA;break; 
		case 4 : gnss->flag |= GNSS_FIX_RTK;	gnss->flag |= GNSS_FIX_PV | GNSS_FIX_DATA;break;
		case 5 : gnss->flag |= GNSS_FIX_FLOAT;gnss->flag |= GNSS_FIX_PV | GNSS_FIX_DATA;break; 
		default : break;
	}
	

	if((gpgga.quality == 0)||(gprmc.status == 'V'))
	{
		gnss->flag = 0 ;
	  gnss->lat = 0;
		gnss->lon = 0;
		gnss->alt = 0;
		gnss->spd = 0;
		gnss->heading = 0;
	}
	else
	{
		gnss->lon = Ddmmtodegree(gpgga.lon);
		gnss->lat = Ddmmtodegree(gpgga.lat);

		
			if(gpgga.lat_dir == 'S')
			{
				gnss->lat = gnss->lat * (-1.0);
			}
			else
			{
	  			gnss->lat = gnss->lat;				
			}
			
			if(gpgga.lon_dir == 'W')
			{
				gnss->lon = gnss->lon * (-1.0);
			}
			else
			{
				gnss->lon = gnss->lon;				
			}

			gnss->alt = gpgga.alt;
			gnss->spd = gprmc.spd * MILE2KM;
			gnss->heading = gprmc.cog;
	}
	gnss->orient = 0;
	gnss->hdop = (TpUint16)(gpgga.hdop * 100);
}


TpVoid TimeChange(TpUint16 * week_num,TpUint32 * week_s)
{
	TpUint16   year  = 0;
	TpUint16   month = 0;
	TpUint16   day   = 0;
	
	TpUint16   hour   = 0;
	TpUint16   minute = 0;
	TpDouble   second = 0;

	TpUchar   leap_year = 0;
	TpUchar   month_2_day = 0;
	
	TpUint32  pass_day = 0;
	TpUchar   week_day = 0;

	hour = gpgga.time_utc / 10000;
	minute = ((TpUint32)gpgga.time_utc % 10000) / 100;
	second = gpgga.time_utc - hour * 10000 - minute *100;

	day = gprmc.date / 10000;
	month  = (gprmc.date % 10000) / 100;
	year  =  gprmc.date % 100 + 2000;
	
	for(TpUint32 i = 1980;i < year;i++)
	{
			if((i % 400) == 0)
			{
				leap_year ++;
			}
			else if(((i % 4) == 0)&&((i % 100) != 0))
			{
				leap_year ++;
			}
	}
	
	if((year % 400) == 0)
	{
		month_2_day = 29;
	}
	else if(((year % 4) == 0)&&((year % 100) == 0))
	{
		month_2_day = 29;
	}
	else
	{
		month_2_day = 28;
	}
	
	switch(month)
	{
		case 0 : 	pass_day = 0;
							break;
		case 1 :
			pass_day = day ;
			break;
	  case 2 :	
			pass_day = 31 + day ;
			break;
		case 3 :
			pass_day = 31 * 1 + month_2_day + day ;
			break;
		case 4 :
			pass_day = 31 * 2 + month_2_day + day ;
			break;
		case 5 :
			pass_day = 31 * 2 + 30 + month_2_day + day ;
			break;
		case 6 :
			pass_day = 31 * 3 + 30 + month_2_day + day ;
			break;
		case 7 :
			pass_day = 31 * 3 + 30 * 2 + month_2_day + day ;
			break;
		case 8 :
			pass_day = 31 * 4 + 30 * 2 + month_2_day + day ;
			break;
		case 9 :
			pass_day = 31 * 5 + 30 * 2 + month_2_day + day ;
			break;
		case 10 :
			pass_day = 31 * 5 + 30 * 3 + month_2_day + day ;
			break;
		case 11 :
			pass_day = 31 * 6 + 30 * 3 + month_2_day + day ;
			break;
		case 12 :
			pass_day = 31 * 6 + 30 * 4 + month_2_day + day ;
			break;	
		default : break;
	}
		
	pass_day += (year - 1980) * 365 + leap_year - 5;
	
	*week_num = pass_day / 7;
	week_day = pass_day % 7;
	
	if(week_day == 0)
	{
		week_day = 7;
	}
	
	*week_s = (TpUint32)(((week_day - 1)*24*3600 + hour*3600 + minute*60 + second + 0.05) *10) * 100;
}

TpDouble Ddmmtodegree(TpDouble dm_degree)
{
	TpUint32 degree_int;
	TpDouble degree_double;
	
	TpUint32 degree_degree;
	TpUint32 degree_minute;
	TpDouble degree_second;
	
	degree_int = (TpUint32)dm_degree;

	degree_degree = degree_int / 100;
	degree_minute = degree_int % 100;
	degree_second = dm_degree - degree_int;
	
	degree_double = degree_degree + (degree_minute + degree_second) / 60;
	
	return degree_double;
}
