#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include "command.h"
#include "command_bin.h"
#include "globals.h"

#define ACC_CAL_PARA_OUT    ("$cmd,get,acc_cal_para,\
kas0,%f,%f,%f,\
kas1,%f,%f,%f,\
kaz0,%f,%f,%f,\
kaz1,%f,%f,%f,\
accn0,%f,%f,%f,\
accn1,%f,%f,%f,\
accn2,%f,%f,%f,*ff\r\n")

#define GYRO_CAL_PARA_OUT    ("$cmd,get,gyro_cal_para,\
kgs0,%f,%f,%f,\
kgs1,%f,%f,%f,\
kgz0,%f,%f,%f,\
kgz1,%f,%f,%f,\
gyron0,%f,%f,%f,\
gyron1,%f,%f,%f,\
gyron2,%f,%f,%f,*ff\r\n")

#define BENCHMARK_FREQ   OUTPUT_RATE_MAX

/* output  */
TpVoid LogOutput(UmiIgmBin* pUmiOutput);
TpVoid LogImuAscii(UmiIgmBin* pUmiOutput);
TpVoid LogAhrsAscii(UmiIgmBin* pUmiOutput);
TpVoid LogAhrsBin(UmiIgmBin* pUmiOutput);
TpVoid LogIgmAscii(UmiIgmBin* pUmiOutput);
TpVoid LogIgmBin(UmiIgmBin* pUmiOutput);

TpVoid AccCalPara(Commond_ACC_GYRO_PARA* acc_para);
TpVoid GyroCalPara(Commond_ACC_GYRO_PARA* gyro_para);
#endif
