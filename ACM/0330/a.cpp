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

const int maxn = 5e4 + 10;
const double eps = 1e-9;
const double inf = 1e100;

struct point
{
	double x, y;
	point() {}
	point(double x, double y) :x(x), y(y) {}
}p[maxn], q[maxn];

point operator + (const point &a, const point &b)
{
	return point(a.x + b.x, a.y + b.y);
}

point operator - (const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}

double operator * (const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

double operator ^ (const point &a, const point &b)
{
	return a.x * b.x + a.y * b.y;
}

double dis(const point &a, const point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void check(point *p, int n)
{
	for (int i = 1; i < n - 1; i++)
	{
		double cross = (p[i + 1] - p[i]) * (p[i + 2] - p[i]);
		if (cross > eps)
			return ;
		else if (cross < -eps)
		{
			reverse(p + 1, p + n + 1);
			return ;
		}
	}
}

double get(const point &a, const point &b, const point &c)
{
	if (dis(a, b) < eps)
		return dis(b, c);
	else if (((b - a) ^ (c - a)) < -eps)
		return dis(a, c);
	else if (((a - b) ^ (c - b)) < -eps)
		return dis(b, c);
	else
		return fabs(((b - a) * (c - a)) / dis(a, b));
}

double get(const point &a, const point &b, const point &c, const point &d)
{
	return min(min(get(a, b, c), get(a, b, d)), min(get(c, d, a), get(c, d, b)));
}

double rotate(point *p, point *q, int n, int m)
{
	int idq = 1, idp = 1;
	for (int i = 1; i <= n; i++)
		if (p[i].y < p[idp].y)
			idp = i;
	for (int i = 1; i <= m; i++)
		if (q[i].y > q[idq].y)
			idq = i;
	p[n + 1] = p[1];
	q[m + 1] = q[1];
	double tmp, ans = inf;
	for (int i = 1; i <= n; i++)
	{
		while ((tmp = ((q[idq + 1] - p[idp + 1]) * (p[idp] - p[idp + 1]) - 
				      (q[idq] - p[idp + 1]) * (p[idp] - p[idp + 1]))) > eps)
			idq = (idq == m ? 1 : idq + 1);
		if (tmp < -eps)
			tense(ans, get(p[idp], p[idp + 1], q[idq]));
		else
			tense(ans, get(p[idp], p[idp + 1], q[idq], q[idq + 1]));
		idp = (idp == n ? 1 : idp + 1);
	}
	return ans;
}

int n, m;

int main()
{
	double x, y;
	while (scanf("%d%d", &n, &m) && n && m)
	{
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf", &x, &y),
			p[i] = point(x, y);
		for (int i = 1; i <= m; i++)
			scanf("%lf%lf", &x, &y),
			q[i] = point(x, y);
		check(p, n);
		check(q, m);
		printf("%.5lf\n", min(rotate(p, q, n, m), rotate(q, p, m, n)));
	}
}