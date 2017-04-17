#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
const int N = 1e6;
const int mod = 1e9 + 7;

int prime[maxn];
bool v[maxn];
int mu[maxn];
int cnt;

int mul(int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * 1ll * x % mod;
		x = x * 1ll * x % mod;
		y >>= 1;
	}
	return ans;
}

int f[maxn];
int sf[maxn];
int invf[maxn];
int g[maxn];
int sg[maxn];
int invg[maxn];

void sieve()
{
	mu[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!v[i])
			prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * prime[j] <= N; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
				break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	f[1] = sf[1] = 1;
	for (int i = 2; i <= N; i++)
		f[i] = (f[i - 1] + f[i - 2]) % mod;
	for (int i = 2; i <= N; i++)
		sf[i] = sf[i - 1] * 1ll * f[i] % mod;
	invf[N] = mul(sf[N], mod - 2);
	for (int i = N - 1; i; i--)
		invf[i] = invf[i + 1] * 1ll * f[i + 1] % mod;
	for (int i = 2; i <= N; i++)
		invf[i] = invf[i] * 1ll * sf[i - 1] % mod;

	invg[0] = sg[1] = 1;
	for (int i = 1; i <= N; i++)
		g[i] = 1;
	for (int i = 2; i <= N; i++)
		for (int j = 1; i * j <= N; j++)
			g[i * j] = g[i * j] * 1ll * (mu[j] == 1 ? f[i] : mu[j] == -1 ? invf[i] : 1) % mod;
	for (int i = 2; i <= N; i++)
		sg[i] = sg[i - 1] * 1ll * g[i] % mod;
	invg[N] = mul(sg[N], mod - 2);
	for (int i =  N - 1; i; i--)
		invg[i] = invg[i + 1] * 1ll * g[i + 1] % mod;
}

int calc(int n, int m)
{
	int ans = 1;
	for (int i = 1, last; i <= n && i <= m; i = last + 1)
	{
		last = min(n / (n / i), m / (m / i));
		ans = ans * 1ll * mul(sg[last] * 1ll * invg[i - 1] % mod, (n / i) * 1ll * (m / i) % (mod - 1)) % mod;
	}
	return ans;
}

int main()
{
	sieve();
	int T, n, m;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", calc(n, m));
	}
}