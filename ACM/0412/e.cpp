#include <stdio.h>
#include <string.h>

#include <algorithm>

#define lowbit(x) (x) & (-(x))

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = 100010;
const int mod = 9901;

int n, d;
int bit[maxn];

void update(int x, int y)
{
	for (int i = x; i <= n; i += lowbit(i))
		bit[i] = (bit[i] + y) % mod;
}


int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		ans = (ans + bit[i]) % mod;
	return ans;
}

int a[maxn];
int b[maxn];
int f[maxn];

int lower(int x)
{
	int l = 1, r = n + 1, mid;
	while (l < r)
	{
		mid = l + r >> 1;
		b[mid] >= x ? r = mid : l = mid + 1;
	}
//	printf("%d\n", l);
	return l;
}

int upper(int x)
{
	int l = 1, r = n + 1, mid;
	while (l < r)
	{
		mid = l + r >> 1;
		b[mid] >= x ? r = mid : l = mid + 1;
	}
//	printf("%d\n", b[l] == x ? l : l - 1);
	return b[l] == x ? l : l - 1;
}

int main()
{
	while (scanf("%d%d", &n, &d) == 2)
	{
		memset(bit, 0, sizeof(bit));
		int ans = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]), b[i] = a[i];
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; i++)
			a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
		for (int i = 1; i <= n; i++)
		{
			(ans += (f[i] = ((query(upper(b[a[i]] + d)) - query(lower(b[a[i]] - d) - 1)) % mod + mod) % mod)) %= mod;
			update(a[i], (f[i] + 1) % mod);
//			printf("%d %d\n", i, f[i]);
		}
		printf("%d\n", ans);
	}
}
/*
10 3
1 7 4 0 9 4 8 8 2 4
*/