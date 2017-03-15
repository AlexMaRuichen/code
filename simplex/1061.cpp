#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int maxn = 1010;
const double inf = 1e10;
const double eps = 1e-7;

int n, m;

double a[maxn * 10][maxn];
double b[maxn * 10];
double c[maxn];
double v;

void pivot(int l, int e)
{
	b[l] /= a[l][e];
	for (int i = 1; i <= n; i++)
		if (i ^ e)
			a[l][i] /= a[l][e];
	a[l][e] = 1 / a[l][e];
	for (int i = 1; i <= m; i++)
		if (i ^ l && fabs(a[i][e]) > eps)
		{
			b[i] -= a[i][e] * b[l];
			for (int j = 1; j <= n; j++)
				if (j ^ e)
					a[i][j] -= a[i][e] * a[l][j];
			a[i][e] = -a[i][e] * a[l][e];
		}
	v += c[e] * b[l];
	for (int i = 1; i <= n; i++)
		if (i ^ e)
			c[i] -= c[e] * a[l][i];
	c[e] = -c[e] * a[l][e];
}

double simplex()
{
	int i, l, e;
	double tmp;
	while (true)
	{
		for (i = 1; i <= n; i++)
			if (c[i] > eps)
				break;
		if ((e = i) == n + 1)
			return v;
		tmp = inf;
		for (i = 1; i <= m; i++)
			if (a[i][e] > eps && b[i] / a[i][e] < tmp)
				tmp = b[i] / a[i][e], l = i;
		if (tmp == inf)
			return inf;
		pivot(l, e);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &c[i]);
	for (int i = 1, x, y, z; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		for (int j = x; j <= y; j++)
			a[i][j] = 1;
		b[i] = z;
	}
	printf("%d\n", int(simplex() + 0.5));
}