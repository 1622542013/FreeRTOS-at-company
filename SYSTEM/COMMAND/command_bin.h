#ifndef COMMAND_BIN_H
#define COMMAND_BIN_H

#include "globals.h"

#define COMMAND_BIN_HEAD0					0xA5
#define COMMAND_BIN_HEAD1					0x5A
#define COMMAND_BIN_END						0XFE

#define FRAME_ID_SET							0X01
#define FRAME_ID_GET           		0X02
#define FRAME_ID_OUTPUT           0X03

#define COMMAND_ID_SAVE								0XA000
#define COMMAND_ID_SETTING_RESTORE		0XA001

/*freedback for set command*/
#define COMMAND_ID_CONFIG_OK				0XB000
#define COMMAND_ID_CONFIG_ERROR			0XB001

#define COMMAND_ID_ACC_PARA									0X0001
#define COMMAND_ID_GYRO_PARA 								0X0002
#define COMMAND_ID_ERASE_ACC_GYRO_PARA			0X0003
#define COMMAND_ID_NAV_MODE									0X0004
#define COMMAND_ID_LEVEARM									0X0005
#define COMMAND_ID_SET_OK										0XAAAA

#define DATA_LAND_MODE						0X0001
#define DATA_AIR_MODE							0X0002
#define DATA_OCEAN_MODE						0X0003

#define ks0_location		5		
#define ks1_location    9
#define kz0_location 		13
#define kz1_location 		17
#define n0_location 		21
#define n1_location 		25
#define n2_location 		29



#define Commond_ACC_GYRO_PARA_SIZE      sizeof(Commond_ACC_GYRO_PARA)
#define Commond_BIN_SIZE								sizeof(Commond_Bin)
	
#pragma pack(push)
#pragma pack(1)

typedef struct
{
	TpUchar  	head[2];
	TpUchar  	frame_id;
	TpUint16  command_id;
	TpUint16  length;
	
	union
	{
		TpUint32  udata;
		float     fdata;
	}data;

	TpUchar   check;
	TpUchar   end;
}Commond_Bin;

typedef struct
{
	TpUchar  	head[2];
	TpUchar  	frame_id;
	TpUint16  command_id;
	TpUint16  length;
	
}Decode_Commond_Bin;

typedef struct
{
	TpUchar  	head[2];
	TpUchar  	frame_id;
	TpUint16  command_id;
	TpUint16  length;
	
	TpFloat   ks0[3];
	TpFloat   ks1[3];
	TpFloat   kz0[3];
	TpFloat   kz1[3];
	
	TpFloat   n0[3];
	TpFloat   n1[3];
	TpFloat   n2[3];
	
	TpUchar   check;
	TpUchar   end;
}Commond_ACC_GYRO_PARA;

#pragma pack(pop)

TpChar* PackAccPara(TpChar* buff_processed[],TpUint16 command_id);
TpChar* CommondBin(TpChar frame_id,TpUint16 command_id,TpUint32 data);
TpVoid DecodeCommondBin(TpUchar* commnd_bin,TpUint16 length);

#endif
