#ifndef __UBLOX_H
#define __UBLOX_H

#include <string.h>
#include "stm32f4xx.h"
#include "USART.h"

#define UbloxCommandSend(buff,length);  UsartSendImmediately(GetUsartAddress(USART_1),buff,length);

/*-----------------------------------------------------------------------------*/
/***********************Common parameter definition*****************************/
/*-----------------------------------------------------------------------------*/
#define UBLOX_RATE										UBLOX_RATE_5HZ
#define	UBLOX_UART_DEFAULT						9600
#define	UBLOX_UART_BAUDRATE_USER			115200

/*output radio by UBLOX_RATE*/
/*example : 
						UBLOX_RATE is 10hz, xx_RATE_RADIO 	is 1,xx RATE is 10hz 
						UBLOX_RATE is 10hz, xx_RATE_RADIO 	is 2,xx RATE is 5hz 
						UBLOX_RATE is 10hz, xx_RATE_RADIO 	is 0,xx RATE is 0hz(do not output!)
*/
#define MSG_GGA_RATE_RADIO							1
#define MSG_GLL_RATE_RADIO							0
#define MSG_GSA_RATE_RADIO							0
#define MSG_GSV_RATE_RADIO							0
#define MSG_RMC_RATE_RADIO							1
#define MSG_VTG_RATE_RADIO							0
#define MSG_GRS_RATE_RADIO							0
#define MSG_GST_RATE_RADIO							0
#define MSG_ZDA_RATE_RADIO							0
#define MSG_GBS_RATE_RADIO							0
#define MSG_DTM_RATE_RADIO							0
#define MSG_GNS_RATE_RADIO							0
#define MSG_VLW_RATE_RADIO							0


#define UBLOX_HEAD_0		0xB5
#define UBLOX_HEAD_1		0x62

/*
Command Format:
head_0 	head_1 	class 	ID 			length 	message 	check_a 	check_b
1byte  	1byte  	1byte 	1byte 	2bytes 	no fixed  1byte   	1byte
*/
#define COMMAND_FIXED_LENGTH	 8 /*Command length except message*/

#define MSG_CLASS				0X06
#define MSG_ID					0X01
#define MSG_LENGTH			8

/*UBLOX Receiver Description P-97*/
#define STANDARD_MSG		0XF0

#define MSG_GGA_ID							0x00
#define MSG_GLL_ID							0x01
#define MSG_GSA_ID							0x02
#define MSG_GSV_ID							0x03
#define MSG_RMC_ID							0x04
#define MSG_VTG_ID							0x05
#define MSG_GRS_ID							0x06
#define MSG_GST_ID							0x07
#define MSG_ZDA_ID							0x08
#define MSG_GBS_ID							0x09

#define MSG_DTM_ID							0x0A
#define MSG_GNS_ID							0x0D
#define MSG_VLW_ID							0x0F


/*UBLOX Receiver Description P-30*/

/*UBLOX PORT CONFIG	*/

#define PORT_ID_IIC							0x00
#define PORT_ID_UART						0x01
#define PORT_ID_USB							0x03
#define PORT_ID_SPI							0x04

#define CFG_PORT_CLASS					0X06
#define CFG_PORT_ID							0X00
#define CFG_PORT_LENGTH					20

#define BITE_8									3			/*0b11*/
#define BITE_7									2			/*0b10 supported only with parity*/

#define EVEN_PARITY							0			/*0b000*/
#define ODD_PARITY							1			/*0b001*/
#define NO_PARITY								4			/*0b100*/

#define STOP_BITE_1							0			/*0b00		1 	Stop Bit*/
#define STOP_BITE_1_5						1			/*0b01		1.5 Stop Bit*/
#define STOP_BITE_2							2			/*0b10		2 	Stop Bit*/
#define STOP_BITE_0_5						3			/*0b11		0.5 Stop Bit*/

#define BITE										BITE_8
#define PARITY									NO_PARITY
#define STOP_BITE								STOP_BITE_1
#define UBLOX_UART_MODE					(BITE<<6)|(PARITY<<9)|(STOP_BITE)



#define RATE_CLASS							0X06
#define RATE_ID									0X08
#define RATE_LENGTH							6

/*measurements rate cycle,unit is ms*/
/*Here are a few examples*/
#define UBLOX_RATE_0_1HZ        10000/*0.1hz*/
#define UBLOX_RATE_1HZ					1000
#define UBLOX_RATE_2HZ					500
#define UBLOX_RATE_5HZ					200
#define UBLOX_RATE_10HZ					100



/*The ratio between the number of	measurements and the number of navigation	solutions*/
/*MAX : 127	*/
#define NAV_RATE_RATIO					1

/*----SYSTEM_TIME-----*/
#define UTC_TIME								0
#define	GPS_TIME								1
#define	GLONASS_TIME						2
#define	BEIDOU_TIME 						3
#define	GALILEO_TIME						4

#define SYSTEM_TIME							GPS_TIME

/*--------------------- UBLOX NMEA CFG -------------------------*/
#define CFG_NMEA_CLASS					0x06		
#define CFG_NMEA_ID							0x17
#define CFG_NMEA_LENGTH					20

#define CFG_NMEA_VERSION				0x23
							
#define HEAD_ID_GP							1
#define HEAD_ID_GL							2
#define HEAD_ID_GN							3
#define HEAD_ID_GA							4
#define HEAD_ID_GB							5

#define HEAD_ID									HEAD_ID_GP


#pragma pack(push)
#pragma pack(1)
typedef struct
{
	uint8_t 	head[2];
	uint8_t 	ublox_class;
	uint8_t		ublox_id;
	uint16_t  length;
	
	uint8_t 	Message[8];	/*include message check_a check_b*/
	
	uint8_t   check_a;
	uint8_t   check_b;
}Ublox_Message_Config;

typedef struct
{
	uint8_t 	head[2];
	uint8_t 	ublox_class;
	uint8_t		ublox_id;
	uint16_t  length;
	
	uint8_t 	port_id;
	
	uint8_t		reserved1;
	uint16_t	txready;
	
	uint32_t	mode;
	uint32_t  baudrate;
	uint16_t	inProtoMask;
	uint16_t	outProtoMask;
	uint16_t	flag;
	uint16_t  reserved2;
	
	uint8_t   check_a;
	uint8_t   check_b;
}Ublox_Baudrate_Config;

typedef struct
{
	uint8_t 	head[2];
	uint8_t 	ublox_class;
	uint8_t		ublox_id;
	uint16_t  length;
	
	uint16_t 	measrate;	/*include message check_a check_b*/
	uint16_t  navrate;
	uint16_t  timeref;
	
	uint8_t   check_a;
	uint8_t   check_b;
}Ublox_Rate_Config;


typedef struct
{
	uint8_t 	head[2];
	uint8_t 	ublox_class;
	uint8_t		ublox_id;
	uint16_t  length;
	
  char 			filter_flag;
	uint8_t   nmeaVersion;
	uint8_t   numSV;
	char			flag;
	int     	gnssToFilter;
	uint8_t   svNumbering;
	uint8_t   mainTalkerId;
	uint8_t   gsvTalkerId;
	uint8_t   version;
	uint16_t  bdsTalkerId;
	uint8_t   reserved1[6];
	
	uint8_t   check_a;
	uint8_t   check_b;
}Ublox_CFG_NMEA;

#pragma pack(pop)

void UbloxInit(void);

#endif 	//__UBLOX_H
