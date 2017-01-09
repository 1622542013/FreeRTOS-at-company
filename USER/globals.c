/*============================================================================*/
/* Copyright (C), 2016, Yagro Co., Ltd.                                       */
/* File name:   user_define.c                                                         */
/* Date:        2016.7.21                                                     */
/* Description:                                                              */
/*============================================================================*/

/*============================================================================*/
/*                               Header include                               */
/*============================================================================*/

#include "globals.h"
#include "definition.h"

/*============================================================================*/
/*                              Global variables                              */
/*============================================================================*/

UmiOutput st_UmiOutput;
UmiOutIMU st_UmiOutIMU;
UmiMagSend    umiMagSend;

/*  add for 54 suo */
#ifdef UMI_SATCOM_FORMAT
SatComYawInit    satComYawInit;
SatComYawUpdate  satComYawUpdate;
SatComYawFlag    satComYawFlag;
SatComImuOut     satComImuOut;
SatComPosOut     satComPosOut;
SatComOverRange  satComOverRange;
#endif

/* out pitch and roll */
TpUchar outgps_flag = 1;
TpUchar outimu_flag = 0;
TpUchar outimu_len = 0;
TpUchar outimu_buf[50] = {0};

TpUchar outmis_flag = 0;
TpUchar rec_reply = 0;

TpUchar flag_throughgps = 0;
TpUint32 logtimer = 0;


/*============================================================================*/
/*                              Global functions                              */
/*============================================================================*/

