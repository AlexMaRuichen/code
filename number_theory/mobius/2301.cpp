#include <stdio.h>

#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 5e4 + 10;
const int N = 5e4;

bool v[maxn];
int prime[6000];
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

int k;

LL calc(int x, int y)
{
	long long ans = 0;
	x /= k;
	y /= k;
	for (int i = 1, last; i <= y && i <= x; i = last + 1)
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
		int a, b, c, d;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%lld\n", calc(b, d) - calc(a - 1, d) - calc(b, c - 1) + calc(a - 1, c - 1));
	}
}