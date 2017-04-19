#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <map>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

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
	while (ch < '0')
		ch = getc();
	while (ch >= '0')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}

const int maxn = 1e8 + 10;
int N;
typedef long long LL;

int cnt;
int prime[5761460];
int mu[maxn];
int w[maxn];
int mu2[maxn];


void sieve()
{
	mu[1] = w[1] = 1;
	int i, *j;
	for (i = 2; i <= N; i++)
	{
		if (!w[i])
			w[i] = 2, prime[++cnt] = i, mu[i] = -1;
		for (j = prime + 1; i * *j <= N && *j; j++)
		{
			if (i % *j == 0)
			{
				w[i * *j] = w[i];
				break;
			}
			else
			{
				w[i * *j] = w[i] << 1;
				mu[i * *j] = -mu[i];
			}
		}
	}
	for (i = 1; i <= N; i++)
		mu2[i] = mu2[i - 1] + mu[i] * mu[i];
	for (i = 1; i <= N; i++)
		w[i] += w[i - 1];
}

map <LL, LL> PHI, W, MU2;

inline LL calc_mu2(LL x)
{
	if (x <= N)
		return mu2[x];
	if (MU2.count(x))
		return MU2[x];
	LL ans = 0;
	for (LL i = 1; i * i <= x; i++)
		ans += mu[i] * (x / i / i);
	return MU2[x] = ans;
}

inline LL calc_w_LL(LL x)
{
	if (W.count(x))
		return W[x];
	LL ans = 0;
	for (LL i = 1, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans += (calc_mu2(last) - calc_mu2(i - 1)) * (x / i);
	}
	return W[x] = ans;
}

inline int calc_w_int(int x)
{
	if (x <= N)
		return w[x];
	if (W.count(x))
		return W[x];
	int ans = 0;
	for (int i = 1, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans += (calc_mu2(last) - calc_mu2(i - 1)) * 1ll * (x / i);
	}
	return W[x] = ans;
}

inline LL calc_w(LL x)
{
	return x <= (1 << 27) ? calc_w_int(x) : calc_w_LL(x);
}

inline LL calc_phi(LL x)
{
	if (PHI.count(x))
		return PHI[x];
	LL ans = 0;
	for (LL i = 1, last; i <= x; i = last + 1)
	{
		last = x / (x / i);
		ans += (calc_w(last) - calc_w(i - 1)) * (x / i);
	}
	return PHI[x] = ans;
}

int T;
LL a[10010];

int main()
{
	LL mx = 0;
	read(T);
	for (int i = 1; i <= T; i++)
		read(a[i]), relax(mx, a[i]);
	N = pow(mx, 2.0 / 3.0);
	sieve();
	for (int i = 1; i <= T; i++)
		printf("%lld\n", calc_phi(a[i]));
}
