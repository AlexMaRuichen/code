#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 1 << 18;
const int mod = 998244353;

inline int add(int a, int b)
{
	static int ans;
	ans = a + b;
	if (ans >= mod)
		ans -= mod;
	if (ans < 0)
		ans += mod;
	return ans;
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

void DFT(int *a, int len)
{
	for (int i = 0, t = 0; i < len; i++)
	{
		if (t < i)
			swap(a[t], a[i]);
		for (int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	for (int i = 2; i <= len; i <<= 1)
		for (int j = 0, wn = mul(3, (mod - 1) / i); j < len; j += i)
			for (int k = 0, w = 1, t; k < (i >> 1); k++, w = w * 1ll * wn % mod)
			{
				t = a[j + k + (i >> 1)] * 1ll * w % mod;
				a[j + k + (i >> 1)] = add(a[j + k], -t);
				a[j + k] = add(a[j + k], t);
			}
}

void NTT(int *a, int *b, int *c, int len)
{
	DFT(a, len);
	DFT(b, len);
	for (int i = 0; i < len; i++)
		c[i] = a[i] * 1ll * b[i] % mod;
	DFT(c, len);
	reverse(c + 1, c + len);
	for (int i = 0, inv = mul(len, mod - 2); i < len; i++)
		c[i] = c[i] * 1ll * inv % mod;
}

int pon[maxn];
int inv[maxn];

int a[maxn];
int b[maxn];
int c[maxn];

void debug(int *a, int n)
{
	for (int i = 0; i <= n; i++)
		printf("%d ", a[i]);
	puts("");
}

int main()
{
	int n, len;
	scanf("%d", &n);
	for (len = 1; len <= (n << 1); len <<= 1);
	pon[0] = 1;
	for (int i = 1; i <= n; i++)
		pon[i] = pon[i - 1] * 1ll * i % mod;
	inv[n] = mul(pon[n], mod - 2);
	for (int i = n - 1; ~i; i--)
		inv[i] = inv[i + 1] * 1ll * (i + 1) % mod;
	for (int i = 0; i <= n; i++)
		a[i] = i & 1 ? mod - inv[i] : inv[i];
	b[0] = 1;
	b[1] = n + 1;
	for (int i = 2; i <= n; i++)
		b[i] = (mul(i, n + 1) - 1) * 1ll * mul(i - 1, mod - 2) % mod * inv[i] % mod;
	NTT(a, b, c, len);
	int ans = 0;
	for (int i = 0; i <= n; i++)
		ans = (ans + mul(2, i) * 1ll * pon[i] % mod * c[i] % mod) % mod;
	printf("%d\n", ans);
}