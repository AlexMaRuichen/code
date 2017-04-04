#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

typedef long long LL;

int nim[17][17];

void init()
{
	static int v[400];
	for (int i = 1; i <= 16; i++)
		nim[i][0] = nim[0][i] = 0;
	for (int i = 1; i <= 16; i++)
		nim[i][1] = nim[1][i] = i;
	for (int i = 2; i <= 16; i++)
		for (int j = i; j <= 16; j++)
		{
			memset(v, 0, sizeof(v));
			for (int a = 0; a < i; a++)
				for (int b = 0; b < j; b++)
					v[nim[a][j] ^ nim[i][b] ^ nim[a][b]] = true;
			for (int a = 0; ; a++)
				if (!v[a])
				{
					nim[i][j] = nim[j][i] = a;
					break;
				}
		}
}

LL pow(LL x, LL y)
{
	if (x <= 16)
		return nim[x][y];
	LL m = 1, l = 1;
	while (true)
	{
		m = 1 << l;
		if (x >= m && x < (1 << (l << 1)))
			break;
		l <<= 1;
	}	
	LL p = x / m;
	LL s = y / m;
	LL t = y % m;
	LL d1 = pow(p, s);
	LL d2 = pow(p, t);
	return m * (d1 ^ d2) ^ pow(m >> 1, d1);
}

LL mul(LL x, LL y)
{
	if (x < y)
		swap(x, y);
	if (x <= 16)
		return nim[x][y];
	LL m = 1, l = 1;
	while (true)
	{
		m = 1 << l;
		if (x >= m && x < (1 << (l << 1)))
			break;
		l <<= 1;
	}
	LL p = x / m;
	LL q = x % m;
	LL s = y / m;
	LL t = y % m;
	LL c1 = mul(p, s);
	LL c2 = mul(p, t) ^ mul(q, s);
	LL c3 = mul(q, t);
	return ((c1 ^ c2) * m) ^ c3 ^ pow(m >> 1, c1);
}

int main()
{
	init();
	int n;
	while (scanf("%d", &n) == 1)
	{
		LL ans = 0;
		for (int i = 1, x, y, z; i <= n; i++)
			scanf("%d%d%d", &x, &y, &z),
			ans ^= mul(mul(x, y), z);
		puts(ans ? "No" : "Yes");
	}
}
