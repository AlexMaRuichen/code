#include <stdio.h>

#include <algorithm>
#include <map>

using namespace std;

typedef long long LL;

const int maxn = 3e6;

int prime[maxn];
LL phi[maxn];
bool v[maxn];
int cnt;

void sieve()
{
	phi[1] = 1;
	for (int i = 2; i < maxn; i++)
	{
		if (!v[i])
			prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * prime[j] < maxn; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 1; i < maxn; i++)
		phi[i] += phi[i - 1];
}

map <int, LL> m;

LL calc(LL x)
{
	if (x < maxn)
		return phi[x];
	if (m.count(x))
		return m[x];
	LL ans = x * (x + 1) >> 1;
	for (LL i = 2, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans -= (last - i + 1) * calc(x / i);
	}
	return m[x] = ans;
}

int main()
{
	int n;
	sieve();
	scanf("%d", &n);
	printf("%lld\n", calc(n));
}
