#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 5000010;
const int mod = 1e9 + 7;

int n, m, k;

int prime[maxn];
bool v[maxn];
int f[maxn];
int g[maxn];
int F[maxn];
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

void sieve()
{
	F[1] = 1;
	for (int i = 2; i < maxn; i++)
	{
		if (!v[i])
		{
			f[i] = mul(i, k);
			g[i] = i;
			F[i] = f[i] - 1;
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < maxn; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] * prime[j];
				F[i * prime[j]] =  g[i] ^ i ? 
								   F[i / g[i]] * 1ll * F[g[i] * prime[j]] % mod : 
								   F[i] * 1ll * f[prime[j]] % mod;
				break;
			}
			g[i * prime[j]] = prime[j];
			F[i * prime[j]] = F[i] * 1ll * F[prime[j]] % mod;
		}
	}
	for (int i = 2; i < maxn; i++)
		F[i] = (F[i] + F[i - 1]) % mod;
}

int calc(int n, int m)
{
	int ans = 0;
	for (int i = 1, last; i <= n && i <= m; i = last + 1)
	{
		last = min(n / (n / i), m / (m / i));
		ans = (ans + (F[last] - F[i - 1] + mod) * 1ll * (n / i) % mod * (m / i) % mod) % mod;
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d%d", &T, &k);
	sieve();
	while (T--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", calc(n, m));
	}
}
