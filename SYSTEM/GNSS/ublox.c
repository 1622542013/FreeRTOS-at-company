/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   ublox.c                                                      */
/* Date:        2016.7.25                                                     */
/* Description:                                                              */
/*============================================================================*/

#include "ublox.h"
#include "config.h"

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

void Ublox_Init(Ublox* ub)
{
	if(ub->Output_Rate==5)
		Ublox_Output_Rate_5Hz();
	else if(ub->Output_Rate==4)
		Ublox_Output_Rate_4Hz();
	else if(ub->Output_Rate==2)
		Ublox_Output_Rate_2Hz();
	else if(ub->Output_Rate==1)
		Ublox_Output_Rate_1Hz();
	
	if(ub->GNDTM)
		Ublox_GNDTM_ON();
	else
		Ublox_GNDTM_OFF();
	
	if(ub->GNGBS)
		Ublox_GNGBS_ON();
	else
		Ublox_GNGBS_OFF();
	
	if(ub->GNGGA)
		Ublox_GNGGA_ON();
	else
		Ublox_GNGGA_OFF();
	
	if(ub->GNGLL)
		Ublox_GNGLL_ON();
	else
		Ublox_GNGLL_OFF();
	
	if(ub->GNGNS)
		Ublox_GNGNS_ON();
	else
		Ublox_GNGNS_OFF();
	
	if(ub->GNGRS)
		Ublox_GNGRS_ON();
	else
		Ublox_GNGRS_OFF();
	
	if(ub->GNGSA)
		Ublox_GNGSA_ON();
	else
		Ublox_GNGSA_OFF();
	
	if(ub->GNGST)
		Ublox_GNGST_ON();
	else
		Ublox_GNGST_OFF();
	
	if(ub->GNGSV)
		Ublox_GNGSV_ON();
	else
		Ublox_GNGSV_OFF();
	
	if(ub->GNRMC)
		Ublox_GNRMC_ON();
	else
		Ublox_GNRMC_OFF();
	
	if(ub->GNVLW)
		Ublox_GNVLW_ON();
	else
		Ublox_GNVLW_OFF();
	
	if(ub->GNVTG)
		Ublox_GNVTG_ON();
	else
		Ublox_GNVTG_OFF();
	
	if(ub->GNZDA)
		Ublox_GNZDA_ON();
	else
		Ublox_GNZDA_OFF();
	
	Ublox_Baudrate();
	
	
}

