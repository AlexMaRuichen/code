#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e7 + 10;
const int N = 1e7;

typedef long long LL;

int mu[maxn];
bool v[maxn];
int prime[670000];
int sum[maxn];

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
			if(i % prime[j] == 0)
				break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= prime[0]; i++)
		for (int j = prime[i]; j <= N; j += prime[i])
			sum[j] += mu[j / prime[i]];
	for (int i = 1; i <= N; i++)
		sum[i] += sum[i - 1];
}

LL calc(int x, int y)
{
	LL ans = 0;
	for (int i = 1, last; i <= x && i <= y; i = last + 1)
	{
		last = min(x / (x / i), y / (y / i));
		ans += (x / i) * 1ll * (y / i) * (sum[last] - sum[i - 1]);
	}
	return ans;
}

int main()
{
	linear_shaker();
	int T, n, m;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		printf("%lld\n", calc(n, m));
	}
}
