#include <stdio.h>

#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return b < a ? a = b, true :  false;
}

int phi(int x)
{
	int ans = x;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			ans = ans / i * (i - 1);
			while (x % i == 0)
				x /= i;
		}
	if (x > 1)
		ans = ans / x * (x - 1);
	return ans;
}

int main()
{
	int n, x;
	while (scanf("%d", &n) == 1)
	{
		long long ans = 1;
		while (n--)
			scanf("%d", &x), (ans *= phi(x)) %= mod;
		printf("%I64d\n", ans);
	}
}