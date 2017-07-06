
#include<stdio.h>
#include<math.h>

#include "eigcal.h"



void f(float A[N_EIG][N_EIG]);
void x(float A[N_EIG][N_EIG]);
void g(float M[N_EIG][N_EIG], float A[N_EIG][N_EIG], int m);

unsigned char eigcal(const float matrix_in[N_EIG*N_EIG], float eigvalue[N_EIG], float eigvector[N_EIG*N_EIG])
{
	float A[N_EIG][N_EIG], Z[N_EIG][N_EIG];
	float a[N_EIG][N_EIG], b[N_EIG][N_EIG], M[N_EIG][N_EIG], R[N_EIG], I[N_EIG], X[N_EIG];
	float sum0, a2, a3, a4, a5, l;
	int i, j, k, m, n, t, tmp;

	tmp = 1;
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			A[i][j] = matrix_in[i*N_EIG+j];
			a[i][j] = matrix_in[i*N_EIG+j];
		}
	}
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			if (i == j)
			{
				Z[i][j] = 1;
			}
			else
			{
				Z[i][j] = 0;
			}
		}
	}
	f(A);

//	freopen("bwr.txt", "a+", stdout);

//	printf("A的拟上三角矩阵为:\n");
//	for (i = 0; i < N_EIG; i++)
//	{
//		for (j = 0; j < N_EIG; j++)
//		{
//			printf("  %.12le", A[i][j]);
//		}
//		printf("\n");
//	}
	m = N_EIG - 1;
	for (t = 0; t < L_EIG; t++)
	{
		for (k = 0; k < N_EIG; k++)
		{
			if (fabs(A[m][m - 1]) <= e_EIG)
			{
				R[m] = A[m][m];
				I[m] = 0;
				m = m - 1;
			}
			else if (fabs(A[m - 1][m - 2]) <= e_EIG)
			{
				a2 = A[m - 1][m - 1] + A[m][m];
				a3 = A[m - 1][m - 1] * A[m][m] - A[m][m - 1] * A[m - 1][m];
				if ((a2*a2 - 4 * a3) >= 0)
				{
					R[m - 1] = (a2 + sqrt(a2*a2 - 4 * a3))*0.5f;
					I[m - 1] = 0;
					R[m] = (a2 - sqrt(a2*a2 - 4 * a3))*0.5f;
					I[m] = 0;
				}
				else
				{
					R[m - 1] = a2*0.5f;
					I[m - 1] = sqrt(-a2*a2 + 4 * a3)*0.5f;
					R[m] = a2*0.5f;
					I[m] = -sqrt(-a2*a2 + 4 * a3)*0.5f;
				}
				m = m - 2;
			}
			else
			{
				break;
			}
			if (m == 1)
			{
				a2 = A[m - 1][m - 1] + A[m][m];
				a3 = A[m - 1][m - 1] * A[m][m] - A[m][m - 1] * A[m - 1][m];
				if ((a2*a2 - 4 * a3) >= 0)
				{
					R[m - 1] = (a2 + sqrt(a2*a2 - 4 * a3))*0.5f;
					I[m - 1] = 0;
					R[m] = (a2 - sqrt(a2*a2 - 4 * a3))*0.5f;
					I[m] = 0;
				}
				else
				{
					R[m - 1] = a2*0.5f;
					I[m - 1] = sqrt(-a2*a2 + 4 * a3)*0.5f;
					R[m] = a2*0.5f;
					I[m] = -sqrt(-a2*a2 + 4 * a3)*0.5f;
				}
				tmp = 0;
				break;
			}
			if (m == 0)
			{
				R[m] = A[m][m];
				I[m] = 0;
				tmp = 0;
				break;
			}
		}
		a4 = A[m - 1][m - 1] + A[m][m];
		a5 = A[m - 1][m - 1] * A[m][m] - A[m][m - 1] * A[m - 1][m];
		for (i = 0; i <= m; i++)
		{
			for (j = 0; j <= m; j++)
			{
				sum0 = 0;
				for (k = 0; k <= m; k++)
				{
					sum0 = sum0 + A[i][k] * A[k][j];
				}
				M[i][j] = sum0 - a4*A[i][j] + a5*Z[i][j];
			}
		}
		g(M, A, m);
		if (tmp == 0)
		{
			break;
		}
	}
