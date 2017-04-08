#include <stdio.h>

#include <algorithm>

using namespace std;

const int mod = 998244353;
const int maxn = (1 << 18) + 10;

int a[maxn];
int b[maxn];
int c[maxn];

char getc() 
{
    static const int len = 1 << 15;
    static char buf[len], *s = buf, *t = buf;
    if (s == t) 
	{
        t = (s = buf) + fread(buf, 1, len, stdin);
        if (s == t)
            return EOF;
    }
    return *s++;
}

void read(register int &x) 
{
    char ch = getc();
    x = 0;
    while (ch < '0' || ch > '9')
        ch = getc();
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + ch - '0', ch = getc();
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

void DFT(int *a, int len, int type) 
{
    for (int i = 0, t = 0; i < len; i++) 
	{
        if (i < t)
            swap(a[i], a[t]);
        for (int j = len >> 1; (t ^= j) < j; j >>= 1);
    }
    for (int i = 2; i <= len; i <<= 1) 
	{
        int wn = mul(3, (mod - 1) / i);
        for (int j = 0; j < len; j += i) 
		{
            int w = 1, t;
            for (int k = 0; k<i>> 1; k++, w = wn * 1ll * w % mod) 
			{
                t = a[j + k + (i >> 1)] * 1ll * w % mod;
                a[j + k + (i >> 1)] = (a[j + k] - t + mod) % mod;
                a[j + k] = (a[j + k] + t) % mod;
            }
        }
    }
    if (type < 0) 
	{
        reverse(a + 1, a + len);
        int t = mul(len, mod - 2);
        for (int i = 0; i < len; i++)
            c[i] = c[i] * 1ll * t % mod;
    }
}

void NTT(int *a, int *b, int *c, int len) 
{
    DFT(a, len, 1);
    DFT(b, len, 1);
    for (int i = 0; i < len; i++)
        c[i] = a[i] * 1ll * b[i] % mod;
    DFT(c, len, -1);
}

int n, m;
int main() 
{
    read(n);
    read(m);
    for (int i = 0; i <= n; i++)
        read(a[i]);
    for (int i = 0; i <= m; i++)
        read(b[i]);
    int len;
    for (len = 1; len <= n + m; len <<= 1);
    NTT(a, b, c, len);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", c[i]);
    puts("");
}