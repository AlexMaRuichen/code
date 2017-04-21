#include <stdio.h>
#include <math.h>

#include <algorithm>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 110;
const double eps = 1e-8;
const double inf = 1e100;

int n, m;
double a[maxn][maxn];
double b[maxn];
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

bool simplex()
{
	int i, l, e;
	double tmp;
	while (true)
	{
		for (e = 1; e <= n; e++)
			if (c[e] > eps)
				break;
		if (e == n + 1)
			return true;
		tmp = inf;
		for (i = 1; i <= m; i++)
			if (a[i][e] > eps && tense(tmp, b[i] / a[i][e]))
				l = i;
		if (tmp == inf)	
			return false;
		pivot(l, e);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			scanf("%lf", &a[i][j]);
		scanf("%lf", &b[i]);
	}
	for (int i = 1; i <= n; i++)
		scanf("%lf", &c[i]);
	simplex() ? printf("%.2lf", v) : puts("Infinity");
}