//	printf("QR迭代结束后矩阵A:\n");
//	for (i = 0; i < N_EIG; i++)
//	{
//		for (j = 0; j < N_EIG; j++)
//		{
//			printf("  %.12le", A[i][j]);
//		}
//		printf("\n");
//	}
	x(A);
//	printf("t=%d\n", t);
	for (i = 0; i < N_EIG; i++)
	{
		if (I[i] != 0)
		{
	//		printf("特征值为:%.12le+(%.12le)i\n", R[i], I[i]);
		}
		else
		{
		//	printf("特征值为:%.12le\n", R[i]);
			for (n = 0; n < N_EIG; n++)
			{
				for (j = 0; j < N_EIG; j++)
				{
					if (n == j)
					{
						b[n][j] = a[n][j] - R[i];
					}
					else
					{
						b[n][j] = a[n][j];
					}
				}
			}
			for (k = 1; k < N_EIG; k++)
			{
				for (n = k; n < N_EIG; n++)
				{
					l = b[n][k - 1] / b[k - 1][k - 1];
					for (j = k - 1; j < N_EIG; j++)
					{
						b[n][j] = b[n][j] - l*b[k - 1][j];
					}
				}
			}
			X[N_EIG - 1] = 1;
			for (k = N_EIG - 2; k >= 0; k--)
			{
				sum0 = 0;
				for (j = k + 1; j < N_EIG; j++)
				{
					sum0 = sum0 + b[k][j] * X[j];
				}
				X[k] = -sum0 / b[k][k];
			}
//			printf("特征值向量为:\n");
			for (k = 0; k < N_EIG; k++)
			{
			//	printf(" %.12le", X[k]);
				eigvector[i*N_EIG + k] = X[k];
				k = k;
			}
//			printf("\n");
		}
		for (i = 0; i < N_EIG;i++)
		   eigvalue[i] = R[i];

		
	}
	//fclose(stdout);
	return 0;
}
void f(float A[N_EIG][N_EIG])
{
	float u[N_EIG], p[N_EIG], q[N_EIG], w[N_EIG];
	float sum, sum1, sum2, d, c, h, t;
	int i, j, r;
	for (r = 0; r < N_EIG - 2; r++)
	{
		sum = 0;
		for (i = r + 1; i < N_EIG; i++)
		{
			sum = sum + A[i][r] * A[i][r];
		}
		d = sqrt(sum);
		if (A[r + 1][r] <= 0)
		{
			c = d;
		}
		else
		{
			c = -d;
		}
		h = c*c - c*A[r + 1][r];
		for (i = 0; i < r + 1; i++)
		{
			u[i] = 0;
		}
		u[r + 1] = A[r + 1][r] - c;
		for (i = r + 2; i < N_EIG; i++)
		{
			u[i] = A[i][r];
		}
		for (i = 0; i < N_EIG; i++)
		{
			sum2 = 0;
			for (j = 0; j < N_EIG; j++)
			{
				sum2 = sum2 + A[j][i] * u[j];
			}
			p[i] = sum2 / h;
		}
		for (i = 0; i < N_EIG; i++)
		{
			sum2 = 0;
			for (j = 0; j < N_EIG; j++)
			{
				sum2 = sum2 + A[i][j] * u[j];
			}
			q[i] = sum2 / h;
		}
		sum1 = 0;
		for (i = 0; i < N_EIG; i++)
		{
			sum1 = p[i] * u[i] + sum1;
		}
		t = sum1 / h;
		for (i = 0; i < N_EIG; i++)
		{
			w[i] = q[i] - t*u[i];
		}
		for (i = 0; i < N_EIG; i++)
		{
			for (j = 0; j < N_EIG; j++)
			{
				A[i][j] = A[i][j] - w[i] * u[j] - u[i] * p[j];
			}
		}
	}
}
void x(float A[N_EIG][N_EIG])
{
	float a[N_EIG][N_EIG], Q[N_EIG][N_EIG], R[N_EIG][N_EIG], u[N_EIG], p[N_EIG], w[N_EIG];
	float sum, sum1, sum2, sum3, d, c, h;
	int i, j, k, r;
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			a[i][j] = A[i][j];
		}
	}
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			if (i == j)
			{
				Q[i][j] = 1;
			}
			else
			{
				Q[i][j] = 0;
			}
		}
	}
	for (r = 0; r < N_EIG - 1; r++)
	{
		sum = 0;
		for (i = r; i < N_EIG; i++)
		{
			sum = sum + a[i][r] * a[i][r];
		}
		d = sqrt(sum);
		if (a[r][r] <= 0)
		{
			c = d;
		}
		else
		{
			c = -d;
		}
		h = c*c - c*a[r][r];
		u[r] = a[r][r] - c;
		for (i = r + 1; i < N_EIG; i++)
		{
			u[i] = a[i][r];
		}
		for (i = 0; i < N_EIG; i++)
		{
			sum1 = 0;
			for (j = r; j < N_EIG; j++)
			{
				sum1 = sum1 + Q[i][j] * u[j];
			}
			w[i] = sum1;
		}
		for (i = 0; i < N_EIG; i++)
		{
			for (j = r; j < N_EIG; j++)
			{
				Q[i][j] = Q[i][j] - w[i] * u[j] / h;
			}
		}
		for (i = 0; i < N_EIG; i++)
		{
			sum2 = 0;
			for (j = r; j < N_EIG; j++)
			{
				sum2 = sum2 + a[j][i] * u[j];
			}
			p[i] = sum2 / h;
		}
		for (i = r; i < N_EIG; i++)
		{
			for (j = 0; j < N_EIG; j++)
			{
				a[i][j] = a[i][j] - u[i] * p[j];
			}
		}
	}
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			R[i][j] = a[i][j];
		}
	}
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			sum3 = 0;
			for (k = 0; k < N_EIG; k++)
			{
				sum3 = sum3 + Q[i][k] * R[k][j];
			}
		}
	}
	for (i = 0; i < N_EIG; i++)
	{
		for (j = 0; j < N_EIG; j++)
		{
			sum3 = 0;
			for (k = 0; k < N_EIG; k++)
			{
				sum3 = sum3 + R[i][k] * Q[k][j];
			}
		}
	}
}
void g(float M[N_EIG][N_EIG], float A[N_EIG][N_EIG], int m)
{
	float B[N_EIG][N_EIG], C[N_EIG][N_EIG], u[N_EIG], v[N_EIG], p[N_EIG], q[N_EIG], w[N_EIG];
	float sum, sum1, sum2, sum3, d, c, h, t;
	int i, j, r;
	for (i = 0; i <= m; i++)
	{
		for (j = 0; j <= m; j++)
		{
			B[i][j] = M[i][j];
		}
	}
	for (i = 0; i <= m; i++)
	{
		for (j = 0; j <= m; j++)
		{
			C[i][j] = A[i][j];
		}
	}
	for (r = 0; r <= m - 1; r++)
	{
		sum = 0;
		for (i = r; i <= m; i++)
		{
			sum = sum + B[i][r] * B[i][r];
		}
		d = sqrt(sum);
		if (B[r][r] <= 0)
		{
			c = d;
		}
		else
		{
			c = -d;
		}
		h = c*c - c*B[r][r];
		for (i = 0; i < r; i++)
		{
			u[i] = 0;
		}
		u[r] = B[r][r] - c;
		for (i = r + 1; i <= m; i++)
		{
			u[i] = B[i][r];
		}
		for (i = 0; i <= m; i++)
		{
			sum1 = 0;
			for (j = 0; j <= m; j++)
			{
				sum1 = sum1 + B[i][j] * u[j];
			}
			v[i] = sum1 / h;
		}
		for (i = 0; i <= m; i++)
		{
			for (j = 0; j <= m; j++)
			{
				B[i][j] = B[i][j] - u[i] * v[j];
			}
		}
		for (i = 0; i <= m; i++)
		{
			sum2 = 0;
			for (j = 0; j <= m; j++)
			{
				sum2 = sum2 + C[j][i] * u[j];
			}
			p[i] = sum2 / h;
		}
		for (i = 0; i <= m; i++)
		{
			sum2 = 0;
			for (j = 0; j <= m; j++)
			{
				sum2 = sum2 + C[i][j] * u[j];
			}
			q[i] = sum2 / h;
		}
		sum3 = 0;
		for (i = 0; i <= m; i++)
		{
			sum3 = p[i] * u[i] + sum3;
		}
		t = sum3 / h;
		for (i = 0; i <= m; i++)
		{
			w[i] = q[i] - t*u[i];
		}
		for (i = 0; i <= m; i++)
		{
			for (j = 0; j <= m; j++)
			{
				C[i][j] = C[i][j] - w[i] * u[j] - u[i] * p[j];
			}
		}
	}
	for (i = 0; i <= m; i++)
	{
		for (j = 0; j <= m; j++)
		{
			A[i][j] = C[i][j];
		}
	}
}







