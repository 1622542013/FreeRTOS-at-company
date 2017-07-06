#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define  _PI_F  3.1415926535897932f 

void MulMatxxd(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const unsigned int uc8Dim3, const double dMat_i1[], const double dMat_i2[], double dMat_o[])
{
	unsigned int i, j, k;
	double *matxxd = (double *)malloc(uc8Dim1*uc8Dim3*sizeof(double));

	for (i = 0; i < uc8Dim1; i++)
	{
		for (j = 0; j < uc8Dim3; j++)
		{
			matxxd[i*uc8Dim3 + j] = 0.0f;
			for (k = 0; k < uc8Dim2; k++)
			{
				matxxd[i*uc8Dim3 + j] += dMat_i1[i*uc8Dim2 + k] * dMat_i2[k*uc8Dim3 + j];
			}
		}
	}
	//SetMatxxf(uc8Dim1*uc8Dim3, matxxf, fMat_o);
	memcpy(dMat_o, matxxd, uc8Dim1 * uc8Dim3 * sizeof(double));
	free(matxxd);
}



unsigned char InvMatxd(const unsigned int n, double a[])
{
	int *is, *js, i, j, k, l, u, v;
	double d, p;
	is = malloc(n*sizeof(int));
	js = malloc(n*sizeof(int));

	//int is[n], js[n];

	for (k = 0; k <= n - 1; k++)
	{
		d = 0.0;
		for (i = k; i <= n - 1; i++)
			for (j = k; j <= n - 1; j++)
			{
				l = i*n + j; p = fabs(a[l]);
				if (p > d) { d = p; is[k] = i; js[k] = j; }
			}
		if (d + 1.0 == 1.0)
		{
			free(is); free(js);
			return(0);
		}
		if (is[k] != k)
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j; v = is[k] * n + j;
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		if (js[k] != k)
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k; v = i*n + js[k];
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		l = k*n + k;
		a[l] = 1.0 / a[l];
		for (j = 0; j <= n - 1; j++)
			if (j != k)
			{
				u = k*n + j; a[u] = a[u] * a[l];
			}
		for (i = 0; i <= n - 1; i++)
			if (i != k)
				for (j = 0; j <= n - 1; j++)
					if (j != k)
					{
						u = i*n + j;
						a[u] = a[u] - a[i*n + k] * a[k*n + j];
					}
		for (i = 0; i <= n - 1; i++)
			if (i != k)
			{
				u = i*n + k; a[u] = -a[u] * a[l];
			}
	}
	for (k = n - 1; k >= 0; k--)
	{
		if (js[k] != k)
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j; v = js[k] * n + j;
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		if (is[k] != k)
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k; v = i*n + is[k];
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
	}
	free(is); free(js);
	return(1);
}


void RotMatxxd(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const double dMat[], double dRotMat[])
{
	unsigned int i, j;
	for (i = 0; i < uc8Dim1; i++)
	{
		for (j = 0; j < uc8Dim2; j++)
		{
			dRotMat[j*uc8Dim1 + i] = dMat[i*uc8Dim2 + j];
		}
	}
}

void SubMatxxd(const unsigned int uc16Dim1, const unsigned int uc16Dim2,const double dMat_i1[], const double dMat_i2[], double dMat_o[])
{
	unsigned int i,j;
	for(i=0;i<uc16Dim1;i++)
		for (j = 0; j<uc16Dim2; j++)
	{
 		dMat_o[i*uc16Dim2+j] = dMat_i1[i*uc16Dim2+j] - dMat_i2[i*uc16Dim2 + j];
	}
}
void trmul(double a[], double b[], int m, int n, int k, double c[])
{ int i, j, l, u;
for (i = 0; i <= m - 1; i++)
for (j = 0; j <= k - 1; j++)
{
	u = i*k + j; c[u] = 0.0;
	for (l = 0; l <= n - 1; l++)
		c[u] = c[u] + a[i*n + l] * b[l*k + j];
}
return;
}
 
/********************** float *************************/


