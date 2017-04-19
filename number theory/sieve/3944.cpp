#include <stdio.h>

#include <algorithm>
#include <map>

using namespace std;

typedef long long LL;

const int maxn = 3e6;

LL phi[maxn], mu[maxn];

int cnt;
int prime[maxn];
bool v[maxn];

void sieve()
{
	phi[1] = mu[1] = 1;
	for (int i = 2; i < maxn; i++)
	{
		if (!v[i])
			prime[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
		for (int j = 1; j <= cnt && i * prime[j] < maxn; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i < maxn; i++)
		phi[i] += phi[i - 1],
		mu[i] += mu[i - 1];
}

typedef pair <LL, LL> query;

map <int, query> m;

inline void operator -= (query &a, const query &b)
{
	a.first -= b.first;
	a.second -= b.second;
}

inline query operator * (int x, const query &y)
{
	return query(y.first * x, y.second * x);
}

query calc(LL x)
{
	if (x < maxn)
		return query(phi[x], mu[x]);
	if (m.count(x))
		return m[x];
	query ans = query(x * 1ll * (x + 1) >> 1, 1);
	for (LL i = 2, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans -= (last - i + 1) * calc(x / i);
	}
	return m[x] = ans;
}

int main()
{
	sieve();
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int x;
		scanf("%d", &x);
		static query ans;
		ans = calc(x);
		printf("%lld %lld\n", ans.first, ans.second);
	}
}