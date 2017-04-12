#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 210;

double mem[2][maxn];

__attribute__((optimize(2))) inline char getc()
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

__attribute__((optimize(2))) inline void read(register int &x)
{
	static char ch = getc();
	x=0;
	while(ch < '0' || ch > '9')
		ch = getc();
	while(ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + ch - '0', ch = getc();
}

__attribute__((optimize(2))) int main()
{
//	freopen("a.in", "r", stdin);
	int n, m, l, r, w;
	double *f, *g, ans;
	register int i;
	while (true)
	{
		read(n);
		read(m);
		read(l);
		read(r);
		if (!n)
			break;
		ans = 0;
		f = mem[0];
		g = mem[1];
		for (i = 1; i <= n; i++)
			g[i] = i == 1;
		while (m--)
		{
			read(w);
			for (i = 1; i <= n; i++)
				f[i] = (g[i - w < 1 ? n + i - w : i - w] + g[i + w > n ? i + w - n : i + w]) / 2;
			swap(f, g);
		}
		for (i = l; i <= r; i++)
			ans += g[i];
		printf("%.4lf\n", ans);
	}
}