void MulMatxxf(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const unsigned int uc8Dim3, const float fMat_i1[], const float fMat_i2[], float fMat_o[])
{
	unsigned int i, j, k;
	float *matxxf = (float *)malloc(uc8Dim1*uc8Dim3*sizeof(float));

	for (i = 0; i < uc8Dim1; i++)
	{
		for (j = 0; j < uc8Dim3; j++)
		{
			matxxf[i*uc8Dim3 + j] = 0.0f;
			for (k = 0; k < uc8Dim2; k++)
			{
				matxxf[i*uc8Dim3 + j] += fMat_i1[i*uc8Dim2 + k] * fMat_i2[k*uc8Dim3 + j];
			}
		}
	}
	//SetMatxxf(uc8Dim1*uc8Dim3, matxxf, fMat_o);
	memcpy(fMat_o, matxxf, uc8Dim1 * uc8Dim3 * sizeof(float));
	free(matxxf);
}


unsigned char InvMatxf(const unsigned int n, float a[])
{
	int *is, *js, i, j, k, l, u, v;
	float d, p;
	is = malloc(n*sizeof(int));
	js = malloc(n*sizeof(int));

	//int is[n], js[n];

	for (k = 0; k <= n - 1; k++)
	{
		d = 0.0f;
		for (i = k; i <= n - 1; i++)
			for (j = k; j <= n - 1; j++)
			{
				l = i*n + j; p = fabs(a[l]);
				if (p > d) { d = p; is[k] = i; js[k] = j; }
			}
		if (d + 1.0f == 1.0f)
		{
			free(is); free(js);
			return(0);
		}
		if (is[k] != k)
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j; v = is[k] * n + j;
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		if (js[k] != k)
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k; v = i*n + js[k];
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		l = k*n + k;
		a[l] = 1.0f / a[l];
		for (j = 0; j <= n - 1; j++)
			if (j != k)
			{
				u = k*n + j; a[u] = a[u] * a[l];
			}
		for (i = 0; i <= n - 1; i++)
			if (i != k)
				for (j = 0; j <= n - 1; j++)
					if (j != k)
					{
						u = i*n + j;
						a[u] = a[u] - a[i*n + k] * a[k*n + j];
					}
		for (i = 0; i <= n - 1; i++)
			if (i != k)
			{
				u = i*n + k; a[u] = -a[u] * a[l];
			}
	}
	for (k = n - 1; k >= 0; k--)
	{
		if (js[k] != k)
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j; v = js[k] * n + j;
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
		if (is[k] != k)
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k; v = i*n + is[k];
				p = a[u]; a[u] = a[v]; a[v] = p;
			}
	}
	free(is); free(js);
	return(1);
}


void RotMatxxf(const unsigned int uc8Dim1, const unsigned int uc8Dim2, const float fMat[], float fRotMat[])
{
	unsigned int i, j;
	for (i = 0; i < uc8Dim1; i++)
	{
		for (j = 0; j < uc8Dim2; j++)
		{
			fRotMat[j*uc8Dim1 + i] = fMat[i*uc8Dim2 + j];
		}
	}
}

void SubMatxxf(const unsigned int uc16Dim1, const unsigned int uc16Dim2, const float fMat_i1[], const float fMat_i2[], float fMat_o[])
{
	unsigned int i, j;
	for (i = 0; i < uc16Dim1; i++)
		for (j = 0; j < uc16Dim2; j++)
		{
			fMat_o[i*uc16Dim2 + j] = fMat_i1[i*uc16Dim2 + j] - fMat_i2[i*uc16Dim2 + j];
		}
}

void SetMatxxEye(const unsigned int Dim, float fMat[])
{
	unsigned int i,j;
	for (i = 0; i < Dim; i++)
		for (j = 0; j < Dim;j++)
	{
		if (i == j)
			fMat[i*Dim + j] = 1.0;
		else
			fMat[i*Dim + j] = 0.0;
	}

}

void SetMatxxZero(const unsigned int Dim, float fMat[])
{
	unsigned int i, j;
	for (i = 0; i < Dim; i++)
		for (j = 0; j < Dim; j++)
		{
			fMat[i*Dim + j] = 0.0;
		}
}

