#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
typedef long long LL;

int b, q;
LL a[maxn];
LL sum;

int main()
{
	scanf("%d%d", &b, &q);
	for (int i = 0; i < b; i++)
	{
		scanf("%lld", &a[i]);
		sum = (sum + a[i] * i) % (b - 1);
	}
	if (sum)
		--a[sum];
	for (int i = 1; i < b; i++)
		a[i] += a[i - 1];
	while (q--)
	{
		static long long k;
		scanf("%lld", &k);
		int ans = upper_bound(a, a + b, k) - a;
		printf("%d\n", ans == b ? -1 : ans);
	}
}
