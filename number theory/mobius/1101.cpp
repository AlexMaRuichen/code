#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 5e4 + 10;
const int N = 5e4;

typedef long long LL;

bool v[maxn];
int prime[maxn];
int mu[maxn];

void linear_shaker()
{
	mu[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!v[i])
			prime[++prime[0]] = i, mu[i] = -1;
		for (int j = 1; j <= prime[0] && i * prime[j] <= N; j++)
		{
			v[i * prime[j]] = true;
			if (i % prime[j] == 0)
				break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= N; i++)
		mu[i] += mu[i - 1];
}

LL calc(int x, int y)
{
	LL ans = 0;
	for (int i = 1, last; i <= x && i <= y; i = last + 1)
	{
		last = min(x / (x / i), y / (y / i));
		ans += (mu[last] - mu[i - 1]) * 1ll * (x / i) * (y / i);
	}
	return ans;
}

int main()
{
	linear_shaker();
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		printf("%lld\n", calc(n / k, m / k));
	}
}