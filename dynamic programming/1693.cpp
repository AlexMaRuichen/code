#include <stdio.h>
#include <string.h>

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

typedef unsigned long long uLL;

const int maxn = 15;
const int maxm = 1 << maxn;

int n, m;
bool map[maxn][maxn];
uLL mem[2][maxm];

uLL work()
{
	uLL *f = mem[0];
	uLL *g = mem[1];
	memset(g, 0, sizeof(mem[0]));
	g[0] = 1;
	int mask = 1 << (m + 1);
	for (int i = 0; i < n; i++)
	{
		memset(f, 0, sizeof(mem[0]));
		for (int k = 0; k < mask; k++)
			if (!(k & (1 << m)))
				f[k << 1] += g[k];
		swap(f, g);
		for (int j = 0; j < m; j++, swap(f, g))
		{
			memset(f, 0, sizeof(mem[0]));
			if (map[i][j])
				for (int k = 0; k < mask; k++)
				{
					if ((!(k & (1 << j))) && (!(k & (1 << (j + 1)))))
						f[k | (1 << j) | (1 << (j + 1))] += g[k];
					if ((k & (1 << j)) && (!(k & (1 << (j + 1)))))
						f[k] += g[k],
						f[(k & (~(1 << j))) | (1 << (j + 1))] += g[k];
					if ((!(k & (1 << j))) && (k & (1 << (j + 1))))
						f[k] += g[k],
						f[(k | (1 << j)) & (~(1 << (j + 1)))] += g[k];
					if ((k & (1 << j)) && (k & (1 << (j + 1))))
						f[k & (~(1 << j)) & (~(1 << (j + 1)))] += g[k];
				}
			else
				for (int k = 0; k < mask; k++)
					if ((!(k & (1 << j))) && (!(k & (1 << (j + 1)))))
						f[k] += g[k];
/*			printf("(%d, %d)\n", i, j);
			for (int k = 0; k < mask; k++)
				printf("%d %llu\n", k, f[k]);*/
		}
	}
	return g[0];
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		static int testcase;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &map[i][j]);
		printf("Case %d: There are %llu ways to eat the trees.\n", ++testcase, work());
	}
}