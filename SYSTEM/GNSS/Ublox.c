#include "Ublox.h"
#include "Delay.h"

/*UBLOX Receiver Description P-121*/
void Ublox_check(uint8_t* buff,uint8_t length)
{
	uint32_t check_a = 0;
	uint32_t check_b = 0;
	uint8_t i;
	uint8_t check_length = length - 2;
	
	for(i = 2;i<check_length;i++)
	{
		check_a += buff[i];
		check_b += check_a;
	} 
	
	buff[length - 2] = check_a;
	buff[length - 1] = check_b;	
}

/*
UBLOX Receiver Description P-157

Message[2~7] is the send port
We use the port 2,so we set the Message[3]

Message[3] :
The Effect of the Byte is frequency division
Example: Output rate is 10HZ
	The byte is 1. Message freq is 10HZ
	The byte is 2. Message freq is 5HZ
	The byte is 0. Message freq does not output
*/
Ublox_Message_Config Ublox_Msg;
void UbloxMsgConfig(uint8_t Msg,uint8_t config)
{
	uint8_t command_length;
	
	Ublox_Msg.head[0] 		= UBLOX_HEAD_0;
	Ublox_Msg.head[1] 		= UBLOX_HEAD_1;
	Ublox_Msg.ublox_class = MSG_CLASS;
	Ublox_Msg.ublox_id  	= MSG_ID;
	Ublox_Msg.length 			= MSG_LENGTH;
	Ublox_Msg.Message[0] 	= STANDARD_MSG;	
	Ublox_Msg.Message[3]  = config;
	switch(Msg)
	{
		/*UBLOX Receiver Description P-97*/
		case MSG_GGA_ID: 
							Ublox_Msg.Message[1] = MSG_GGA_ID;break;
		case MSG_GLL_ID: 
							Ublox_Msg.Message[1] = MSG_GLL_ID;break;
		case MSG_GSA_ID: 
							Ublox_Msg.Message[1] = MSG_GSA_ID;break;
		case MSG_GSV_ID: 
							Ublox_Msg.Message[1] = MSG_GSV_ID;break;
		case MSG_RMC_ID: 
							Ublox_Msg.Message[1] = MSG_RMC_ID;break;
		case MSG_VTG_ID: 
							Ublox_Msg.Message[1] = MSG_VTG_ID;break;
		case MSG_GRS_ID: 
							Ublox_Msg.Message[1] = MSG_GRS_ID;break;
		case MSG_GST_ID: 
							Ublox_Msg.Message[1] = MSG_GST_ID;break;
		case MSG_ZDA_ID:
							Ublox_Msg.Message[1] = MSG_ZDA_ID;break;		
		case MSG_GBS_ID: 
							Ublox_Msg.Message[1] = MSG_GBS_ID;break;	
		case MSG_DTM_ID: 
							Ublox_Msg.Message[1] = MSG_DTM_ID;break;
		case MSG_GNS_ID: 
							Ublox_Msg.Message[1] = MSG_GNS_ID;break;
		case MSG_VLW_ID: 
							Ublox_Msg.Message[1] = MSG_VLW_ID;break;
	
		default :break;
	}
	
	command_length = MSG_LENGTH + COMMAND_FIXED_LENGTH;
	Ublox_check((uint8_t*)&Ublox_Msg,command_length);
	
	UbloxCommandSend((uint8_t*)&Ublox_Msg,command_length);
}

Ublox_Baudrate_Config  Ublox_baudrate;
void UbloxBaudrateConfig(void)
{
	uint8_t command_length;
	Ublox_baudrate.head[0] 			= UBLOX_HEAD_0;
	Ublox_baudrate.head[1] 			= UBLOX_HEAD_1;
	Ublox_baudrate.ublox_class 	= CFG_PORT_CLASS;
	Ublox_baudrate.ublox_id  		= CFG_PORT_ID;
	Ublox_baudrate.length 			= CFG_PORT_LENGTH;
	
	Ublox_baudrate.port_id 			= PORT_ID_UART;
	Ublox_baudrate.reserved1 		= 0;
	Ublox_baudrate.txready 			= 0;
	Ublox_baudrate.mode 				= UBLOX_UART_MODE;
	Ublox_baudrate.baudrate 		= UBLOX_UART_BAUDRATE_USER;
	Ublox_baudrate.inProtoMask	=	0x0007;/*ENALBE ALL */	/*UBLOX Receiver Description P-97*/
	Ublox_baudrate.outProtoMask	=	0x0003;/*ENALBE ALL */
	Ublox_baudrate.flag 				= 0;
	Ublox_baudrate.reserved2 		= 0;
	
	command_length = CFG_PORT_LENGTH + COMMAND_FIXED_LENGTH;
	Ublox_check((uint8_t*)&Ublox_baudrate,command_length);
	
	UbloxCommandSend((uint8_t*)&Ublox_baudrate,command_length);
}

