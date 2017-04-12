#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 210;

struct size
{

double mem[2][maxn];

__attribute__((optimize(2))) int main()
{
	int n, m, l, r, w;
	double *f;
	double *g;
	register int i;
	while (scanf("%d%d%d%d", &n, &m, &l, &r) && n)
	{
		f = mem[0];
		g = mem[1];
		for (i = 1; i <= m; i++)
			g[i] = i == 1;
		while (m--)
		{
			scanf("%d", &w);
			for (i = 1; i <= n; i++)
				f[i] = (g[i - w < 1 ? n + i - w : i - w] + g[i + w > n ? i + w - n : i + w]) / 2;
			swap(f, g);
		}
		double ans = 0;
		for (i = l; i <= r; i++)
			ans += g[i];
		printf("%.4lf\n", ans);
	}
}
}cls;
int main()
{
	printf("%d\n", sizeof(cls) / 1024);
}