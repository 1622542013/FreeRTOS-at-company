#include <stdint.h>

typedef unsigned char bool;

/* ÈÎÒâÎ¬¾ØÕóÏà³Ë */
void MulMatxxd(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const unsigned int uc8Dim3, const double dMat_i1[], const double dMat_i2[], double dMat_o[]);

/* ¾ØÕóÇóÄæ  */
unsigned char InvMatxd(const unsigned int n, double a[]);

/** ¾ØÕóÇó×ªÖÃ ****/
void RotMatxxd(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const double dMat[], double dRotMat[]);
/** ¾ØÕóÏà¼õ ****/
void SubMatxxd(const unsigned int uc16Dim1, const unsigned int uc16Dim2, const double dMat_i1[], const double dMat_i2[], double dMat_o[]);

/******************************************   float    **************************************************************/
void MulMatxxf(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const unsigned int uc8Dim3, const float fMat_i1[], const float fMat_i2[], float fMat_o[]);
unsigned char InvMatxf(const unsigned int n, float a[]);
/** ¾ØÕóÇó×ªÖÃ ****/
void RotMatxxf(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const float fMat[], float fRotMat[]);
/** ¾ØÕóÏà¼õ ****/
void SubMatxxf(const unsigned int uc16Dim1, const unsigned int uc16Dim2, const float fMat_i1[], const float fMat_i2[], float fMat_o[]);
void SetMatxxEye(const unsigned int Dim, float fMat[]);
void SetMatxxZero(const unsigned int Dim, float fMat[]);
void SetMatxxinverse(const float fVec[3], float fMat[]);

/********************************************************/


void SetQuatf(const float fVecQi[4], float fVecQo[4]);
void SetMat3f(const float fMat_i[9], float fMat_o[9]);
void Att2Quat(const float att[3],float quat[4]);
void Att2Cnb(const float att[3],float Cnb[9]);

void Quat2Dcm(const float quat[4], float Dcm[9]);
void Dcm2Euler(const float Dcm[9], float att[3]);

float LengthVec3f(const float fVec3[3]);
// 
void MulCbnVec3(const float cbn[9],const float vec[3],float out[3]);

void VecCross(const float vec1[3],const float vec2[3],float out[3]);

void RotVec2Quat(const float rot_vec[3], float quat[4]);

void MulQuatf(const float fVecQ1[4], const float fVecQ2[4], float fVecQo[4]);
