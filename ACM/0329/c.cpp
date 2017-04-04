#include <stdio.h>
#include <math.h>

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

template <typename T> inline T abs(const T &a)
{
	return a < 0 ? -a : a;
}

template <typename T> inline bool equal(const T &a, const T &b)
{
	static const double eps = 1e-6;
	return abs(a - b) < eps;
}

const int maxn = 1510;
const double PI = 3.141592653589793238462;

int x[maxn << 1];
int y[maxn << 1];

int bx, by;

pair <double, int> p[maxn << 2];


bool cmp (const pair <double, int> &p1, const pair <double, int> &p2)
{
	return equal(p1.first, p2.first) ? p1.second > p2.second : p1.first < p2.first;
}

int main()
{
	int T, n;
	scanf("%d", &T);
	while (T--)
	{
		int ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d%d", &x[i], &y[i], &x[i + n], &y[i + n]);
		scanf("%d%d", &bx, &by);
		for (int i = 1; i <= n; i++)
		{
			x[i] -= bx;
			y[i] -= by;
			x[i + n] -= bx;
			y[i + n] -= by;
		}
		for (int i = 1; i <= n; i++)
			if (x[i] * y[i + n] - x[i + n] * y[i] < 0)
				swap(x[i], x[i + n]),
				swap(y[i], y[i + n]);
		int cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			double alpha1 = atan2(y[i], x[i]);
			double alpha2 = atan2(y[i + n], x[i + n]);
			if (alpha1 > alpha2)
			{
				p[++cnt] = make_pair(alpha1, 1);
				p[++cnt] = make_pair(PI + 1, -1);
				p[++cnt] = make_pair(- PI - 1, 1);
				p[++cnt] = make_pair(alpha2, -1);
			}
			else
			{
				p[++cnt] = make_pair(alpha1, 1);
				p[++cnt] = make_pair(alpha2, -1);
			}
		}
		sort(p + 1, p + cnt + 1, cmp);
		for (int i = 1, cur = 0; i <= cnt; i++)
			relax(ans, cur += p[i].second);
		printf("%d\n", ans);
	}
}