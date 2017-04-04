#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>

inline char getc()
{
	static const int len = 1 << 15;
	static char buf[len], *s, *t;
	if (s == t)
	{
		t = (s = buf) + fread(buf, 1, len, stdin);
		if (s == t)
			return EOF;
	} 
	return *s++;
}

template <typename T> inline void read(register T &x)
{
	static char ch;
	x = 0;
	while (ch < '0')
		ch = getc();
	while (ch >= '0')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}


using namespace std;

typedef long long LL;

const LL a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

int T;

LL mx;

LL gcd(LL a, LL b) 
{ 
	return b ? gcd(b, a % b) : a; 
}

LL mul(LL a, LL b, LL p) 
{
    LL d = ((long double)a / p * b + 1e-8);
    LL res = a * b - d * p;
    res = res < 0 ? res + p : res;
    return res;
}

LL qpow(LL a, LL b, LL c) 
{
    LL res = 1;
    for (; b; b >>= 1, a = mul(a, a, c))
        if (b & 1)
            res = mul(res, a, c);
    return res;
}

bool check(LL a, LL n, LL r, LL s) 
{
    LL x = qpow(a, r, n), pre = x;
    for (int i = 1; i <= s; i++) 
	{
        x = mul(x, x, n);
        if (x == 1 && pre != 1 && pre != n - 1)
            return 0;
        pre = x;
    }
    if (x != 1)
        return 0;
    return 1;
}

bool MR(LL n) 
{
    if (n <= 1)
        return false;
    LL r = n - 1, s = 0;
    while (!(r & 1))
        r >>= 1, s++;
    for (int i = 0; i < 9; i++) 
	{
        if (a[i] == n)
            return true;
        if (!check(a[i], n, r, s))
            return false;
    }
    return true;
}

LL pol_rho(LL n, LL c) 
{
    LL k = 2, x = rand() % n, y = x, p = 1;
    for (LL i = 1; p == 1; i++) 
	{
        x = (mul(x, x, n) + c) % n;
        p = y > x ? y - x : x - y;
        p = gcd(n, p);
        if (i == k)
            y = x, k += k;
    }
    return p;
}

void solve(LL n) 
{
    if (n == 1)
        return;
    if (MR(n)) 
	{
        mx = max(mx, n);
        return;
    }
    LL t = n;
    while (t == n)
        t = pol_rho(n, rand() % (n - 1));
    solve(t);
	solve(n / t);
}

int main() 
{
    srand(20000612);
	rand();
	int T;
    scanf("%d", &T);
    while (T--) 
	{
        LL x;
        mx = 0;
        read(x), solve(x);
        if (mx == x)
            puts("Prime");
        else
            printf("%lld\n", mx);
    }
    return 0;
}