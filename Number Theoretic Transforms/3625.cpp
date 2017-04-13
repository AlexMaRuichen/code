#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 1 << 19;
const int mod = 998244353;

int inv2;

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

void DFT(int *a, int len)
{
	for (int i = 0, t = 0; i < len; i++)
	{
		if (t < i)
			swap(a[i], a[t]);
		for (int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	for (int i = 2; i <= len; i <<= 1)
	{
		int wn = mul(3, (mod - 1) / i);
		for (int j = 0; j < len; j += i)
		{
			int w = 1, t;
			for (int k = 0; k < (i >> 1); k++, w = w * 1ll * wn % mod)
			{
				t = a[j + k + (i >> 1)] * 1ll * w % mod;
				a[j + k + (i >> 1)] = (a[j + k] + mod - t) % mod;
				a[j + k] = (a[j + k] + t) % mod;
			}
		}
	}
}

int ti[maxn];

void inv(int *a, int *b, int len)
{
	if (len == 1)
	{
		b[0] = mul(a[0], mod - 2);
		return;
	}
	inv(a, b, len >> 1);
	memcpy(ti, a, sizeof(int) * len);
	memset(ti + len, 0, sizeof(int) * len);
	DFT(ti, len << 1);
	DFT(b, len << 1);
	for (int i = 0; i < len << 1; i++)
		ti[i] = b[i] * (2 - ti[i] * 1ll * b[i] % mod + mod) % mod;
	DFT(ti, len << 1);
	reverse(ti + 1, ti + (len << 1));
	for (int i = 0, inverse = mul(len << 1, mod - 2); i < len; i++)
		b[i] = ti[i] * 1ll * inverse % mod;
	memset(b + len, 0, sizeof(int) * len);
}

int tr[maxn];
int ir[maxn];

void root(int *a, int *b, int len)
{
	if (len == 1)
	{
		b[0] = 1;
		return;
	}
	root(a, b, len >> 1);
	memset(ir, 0, sizeof(int) * len);
	inv(b, ir, len);
	memcpy(tr, a, sizeof(int) * len);
	memset(tr + len, 0, sizeof(int) * len);
	DFT(tr, len << 1);
	DFT(b, len << 1);
	DFT(ir, len << 1);
	for (int i = 0; i < len << 1; i++)
		tr[i] = inv2 * (b[i] + tr[i] * 1ll * ir[i] % mod) % mod;
	DFT(tr, len << 1);
	reverse(tr + 1, tr + (len << 1));
	for (int i = 0, inverse = mul(len << 1, mod - 2); i < len; i++)
		b[i] = tr[i] * 1ll * inverse % mod;
	memset(b + len, 0, sizeof(int) * len);
}

int n, m;
int a[maxn];
int b[maxn];

int main()
{
	inv2 = mul(2, mod - 2);
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		if (x <= m)
			a[x] = mod - 4;
	}
	int len = 1;
	for (; len <= m; len <<= 1);
	++a[0];
	root(a, b, len);
	memcpy(a, b, sizeof(int) * len);
	++a[0];
	memset(b, 0, sizeof(int) * len);
	inv(a, b, len);
	for (int i = 1; i <= m; i++)
		printf("%d\n", (b[i] + b[i]) % mod);
}