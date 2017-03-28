#include <stdio.h>

#include <algorithm>

#define lowbit(x) ((x) & (-(x)))

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

const int maxn = 5e4 + 10;
const int inf = 1e9;

int n;

struct BIT
{
	int v, p;
	BIT() {}
	BIT(int v, int p) :v(v), p(p) {}
	void init()
	{
		v = inf;
		p = -1;
	}
}bit[maxn];

bool operator < (const BIT &a, const BIT &b)
{
	return a.v < b.v;
}

void modify(int x, const BIT &y)
{
	for (int i = x; i; i -= lowbit(i))
		tense(bit[i], y);
}

int query(int x, int y)
{
	static BIT tmp;
	tmp.init();
	for (int i = x; i <= y; i += lowbit(i))
		tense(tmp, bit[i]);
	return tmp.p;
}

struct point
{
	int x, y, id;
	point() {}
	point(int x, int y, int id) :x(x), y(y), id(id) {}
}p[maxn];

bool operator < (const point &a, const point &b)
{
	return a.x ^ b.x ? a.x < b.x : a.y < b.y;
}

struct edge
{
	int x, y, len;
	edge() {}
	edge(int x, int y, int len) :x(x), y(y), len(len) {}
}e[maxn << 3];

bool operator < (const edge &a, const edge &b)
{
	return a.len < b.len;
}

int tot;

inline int dis(const point &a, const point &b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void gen()
{
	static int a[maxn], b[maxn];
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		a[i] = b[i] = p[i].y - p[i].x;
	sort(b + 1, b + n + 1);
	int m = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= m; i++)
		bit[i].init();
	for (int i = n; i; i--)
	{
		int pos = lower_bound(b + 1, b + m + 1, a[i]) - b;
		int ans = query(pos, m);
		if (~ans)
			e[++tot] = edge (p[i].id, p[ans].id, dis(p[i], p[ans]));
		modify(pos, BIT(p[i].x + p[i].y, i));
	}
}

void work()
{
	gen();
	
	for (int i = 1; i <= n; i++)
		swap(p[i].x, p[i].y);
	gen();

	for (int i = 1; i <= n; i++)
		p[i].x = -p[i].x;
	gen();

	for (int i = 1; i <= n; i++)
		swap(p[i].x, p[i].y);
	gen();
}

int fa[maxn];
int r[maxn];

inline void init()
{
	for (int i = 1; i <= n; i++)
		fa[i] = i, r[i] = 1;
}

inline void merge(int x, int y)
{
	if (r[x] > r[y])
		swap(x, y);
	else if (r[x] == r[y])
		++r[y];
	fa[x] = y;
}

int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

LL kruskal()
{
	LL ans = 0;
	init();
	sort(e + 1, e + tot + 1);
	for (int i = 1; i <= tot; i++)
	{
		int x = getfa(e[i].x);
		int y = getfa(e[i].y);
		if (x == y)
			continue;
		merge(x, y);
		ans += e[i].len;
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].x, &p[i].y), p[i].id = i;
	work();
	printf("%lld\n", kruskal());
}
