#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <functional>

using namespace std;

typedef long long LL;

const int maxn = 110;

LL tot, ans;
int n, top;
int a[maxn], b[35], q[110];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), tot += a[i];
	sort(a + 1, a + n + 1, greater <int> ());
	for (int i = 1; i <= n; i++)
	{
		int t = a[i];
		for (int j = 30 ;j>=0;j--)
			if (a[i] & (1 << j))
			{
				if (!b[j])
				{
					b[j]=i;
					break;
				}
				else 
					a[i] ^= a[b[j]];
			}
		if (a[i])
			ans+=t;
	}
	ans ? printf("%lld\n",tot - ans) : puts("-1"); 
}