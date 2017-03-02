#include <stdio.h>

#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 150 + 10;

int n, sum;
int cnt[maxn];
LL ans = 1;

LL mul(LL x, int y)
{
	LL ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * x;
		x = x * x;
		y >>= 1;
	}
	return ans;
}

void split(int x, int flag)
{
	for (int i = 2; i * i <= x; i++)
		while(x % i == 0)
			cnt[i] += flag, x /= i;
	if (x ^ 1)
		cnt[x] += flag;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		if (!x && n ^ 1)
			return puts("0"), 0;
		sum += x - 1;
		for (int j = 2; j < x; j++)
			split(j, -1);
	}
	if (sum ^ (n - 2))
		return puts("0"), 0;
	for (int i = 2; i <= n - 2; i++)
		split(i, 1);
	for (int i = 2; i <= n; i++)
		ans *= mul(i, cnt[i]);
	printf("%lld\n", ans);
}
