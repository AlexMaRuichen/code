#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int maxn = 1e3 + 10;
const double eps = 1e-6;

inline bool equal(double x, double y)
{
	return fabs(x - y) < eps;
}

struct point
{
	double x, y;
	bool flag;
	point() {}
	point(double x, double y) :x(x), y(y) {}
}p[maxn << 1];

bool operator != (const point &a, const point &b)
{
	return !equal(a.x, b.x) && !equal(a.y ,b.y);
}

point operator + (const point &x, const point &y)
{
	return point(x.x + y.x, x.y + y.y);
}

point operator - (const point &x, const point &y)
{
	return point(x.x - y.x, x.y - y.y);
}

point operator * (const point &x, double y)
{
	return point(x.x * y, x.y * y);
}

double operator ^ (const point &x, const point &y)
{
	return x.x * y.x + x.y * y.y;
}

double operator * (const point &x, const point &y)
{
	return x.x * y.y - x.y * y.x;
}

struct line
{
	point p, v;
	line() {}
	line(const point &p, const point &v) :p(p), v(v) {}
};

point intersect(const line &x, const line &y)
{
	point u = x.p - y.p;
	double tmp = (y.v * u) / (x.v * y.v);
	return x.p + x.v * tmp;
}

struct seg
{
	double l, r;
	seg() {}
	seg(double l, double r) :l(l), r(r) {}
}s[maxn << 1];

bool cmp(const seg &x, const seg &y)
{
	return equal(x.l, y.l) ? x.r < y.r : x.l < y.l;
}

int cnt;

int main()
{
	line home, road;
	point homel, homer, null(1e9, 1e9), roadl, roadr;
	null.flag = false;
	double x, y, z;
	while (scanf("%lf%lf%lf", &x, &y, &z))
	{
		double ans = 0;
		cnt = 0;
		if (equal(x, 0) && equal(y, 0) && equal(z, 0))
			return 0;
		homel = point(x, z);
		homer = point(y, z);
//		printf("%lf %lf %lf %lf\n", home.p.x, home.p.y, home.v.x, home.v.y);
		scanf("%lf%lf%lf", &x, &y, &z);
		road = line(point(x, z), point(y, z) - point(x, z));
		roadl = point(x, z), roadr = point(y, z);
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf%lf", &x, &y, &z);
			if (z > homel.y || z < roadl.y  || equal(z, homel.y) || equal(z, roadl.y))
				continue;
			point lint = intersect(line(homer, point(x, z) - homer), road);
			point rint = intersect(line(homel, point(y, z) - homel), road);
			if (lint.x > roadr.x || rint.x < roadl.x)
				continue;
			s[++cnt].l = max(roadl.x, lint.x);
			s[cnt].r = min(roadr.x, rint.x);
		}
		sort(s + 1, s + cnt + 1, cmp);
		double lastx = roadl.x;
		if (cnt)
		{
			for (int i = 1; i <= cnt; i++)
			{
				if(s[i].l > lastx + eps)  
				{
					ans = max(ans, s[i].l - lastx);  
					lastx = s[i].r;  
				}  
				else if(s[i].r > lastx + eps)  
					lastx = s[i].r;  
			}
			if(lastx + eps < roadr.x)  
				ans = max(ans, roadr.x - lastx);  
		}
		else
			ans = roadr.x - roadl.x;
		equal(ans, 0) ? puts("No View") : printf("%.2f\n", ans);
	}
}