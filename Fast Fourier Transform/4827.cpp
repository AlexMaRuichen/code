#include <stdio.h>
#include <math.h>

#include <algorithm>

template <typename T> inline bool tense(T &a, const T &b)
{
	return b < a ? a = b, true : false;
}

template <typename T> inline bool relax(T &a, const T &b)
{
	return a < b ? a = b, true : false;
}

using namespace std;

const int maxn = (1 << 18) + 10;
const int inf = 1e9;

struct cp
{
	double x, y;
	cp() {}
	cp(double x, double y) :x(x), y(y) {}
};

cp operator + (const cp &a, const cp &b)
{
	return cp(a.x + b.x, a.y + b.y);
}

cp operator - (const cp &a, const cp &b)
{
	return cp(a.x - b.x, a.y - b.y);
}

cp operator * (const cp &a, const cp &b)
{
	return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void DFT(cp *a, int len, int type)
{
	for (int i = 0, t = 0; i < len; i++)
	{
		if (t < i)
			swap(a[t], a[i]);
		for (int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	for (int i = 2; i <= len; i <<= 1)
	{
		cp wn(cos(2 * M_PI * type / i), sin(2 * M_PI * type / i));
		for (int j = 0; j < len; j += i)
		{
			cp w(1, 0), t;
			for (int k = 0; k < (i >> 1); k++, w = w * wn)
			{
				t = a[j + k + (i >> 1)] * w;
				a[j + k + (i >> 1)] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
		}
	}
	if (type < 0)
		for (int i = 0; i < len; i++)
			a[i].x /= len;
}

void FFT(cp *a, cp *b, int len)
{
	DFT(a, len, 1);
	DFT(b, len, 1);
	for (int i = 0; i < len; i++)
		a[i] = a[i] * b[i];
	DFT(a, len, -1);
}

cp a[maxn];
cp b[maxn];

int vala[maxn];
int valb[maxn];

int c, del, inv, ans = inf;

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &vala[i]);
		c += vala[i] * vala[i];
		del += vala[i];
		inv -= vala[i];
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &valb[i]);
		c += valb[i] * valb[i];
		del -= valb[i];
		inv += valb[i];
	}
	del <<= 1;
	inv <<= 1;
	for (int i = 0; i < n; i++)
		a[i].x = a[i + n].x = vala[i],
		b[i].x = valb[n - i - 1];
	int len;
	for (len = 1; len < n << 2; len <<= 1);
	FFT(a, b, len);
	for (int i = 0; i < len; i++)
		vala[i] = int(a[n - 1+ i].x + 0.5) << 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m; j++)
			tense(ans, c + j * j * n + del * j - vala[i]),
			tense(ans, c + j * j * n + inv * j - vala[i]);
	printf("%d\n", ans);
}