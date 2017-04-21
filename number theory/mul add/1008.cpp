#include <stdio.h>

#include <algorithm>

using namespace std;

const int mod = 100003;

typedef long long LL;

int mul(LL x, LL y)
{
	LL ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

LL n, m;

int main()
{
	scanf("%lld%lld", &m, &n);
	int ans = (mul(m, n) - m * 1ll * mul(m - 1, n - 1) % mod + mod) % mod;
	printf("%d\n", ans);
}