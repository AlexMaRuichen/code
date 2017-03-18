#include <stdio.h>

#include <algorithm>

using namespace std;

typedef long long LL;

LL n;
LL prime[40];
int cnt[40];

void get(LL x)
{
	prime[0] = 0;
	for (LL i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			prime[++prime[0]] = i;
			while(x % i == 0)
				++cnt[prime[0]], x /= i;
		}
	if (x ^ 1)
		prime[++prime[0]] = x, cnt[prime[0]] = 1;
}

LL calc(LL x)
{
	LL ans = 1;
	for (LL i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			ans *= (i - 1);
			x /= i;
			while(x % i == 0)
				ans *= i, x /= i;
		}
	if (x != 1)
		ans *= x - 1;
	return ans;
}

LL add(LL x, LL y)
{
	LL ans = 0;
	while (y)
	{
		if (y & 1)
			ans = (ans + x) % n;
		x = (x + x) % n;
		y >>= 1;
	}
	return ans;
}

LL mul(LL x, LL y)
{
	LL ans = 1;
	while (y)
	{
		if (y & 1)
			ans = add(ans, x);
		x = add(x, x);
		y >>= 1;
	}
	return ans;
}

bool check(LL x)
{
	if (x % 4 == 0)
		return false;
	if (x % 2 == 0)
		x /= 2;
	get(x);
	return prime[0] == 1;
}

int find_g(LL x)
{
	LL phi = calc(x);
	get(phi);
	for (int g = 2; ; g++)
	{
		for (int i = 1; i <= prime[0]; i++)
			if (mul(g, phi/prime[0]) == 1)
				goto lableA;
		return g;
		lableA:;
	}
}

int main()
{
	scanf("%lld", &n);
	if (n == 2)
		puts("1");
	else if (n == 4)
		puts("2");
	else if (!check(n))
		puts("-1");
	else
		printf("%d\n", find_g(n));
}