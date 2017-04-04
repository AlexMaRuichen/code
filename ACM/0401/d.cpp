#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1e4 + 10;
const int N = 1e4;
const int mod = 1e4 + 7;

int n;
int prime[maxn];
bool v[maxn];
int tot;
int mu[maxn];
int cnt[maxn];

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
}

int main()
{
	linear_shaker();

	while (scanf("%d", &n) == 1)
	{
		memset(cnt, 0 ,sizeof(cnt));
		int res = 0;
		for (int i = 1, x; i <= n; i++)
			scanf("%d", &x), ++cnt[x];
		for (int i = 1; i <= N; i++)
			for (int j = 2; i * j <= N; j++)
				(cnt[i] += cnt[i * j]) %= mod;
		for (int i = 1; i <= N; i++)
			cnt[i] = cnt[i] * cnt[i] % mod;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j * i <= N; j++)
				(res += i * (i - 1) % mod * cnt[i * j] % mod * mu[j]) %= mod;
 		printf("%d\n", res);
	}
}