void Ublox_Config(uint8_t* data, Ublox* ub)
{
	if(!memcmp("$cmd,ublox,gngga,on", data, 19))
	{
		ub->GNGGA = 1;
		Ublox_GNGGA_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngga,off", data, 20))
	{
		ub->GNGGA = 0;
		Ublox_GNGGA_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnrmc,on", data, 19))
	{
		ub->GNRMC = 1;
		Ublox_GNRMC_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnrmc,off", data, 20))
	{
		ub->GNRMC = 0;
		Ublox_GNRMC_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnvtg,on", data, 19))
	{
		ub->GNVTG = 1;
		Ublox_GNVTG_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnvtg,off", data, 20))
	{
		ub->GNVTG = 0;
		Ublox_GNVTG_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngsa,on", data, 19))
	{
		ub->GNGSA = 1;
		Ublox_GNGSA_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngsa,off", data, 20))
	{
		ub->GNGSA = 0;
		Ublox_GNGSA_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngsv,on", data, 19))
	{
		ub->GNGSV = 1;
		Ublox_GNGSV_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngsv,off", data, 20))
	{
		ub->GNGSV = 0;
		Ublox_GNGSV_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngll,on", data, 19))
	{
		ub->GNGLL = 1;
		Ublox_GNGLL_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngll,off", data, 20))
	{
		ub->GNGLL = 0;
		Ublox_GNGLL_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngrs,on", data, 19))
	{
		ub->GNGRS = 1;
		Ublox_GNGRS_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngrs,off", data, 20))
	{
		ub->GNGRS = 0;
		Ublox_GNGRS_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngst,on", data, 19))
	{
		ub->GNGST = 1;
		Ublox_GNGST_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngst,off", data, 20))
	{
		ub->GNGST = 0;
		Ublox_GNGST_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnzda,on", data, 19))
	{
		ub->GNZDA = 1;
		Ublox_GNZDA_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnzda,off", data, 20))
	{
		ub->GNZDA = 0;
		Ublox_GNZDA_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngbs,on", data, 19))
	{
		ub->GNGBS = 1;
		Ublox_GNGBS_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngbs,off", data, 20))
	{
		ub->GNGBS = 0;
		Ublox_GNGBS_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gndtm,on", data, 19))
	{
		ub->GNDTM = 1;
		Ublox_GNDTM_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gndtm,off", data, 20))
	{
		ub->GNDTM = 0;
		Ublox_GNDTM_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngns,on", data, 19))
	{
		ub->GNGNS = 1;
		Ublox_GNGNS_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gngns,off", data, 20))
	{
		ub->GNGNS = 0;
		Ublox_GNGNS_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnvlw,on", data, 19))
	{
		ub->GNVLW = 1;
		Ublox_GNVLW_ON();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gnvlw,off", data, 20))
	{
		ub->GNVLW = 0;
		Ublox_GNVLW_OFF();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,output_rate,5Hz", data, 26))
	{
		ub->Output_Rate = 5;
		Ublox_Output_Rate_5Hz();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,output_rate,4Hz", data, 26))
	{
		ub->Output_Rate = 4;
		Ublox_Output_Rate_4Hz();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,output_rate,2Hz", data, 26))
	{
		ub->Output_Rate = 2;
		Ublox_Output_Rate_2Hz();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,output_rate,1Hz", data, 26))
	{
		ub->Output_Rate = 1;
		Ublox_Output_Rate_1Hz();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,save", data, 15))
	{
		Ublox_SAVE();
		Out_Config_OK();
	}
	else if(!memcmp("$cmd,ublox,gps_upload,on", data, 24))
	{
		Out_Config_OK();
		ub->GPS_Upload = 1;
	}
	else if(!memcmp("$cmd,ublox,gps_upload,off", data, 25))
	{
		Out_Config_OK();
		ub->GPS_Upload = 0;
	}
	else
		Out_Command_Bad();
}

void Command_Reply(char *ReplyBuffer, uint16_t BufferNum)
{
	uint16_t i;
	
//	while(DMA_GetFlagStatus(DMA1_Stream6, DMA_FLAG_TCIF6)==0);
  
  memset(usart2.cb.send_buf, 0, BUFSIZE_USART1);	//清空内存
	
	for(i=0; i<BufferNum; i++)
	{
		usart2.cb.send_buf[i] = ReplyBuffer[i];
	}
	
//  UsartSend(&usart2,BufferNum);
	
}

void Command_Pass(uint8_t *ReplyBuffer, uint16_t BufferNum)
{
	uint16_t i;
	
	while(DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7)==0);

//	memset(usart1.cb.send_buf, 0, BUFSIZE_USART1);	//清空内存
//	
//	for(i=0; i<BufferNum; i++)
//	{
//		usart1.cb.send_buf[i] = ReplyBuffer[i];
//	}
	
	UsartPushSendBuf(&usart1,ReplyBuffer,BufferNum,0);
	
	UsartSend(&usart1);

//	Delay_ms(5);

}


/*******************************************************************************
* 函数名称  : Out_Config_OK
* 描述      : 输出设置成功提示语句
* 输入      : 无
* 输出		: $cmd,Config,OK*ff
* 返回      : 无
*******************************************************************************/
void Out_Config_OK(void)
{
	Command_Reply("$cmd,Config,OK*ff\r\n", 19);
}


/*******************************************************************************
* 函数名称  : Out_Command_Bad
* 描述      : 输出错误命令提示语句
* 输入      : 无
* 输出		: $cmd,Bad,Command*ff
* 返回      : 无
*******************************************************************************/
void Out_Command_Bad(void)
{
	Command_Reply("$cmd,Bad,Command*ff\r\n", 21);
}


void Ublox_GNGGA_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[9] = 0x01;
	data[15] = 0x28;
	
	Command_Pass(data, 16);
}


void Ublox_GNGGA_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[14] = 0xFF;
	data[15] = 0x23;
	
	Command_Pass(data, 16);
}


void Ublox_GNRMC_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x04;
	data[9] = 0x01;
	data[14] = 0x04;
	data[15] = 0x44;
	
	Command_Pass(data, 16);
}


void Ublox_GNRMC_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x04;
	data[14] = 0x03;
	data[15] = 0x3F;
	
	Command_Pass(data, 16);
}


void Ublox_GNVTG_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x05;
	data[9] = 0x01;
	data[14] = 0x05;
	data[15] = 0x4B;
	
	Command_Pass(data, 16);
}


void Ublox_GNVTG_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x05;
	data[14] = 0x04;
	data[15] = 0x46;
	
	Command_Pass(data, 16);
}


void Ublox_GNGSA_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x02;
	data[9] = 0x01;
	data[14] = 0x02;
	data[15] = 0x36;
	
	Command_Pass(data, 16);
}


void Ublox_GNGSA_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x02;
	data[14] = 0x01;
	data[15] = 0x31;
	
	Command_Pass(data, 16);
}


void Ublox_GNGSV_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x03;
	data[9] = 0x01;
	data[14] = 0x03;
	data[15] = 0x3D;
	
	Command_Pass(data, 16);
}


void Ublox_GNGSV_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x03;
	data[14] = 0x02;
	data[15] = 0x38;
	
	Command_Pass(data, 16);
}


void Ublox_GNGLL_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x01;
	data[9] = 0x01;
	data[14] = 0x01;
	data[15] = 0x2F;
	
	Command_Pass(data, 16);
}


void Ublox_GNGLL_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x01;
	data[15] = 0x2A;
	
	Command_Pass(data, 16);
}


void Ublox_GNGRS_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x06;
	data[9] = 0x01;
	data[14] = 0x06;
	data[15] = 0x52;
	
	Command_Pass(data, 16);
}


void Ublox_GNGRS_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x06;
	data[14] = 0x05;
	data[15] = 0x4D;
	
	Command_Pass(data, 16);
}


void Ublox_GNGST_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x07;
	data[9] = 0x01;
	data[14] = 0x07;
	data[15] = 0x59;
	
	Command_Pass(data, 16);
}


void Ublox_GNGST_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x07;
	data[14] = 0x06;
	data[15] = 0x54;
	
	Command_Pass(data, 16);
}


void Ublox_GNZDA_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x08;
	data[9] = 0x01;
	data[14] = 0x08;
	data[15] = 0x60;
	
	Command_Pass(data, 16);
}


void Ublox_GNZDA_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x08;
	data[14] = 0x07;
	data[15] = 0x5B;
	
	Command_Pass(data, 16);
}


void Ublox_GNGBS_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x09;
	data[9] = 0x01;
	data[14] = 0x09;
	data[15] = 0x67;
	
	Command_Pass(data, 16);
}


void Ublox_GNGBS_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x09;
	data[14] = 0x08;
	data[15] = 0x62;
	
	Command_Pass(data, 16);
}


void Ublox_GNDTM_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0A;
	data[9] = 0x01;
	data[14] = 0x0A;
	data[15] = 0x6E;
	
	Command_Pass(data, 16);
}


void Ublox_GNDTM_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0A;
	data[14] = 0x09;
	data[15] = 0x69;
	
	Command_Pass(data, 16);
}


void Ublox_GNGNS_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0D;
	data[9] = 0x01;
	data[14] = 0x0D;
	data[15] = 0x83;
	
	Command_Pass(data, 16);
}


void Ublox_GNGNS_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0D;
	data[14] = 0x0C;
	data[15] = 0x7E;
	
	Command_Pass(data, 16);
}


void Ublox_GNVLW_ON(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0F;
	data[9] = 0x01;
	data[14] = 0x0F;
	data[15] = 0x91;
	
	Command_Pass(data, 16);
}


void Ublox_GNVLW_OFF(void)
{
	uint8_t data[16]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x01;
	data[4] = 0x08;
	data[6] = 0xF0;
	data[7] = 0x0F;
	data[14] = 0x0E;
	data[15] = 0x8C;
	
	Command_Pass(data, 16);
}


void Ublox_Output_Rate_1Hz(void)
{
	uint8_t data[14]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x08;
	data[4] = 0x06;
	data[6] = 0xE8;
	data[7] = 0x03;
	data[8] = 0x01;
	data[10] = 0x01;
	data[12] = 0x01;
	data[13] = 0x39;
	
	Command_Pass(data, 14);
}


void Ublox_Output_Rate_2Hz(void)
{
	uint8_t data[14]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x08;
	data[4] = 0x06;
	data[6] = 0xF4;
	data[7] = 0x01;
	data[8] = 0x01;
	data[10] = 0x01;
	data[12] = 0x0B;
	data[13] = 0x77;
	
	Command_Pass(data, 14);
}


void Ublox_Output_Rate_4Hz(void)
{
	uint8_t data[14]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x08;
	data[4] = 0x06;
	data[6] = 0xFA;
	data[8] = 0x01;
	data[10] = 0x01;
	data[12] = 0x10;
	data[13] = 0x96;
	
	Command_Pass(data, 14);
}


void Ublox_Output_Rate_5Hz(void)
{
	uint8_t data[14]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x08;
	data[4] = 0x06;
	data[6] = 0xC8;
	data[8] = 0x01;
	data[10] = 0x01;
	data[12] = 0xDE;
	data[13] = 0x6A;
	
	Command_Pass(data, 14);
}

//波特率115200
void Ublox_Baudrate(void)
{
	uint8_t data[28]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[4] = 0x14;
	data[6] = 0x01;
	data[10] = 0xD0;
	data[11] = 0x08;
	data[15] = 0xC2;
	data[16] = 0x01;
	data[18] = 0x07;
	data[20] = 0x03;
	data[26] = 0xC0;
	data[27] = 0x7E;
	
	Command_Pass(data, 28);
}


void Ublox_SAVE(void)
{
	uint8_t data[21]={0};
	
	data[0] = 0xB5;
	data[1] = 0x62;
	data[2] = 0x06;
	data[3] = 0x09;
	data[4] = 0x0D;
	data[10] = 0xFF;
	data[11] = 0xFF;
	data[18] = 0x03;
	data[19] = 0x1D;
	data[20] = 0xAB;
	
	Command_Pass(data, 21);
}
