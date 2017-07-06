
#include "math.h"
#include "stdio.h"
#include "cholcal.h"

int cholcal(float a[], int n, float det[])
{ int i, j, k, u,l;
float d;
if ((a[0] + 1.0f == 1.0f) || (a[0] < 0.0f))
{
	return(-2);
}
a[0] = sqrt(a[0]);
d = a[0];
for (i = 1; i <= n - 1; i++)
{
	u = i*n; a[u] = a[u] / a[0];
}
for (j = 1; j <= n - 1; j++)
{
	l = j*n + j;
	for (k = 0; k <= j - 1; k++)
	{
		u = j*n + k; a[l] = a[l] - a[u] * a[u];
	}
	if ((a[l] + 1.0f == 1.0f) || (a[l] < 0.0f))
	{
	
		return(-2);
	}
	a[l] = sqrt(a[l]);
	d = d*a[l];
	for (i = j + 1; i <= n - 1; i++)
	{
		u = i*n + j;
		for (k = 0; k <= j - 1; k++)
			a[u] = a[u] - a[i*n + k] * a[j*n + k];
		a[u] = a[u] / a[l];
	}
}
*det = d*d;
for (i = 0; i <= n - 2; i++)
for (j = i + 1; j <= n - 1; j++)
a[i*n + j] = 0.0f;
return(2);
}

