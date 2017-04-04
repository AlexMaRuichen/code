#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 110;
const int stop = 1000;
const double eps = 1e-9;

double f[210][maxn];
int m[maxn];

int n, nf, nb, ns;

int main()
{
	scanf("%d", &n);
	scanf("%d", &nf);
	for (int i = 1, x, y; i <= nf; i++)
	{
		scanf("%d%d", &x, &y);
		m[x] = y;
	}
	scanf("%d", &nb);
	for (int i = 1, x, y; i <= nb; i++)
	{
		scanf("%d%d", &x, &y);
		m[x] = -y;
	}
	scanf("%d", &ns);
	for (int i = 1, x; i <= ns; i++)
	{
		scanf("%d", &x);
		m[x] = stop;
	}
	f[0][0] = 1;
	for (int i = 0; i <= 200; i++)
		for (int j = 0; j < n; j++)
		{
			if (f[i][j] < eps)
				continue;
			for (int k = 1; k <= 6; k++)
			{
				int pos = j + k;
				if (pos < 0)
					pos = -pos;
				if (pos > n)
					pos = 2 * n - pos;
				if (m[pos] == stop)
					f[i + 2][pos] += f[i][j] / 6;
				else
				{
					pos += m[pos];
					if (pos < 0)
						pos = -pos;
					if (pos > n)
						pos = 2 * n - pos;
					f[i + 1][pos] += f[i][j] / 6;
				}
			}
		}
	double ans = 0;
	for (int i = 1; i < 200; i++)
		ans += f[i][n] * i;
	if (ans < 0.005)
		puts("Impossible");
	else
		printf("%.2lf\n", ans);
}