Ublox_Rate_Config Ublox_Rate;
void UbloxRateConfig(void)
{
	uint8_t command_length;
	Ublox_Rate.head[0] 			= UBLOX_HEAD_0;
	Ublox_Rate.head[1] 			= UBLOX_HEAD_1;
	Ublox_Rate.ublox_class 	= RATE_CLASS;
	Ublox_Rate.ublox_id  		= RATE_ID;
	Ublox_Rate.length 			= RATE_LENGTH;
	
	Ublox_Rate.measrate 		= UBLOX_RATE;
	Ublox_Rate.navrate			= NAV_RATE_RATIO;
	Ublox_Rate.timeref			= SYSTEM_TIME;
	
	command_length = RATE_LENGTH + COMMAND_FIXED_LENGTH;
	Ublox_check((uint8_t*)&Ublox_Rate,command_length);
	
	UbloxCommandSend((uint8_t*)&Ublox_Rate,command_length);
}

Ublox_CFG_NMEA ublox_cfg_nmea;
void Ublox_NMEA_Config(void)
{
	uint8_t command_length;
	ublox_cfg_nmea.head[0] 			= UBLOX_HEAD_0;
	ublox_cfg_nmea.head[1] 			= UBLOX_HEAD_1;
	ublox_cfg_nmea.ublox_class 	= CFG_NMEA_CLASS;
	ublox_cfg_nmea.ublox_id  		= CFG_NMEA_ID;
	ublox_cfg_nmea.length 			= CFG_NMEA_LENGTH;
	
  ublox_cfg_nmea.filter_flag = 0x0f;
	ublox_cfg_nmea.nmeaVersion = CFG_NMEA_VERSION;
	ublox_cfg_nmea.numSV = 0;
	ublox_cfg_nmea.flag = 0;
	ublox_cfg_nmea.gnssToFilter = 0;
	ublox_cfg_nmea.svNumbering = 0;
	ublox_cfg_nmea.mainTalkerId = HEAD_ID;
	ublox_cfg_nmea.gsvTalkerId = 1;
	ublox_cfg_nmea.version = 1;
	ublox_cfg_nmea.bdsTalkerId = 0;
	ublox_cfg_nmea.reserved1[0] = 0;
	
	command_length = 20 + COMMAND_FIXED_LENGTH;
	Ublox_check((uint8_t*)&ublox_cfg_nmea,command_length);
	
	UbloxCommandSend((uint8_t*)&ublox_cfg_nmea,command_length);
}

void UbloxInit(void)
{
	UsartConfig(GetUsartAddress(USART_1),USART_1,UBLOX_UART_DEFAULT);
	Delay_ms(250);
	UbloxBaudrateConfig();
	Delay_ms(250);	
	
	UsartConfig(GetUsartAddress(USART_1),USART_1,UBLOX_UART_BAUDRATE_USER);
	Delay_ms(250);	
	
	UbloxRateConfig();
	Delay_ms(50);
	
	Ublox_NMEA_Config();
	Delay_ms(50);

	UbloxMsgConfig(MSG_GGA_ID,MSG_GGA_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GLL_ID,MSG_GLL_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GSA_ID,MSG_GSA_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GSV_ID,MSG_GSV_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_RMC_ID,MSG_RMC_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_VTG_ID,MSG_VTG_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GRS_ID,MSG_GRS_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GST_ID,MSG_GST_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_ZDA_ID,MSG_ZDA_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GBS_ID,MSG_GBS_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_DTM_ID,MSG_DTM_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_GNS_ID,MSG_GNS_RATE_RADIO);
	Delay_ms(50);	
	UbloxMsgConfig(MSG_VLW_ID,MSG_VLW_RATE_RADIO);
	
}