void SetMatxxinverse(const float fVec[3], float fMat[])
{
	fMat[0] = fMat[4] = fMat[8] = 0.0;
	fMat[1] = -fVec[2];
	fMat[2] =  fVec[1];
	fMat[3] =  fVec[2];
	fMat[5] = -fVec[0];
	fMat[6] = -fVec[1];
	fMat[7] =  fVec[0];
}

void SetQuatf(const float fVecQi[4], float fVecQo[4])
{
    fVecQo[0] = fVecQi[0];
    fVecQo[1] = fVecQi[1];
    fVecQo[2] = fVecQi[2];
    fVecQo[3] = fVecQi[3];
}

void SetMat3f(const float fMat_i[9], float fMat_o[9])
{
	fMat_o[0] = fMat_i[0];
	fMat_o[1] = fMat_i[1];
	fMat_o[2] = fMat_i[2];
	fMat_o[3] = fMat_i[3];
	fMat_o[4] = fMat_i[4];
	fMat_o[5] = fMat_i[5];
	fMat_o[6] = fMat_i[6];
	fMat_o[7] = fMat_i[7];
	fMat_o[8] = fMat_i[8];
}

void Att2Quat(const float att[3],float quat[4])
{
	float sy,cy;
	float sp,cp;
	float sr,cr;
	
	float pitch,roll,yaw;
	
	//
	pitch = att[0];
	roll  = att[1];
	yaw   = att[2];
	
	//
	sy = sinf(yaw*0.5f);
	cy = cosf(yaw*0.5f);
	sp = sinf(pitch*0.5f);
	cp = cosf(pitch*0.5f);
	sr = sinf(roll*0.5f);
	cr = cosf(roll*0.5f);
	//
	quat[0] = cy*cp*cr - sy*sp*sr;
	quat[1] = -sy*cp*sr + cy*sp*cr;
	quat[2] = sy*sp*cr + cy*cp*sr;
	quat[3] = sy*cp*cr + cy*sp*sr;
}

void Att2Cnb(const float att[3],float Cnb[9])
{
  float si,ci;
	float sj,cj;
	float sk,ck;
	
	// 
	si = sinf(att[0]); 
	ci = cosf(att[0]);
	//
	sj = sinf(att[1]); 
	cj = cosf(att[1]);
	//
	sk = sinf(att[2]); 
	ck = cosf(att[2]);
	
	//
	Cnb[0] = cj*ck-si*sj*sk;
	Cnb[1] = -ci*sk;
	Cnb[2] = sj*ck+si*cj*sk;
	Cnb[3] = cj*sk+si*sj*ck;
	Cnb[4] = ci*ck;
	Cnb[5] = sj*sk-si*cj*ck;
	Cnb[6] = -ci*sj;
	Cnb[7] = si;
	Cnb[8] = ci*cj;
}

void Quat2Dcm(const float quat[4], float Dcm[9])
{
    float l_Q00, l_Q01, l_Q02, l_Q03, l_Q11, l_Q12, l_Q13, l_Q22, l_Q23, l_Q33;


    l_Q00 = quat[0] * quat[0];
    l_Q11 = quat[1] * quat[1];
    l_Q22 = quat[2] * quat[2];
    l_Q33 = quat[3] * quat[3];
    l_Q12 = 2.0f*quat[1] * quat[2];	l_Q03 = 2.0f*quat[0] * quat[3];
    l_Q13 = 2.0f*quat[1] * quat[3];	l_Q02 = 2.0f*quat[0] * quat[2];
    l_Q23 = 2.0f*quat[2] * quat[3];	l_Q01 = 2.0f*quat[0] * quat[1];
    Dcm[0 * 3 + 0] = l_Q00 + l_Q11 - l_Q22 - l_Q33;
    Dcm[0 * 3 + 1] = l_Q12 - l_Q03;
    Dcm[0 * 3 + 2] = l_Q13 + l_Q02;
    Dcm[1 * 3 + 0] = l_Q12 + l_Q03;
    Dcm[1 * 3 + 1] = l_Q00 - l_Q11 + l_Q22 - l_Q33;
    Dcm[1 * 3 + 2] = l_Q23 - l_Q01;
    Dcm[2 * 3 + 0] = l_Q13 - l_Q02;
    Dcm[2 * 3 + 1] = l_Q23 + l_Q01;
    Dcm[2 * 3 + 2] = l_Q00 - l_Q11 - l_Q22 + l_Q33;
}

