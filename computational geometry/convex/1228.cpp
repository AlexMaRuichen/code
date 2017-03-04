#include <stdio.h>
#include <math.h>
#include <string.h>

#include <algorithm>

#define leftpoint(j) (j - 1) % top + 1
#define rightpoint(j) j % top + 1

using namespace std;

const int maxn = 1e3 + 10;
const int inf = 1e9;
const double eps = 1e-7;

struct point
{
	int x, y;
	point() {}
	point(int x, int y) :x(x), y(y) {}
}p[maxn], start(inf, inf), last;

point operator + (const point &a, const point &b)
{
	return point(a.x + b.x, a.y + b.y);
}

point operator - (const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}


int operator * (const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

bool left(const point &a, const point &b, const point &p)
{
	return (p - a) * b <= 0;
}

inline double alpha(const point &p)
{
	return atan2(p.y, p.x);
}

bool equal (double x, double y)
{
	return fabs(x - y) < eps;
}

int dis(const point &a, const point &b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(const point &a, const point &b)
{
	static double a1, a2;
	return equal(a1 = alpha(a - start), a2 = alpha(b - start)) ?  dis(a, start) < dis(b, start) : a1 < a2;
}

int top;
point stack[maxn];
int cnt[maxn];

void Graham(int n)
{
	int id;
	start = point(inf, inf);
	for (int i = 1; i <= n; i++)
		if (start.y > p[i].y)
			id = i, start = p[i];
	swap(p[id], p[n--]);
	sort(p + 1, p + n + 1, cmp);
	top = 0;
	stack[++top] = start;
	stack[++top] = p[1];
	for (int i = 2; i <= n; i++)
	{
		while (top > 1 && left(stack[top - 1], p[i] - stack[top - 1], stack[top]))
			--top;
		stack[++top] = p[i];
	}
	if (top == 2)
		puts("NO");
	else
	{
		memset(cnt, 0, sizeof(cnt));
		++n;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= top; j++)
				if ((p[i] - stack[leftpoint(j)]) * (stack[rightpoint(j)] - stack[leftpoint(j)]) == 0)
				 	++cnt[j];
		for (int j = 1; j <= top; j++)
			if (cnt[j] < 3)
			{
				puts("NO");
				return;
			}
		puts("YES");
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &p[i].x, &p[i].y);
		if (n < 6)
			puts("NO");
		else
			Graham(n);
	}
}