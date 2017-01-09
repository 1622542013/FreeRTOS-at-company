/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   ublox.h                                                      */
/* Date:        2016.8.5                                                     */
/* Description:                                                              */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#ifndef __UMI_UBLOX_H__
#define __UMI_UBLOX_H__


#include <string.h>
#include "usart.h"



/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

typedef struct
{
	TpUint32 GNGGA;
	TpUint32 GNRMC;
	TpUint32 GNVTG;
	TpUint32 GNGSA;
	TpUint32 GNGSV;
	TpUint32 GNGLL;
	TpUint32 GNGRS;
	TpUint32 GNGST;
	TpUint32 GNZDA;
	TpUint32 GNGBS;
	TpUint32 GNDTM;
	TpUint32 GNGNS;
	TpUint32 GNVLW;
	
	TpUint32 Output_Rate;	
	TpUint32 GPS_Upload;
	
}Ublox;


void Ublox_Init(Ublox* ub);
void Ublox_Config(uint8_t* data, Ublox* ub);
void Command_Reply(char *ReplyBuffer, uint16_t BufferNum);
void Command_Pass(uint8_t *ReplyBuffer, uint16_t BufferNum);
void Out_Config_OK(void);
void Out_Command_Bad(void);
void Ublox_GNGGA_ON(void);
void Ublox_GNGGA_OFF(void);
void Ublox_GNRMC_ON(void);
void Ublox_GNRMC_OFF(void);
void Ublox_GNVTG_ON(void);
void Ublox_GNVTG_OFF(void);
void Ublox_GNGSA_ON(void);
void Ublox_GNGSA_OFF(void);
void Ublox_GNGSV_ON(void);
void Ublox_GNGSV_OFF(void);
void Ublox_GNGLL_ON(void);
void Ublox_GNGLL_OFF(void);
void Ublox_GNGRS_ON(void);
void Ublox_GNGRS_OFF(void);
void Ublox_GNGST_ON(void);
void Ublox_GNGST_OFF(void);
void Ublox_GNZDA_ON(void);
void Ublox_GNZDA_OFF(void);
void Ublox_GNGBS_ON(void);
void Ublox_GNGBS_OFF(void);
void Ublox_GNDTM_ON(void);
void Ublox_GNDTM_OFF(void);
void Ublox_GNGNS_ON(void);
void Ublox_GNGNS_OFF(void);
void Ublox_GNVLW_ON(void);
void Ublox_GNVLW_OFF(void);
void Ublox_Output_Rate_1Hz(void);
void Ublox_Output_Rate_2Hz(void);
void Ublox_Output_Rate_4Hz(void);
void Ublox_Output_Rate_5Hz(void);
void Ublox_Baudrate(void);
void Ublox_SAVE(void);


#endif 	//__UBLOX_H
