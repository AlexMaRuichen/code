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

typedef long long LL;

const int maxn = 110;
int mod;

template <typename T> inline T& add(T &a, const T &b)
{
	if ((a += b) >= mod)
		a -= mod;
	return a;
}

int a[maxn];
int b[maxn];
int c[maxn];
int bin[maxn];

int f[maxn][2][2][2];
int g[maxn][2][2][2];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		LL n, m, k;
		scanf("%lld%lld%lld%d", &m, &n, &k, &mod);
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		int lenm, lenn, lenk;
		for (lenm = 0; m; m >>= 1)
			a[++lenm] = m & 1;
		for (lenn = 0; n; n >>= 1)
			b[++lenn] = n & 1;
		for (lenk = 0; k; k >>= 1)
			c[++lenk] = k & 1;
		int len = max(max(lenm, lenn), lenk);
		bin[0] = 1;
		for (int i = 1; i <= len; i++)
			add(bin[i] = bin[i - 1] << 1, 0);
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		int tmp;
		for (int x = 0; x < 2; x++)
			for (int y = 0; y < 2; y++)
				for (int z = 0; z < 2; z++)
					for (int u = 0; u < (x ? 2 : a[1]); u++)
						for (int v = 0; v < (y ? 2 : b[1]); v++)
							if ((u ^ v) >= c[1] || z)
								add(f[1][x][y][z], ((u ^ v) - c[1] + mod) % mod),
								add(g[1][x][y][z], 1);
		for (int i = 2; i <= len; i++)
			for (int x = 0; x < 2; x++)
				for (int y = 0; y < 2; y++)
					for (int z = 0; z < 2; z++)
						for (int u = 0; u <= max(x, a[i]); u++)
							for (int v = 0; v <= max(y, b[i]); v++)
								if ((u ^ v) >= c[i] || z)
								{
									int j = x | (u < a[i]);
									int k = y | (v < b[i]);
									int l = z | ((u ^ v) > c[i]);
									tmp = g[i - 1][j][k][l] * 1ll * ((u ^ v) - c[i]) * bin[i - 1] % mod;
									if (tmp < 0)
										tmp += mod;
									add(tmp, f[i - 1][j][k][l]);
									add(f[i][x][y][z], tmp);
									add(g[i][x][y][z], g[i - 1][j][k][l]);
								}
		printf("%d\n", f[len][0][0][0]);	
	}
}

