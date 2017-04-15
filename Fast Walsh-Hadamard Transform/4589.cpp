#include <bits/stdc++.h>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

typedef long long LL;

const int maxn = 1 << 18;
const double eps = 1e-6;
const int inf = 1e9;
const int mod = 1e9 + 7;

int inv;
int a[maxn];

void DWT(int l, int r)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	DWT(l, mid);
	DWT(mid + 1, r);
	for (int i = l, j = mid + 1, x; i <= mid; i++, j++)
	{
		x = (a[i] + a[j]) % mod;
		a[i] = (a[i] - a[j] + mod) % mod;
		a[j] = x;
	}
}

void IDWT(int l, int r)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	for (int i = l, j = mid + 1, x; i <= mid; i++, j++)
	{
		x = (a[j] - a[i] + mod) * 1ll * inv % mod;
		a[i] = (a[i] + a[j]) * 1ll * inv % mod;
		a[j] = x;
	}
	IDWT(l, mid);
	IDWT(mid + 1, r);
}

bool v[maxn];
int p[maxn];
int cnt;

void sieve()
{
	for (int i = 2; i < maxn; i++)
		if (!v[i])
		{
			p[++cnt] = i;
			for (int j = 2; i * j < maxn; j++)
				v[i * j] = true;
		}
}

int mul(int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1)
			ans = ans * 1ll * x % mod;
		x = x * 1ll * x % mod;
		y >>= 1;
	}
	return ans;
}


// BEGIN CUT HERE
int main()
{
	inv = mul(2, mod - 2);
	sieve();
//	___test.run_test(-1);
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		memset(a, 0, sizeof(a));
		int len = 1;
        for (int i = 1; p[i] <= m; i++) 
			a[p[i]] = 1;
		for(; len <= m; len <<= 1);
		--len;
		DWT(0, len);
		for (int i = 0 ; i <= len; i++)
			a[i] = mul(a[i], n);
		IDWT(0, len);
		printf("%d\n", a[0]);
	}
	return 0;
}
// END CUT HERE