void Dcm2Euler(const float Dcm[9], float att[3])
{
	float pit,rol,yaw;
    pit = asinf(Dcm[2 * 3 + 1]);
    rol = atan2f(-Dcm[2 * 3 + 0], Dcm[2 * 3 + 2]);
    yaw = atan2f(-Dcm[0 * 3 + 1], Dcm[1 * 3 + 1]);
    if (yaw < 0.0f)
    {
        yaw += _PI_F * 2;
    }
		
		att[0] = pit;
		att[1] = rol;
		att[2] = yaw;
}

float LengthVec3f(const float fVec3[3])
{
   return sqrtf(fVec3[0]*fVec3[0]+fVec3[1]*fVec3[1]+fVec3[2]*fVec3[2]);
}


void MulCbnVec3(const float cbn[9],const float vec[3],float out[3])
{
    out[0] = cbn[0]*vec[0]+cbn[1]*vec[1]+cbn[2]*vec[2];
	  out[1] = cbn[3]*vec[0]+cbn[4]*vec[1]+cbn[5]*vec[2];
	  out[2] = cbn[6]*vec[0]+cbn[7]*vec[1]+cbn[8]*vec[2];

}

void VecCross(const float vec1[3],const float vec2[3],float out[3])
{
	out[0] = -vec1[2]*vec2[1] + vec1[1]*vec2[2];
	out[1] =  vec1[2]*vec2[0] - vec1[0]*vec2[2];
	out[2] = -vec1[1]*vec2[0] + vec1[0]*vec2[1];
}

void RotVec2Quat(const float rot_vec[3], float quat[4])
{
    float v1, v2, v3;
    float m, f;

    v1 = rot_vec[0];
    v2 = rot_vec[1];
    v3 = rot_vec[2];

    m = sqrtf(v1*v1 + v2*v2 + v3*v3);
    if (m > 1e-10f)
    {
        f = sinf(m / 2.0f) / m;
    }
    else
    {
        f = 0.5f;
    }

    quat[0] = cosf(m / 2.0f);
    quat[1] = f*v1;
    quat[2] = f*v2;
    quat[3] = f*v3;
}

void MulQuatf(const float fVecQ1[4], const float fVecQ2[4], float fVecQo[4])
{
    float q0;
    float quat[4];

    quat[0] = fVecQ1[0] * fVecQ2[0] - fVecQ1[1] * fVecQ2[1] - fVecQ1[2] * fVecQ2[2] - fVecQ1[3] * fVecQ2[3];
    quat[1] = fVecQ1[0] * fVecQ2[1] + fVecQ1[1] * fVecQ2[0] + fVecQ1[2] * fVecQ2[3] - fVecQ1[3] * fVecQ2[2];
    quat[2] = fVecQ1[0] * fVecQ2[2] - fVecQ1[1] * fVecQ2[3] + fVecQ1[2] * fVecQ2[0] + fVecQ1[3] * fVecQ2[1];
    quat[3] = fVecQ1[0] * fVecQ2[3] + fVecQ1[1] * fVecQ2[2] - fVecQ1[2] * fVecQ2[1] + fVecQ1[3] * fVecQ2[0];
    q0 = sqrtf(quat[0]*quat[0] + quat[1]*quat[1]+quat[2]*quat[2]+quat[3]*quat[3]);
  
    quat[0] = quat[0]/q0;
	  quat[1] = quat[1]/q0;  
	  quat[2] = quat[2]/q0;  
	  quat[3] = quat[3]/q0;  
	
    fVecQo[0] = quat[0];
    fVecQo[1] = quat[1];
    fVecQo[2] = quat[2];
    fVecQo[3] = quat[3];
}


