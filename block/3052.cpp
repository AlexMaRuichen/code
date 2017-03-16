#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace std;

const int LOG = 17;
const int maxn = 100010;

typedef long long LL;

struct query
{
	int x, y, pos;
}q[maxn];

struct mod
{
	int x, v1, v2, pos;
}m[maxn];

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
	head[y] = new edge(x, head[y]);
}

int a[maxn];
int v[maxn];
int w[maxn];
int dep[maxn];
int cnt[maxn];
bool vis[maxn];
int fa[LOG + 1][maxn];
LL now;

inline void Xor(int x)
{
	(vis[x] ^= 1) ? now += v[a[x]] * w[++cnt[a[x]]] : now -= v[a[x]] * w[cnt[a[x]]--];
}

inline void path(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	while (dep[x] > dep[y])
		Xor(x), x = fa[0][x];
	while (x ^ y)
		Xor(x), Xor(y), x = fa[0][x], y = fa[0][y];
}

void change(const mod &x, bool flag)
{
	if (flag)
	{
		a[x.x] = x.v1;
		if (vis[x.x])
		{
			cnt[x.v2] ? now -= v[x.v2] * 1ll * w[cnt[x.v2]] : 1;
			--cnt[x.v2];
			++cnt[x.v1];
			cnt[x.v1] ? now += v[x.v1] * 1ll * w[cnt[x.v1]] : 1;
		}
		
	}
	else
	{
		a[x.x] = x.v2;
		if (vis[x.x])
		{
			cnt[x.v1] ? now -= v[x.v1] * 1ll * w[cnt[x.v1]] : 1;
			--cnt[x.v1];
			++cnt[x.v2];
			cnt[x.v2] ? now += v[x.v2] * 1ll * w[cnt[x.v2]] : 1;
		}
	}
}

void dfs(int x, int d)
{
	dep[x] = d;
	for (int i = 1; i <= LOG; i++)
		fa[i][x] = fa[i - 1][fa[i - 1][x]];
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa[0][x])
			fa[0][p->to] = x,
			dfs(p->to, d + 1);
}

int getfa(int x, int y)
{
	for (int i = 0; i <= LOG; i++)
		if ((1 << i) & y)
			x = fa[i][x];
	return x;
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	x = getfa(x, dep[x] - dep[y]);
	if (x == y)
		return x;
	for (int i = LOG; i; i--)
		if (fa[i][x] ^ fa[i][y])
			x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

int block;
int top;
int DIV;
int stack[maxn];
int belong[maxn];
LL ans[maxn];

bool operator < (const query &a, const query &b)
{
	return belong[a.x] == belong[a.y] ? 
	(belong[a.y] == belong[a.y] ? a.pos < b.pos : belong[a.y] < belong[b.y]) :
	belong[a.x] < belong[a.y];
}

void getblock(int x, int fa)
{
	int last = top;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			getblock(p->to, x);
			if (top - last >= block)
			{
				++DIV;
				while (top ^ last)
					belong[stack[top--]] = DIV;
			}
		}
	stack[++top] = x;
}

int b[maxn];

int main()
{
	int N, M, Q;
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= M; i++)
		scanf("%d", &v[i]);
	for (int i = 1; i <= N; i++)
		scanf("%d", &w[i]);
	for (int i = 1, x, y; i < N; i++)
	{
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= N; i++)
		scanf("%d", &a[i]);
	int cntq = 0, cntm = 0;
	for (int i = 1, opt, x, y; i <= Q; i++)
	{
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1)
		{
			++cntq;
			q[cntq].pos = cntq;
			q[cntq].x = x;
			q[cntq].y = y;
		}
		else
		{
			++cntm;
			m[cntm].pos = cntq;
			m[cntm].v1 = a[x];
			m[cntm].v2 = a[x] = y;
			m[cntm].x = x;
		}
	}
	Q = cntq;
	int T = cntm;
	block = cntm ? pow(N, 2.0 / 3.0) + 1 : sqrt(N) + 1;
	dfs(1, 1);
	getblock(1, 1);
	for (int i = 1; i <= Q; i++)
		if (belong[q[i].x] > belong[q[i].y])
		 	swap(q[i].x, q[i].y);
	sort(q + 1, q + Q + 1);
	for (int i = 1, l = 1, r = 1, lca; i <= Q; i++)
	{
		path(l, q[i].x);
		path(r, q[i].y);
		Xor(lca = LCA(l = q[i].x, r = q[i].y));
		while (T && m[T].pos >= q[i].pos)
			change(m[T--], true);
		while (T < cntm && m[T + 1].pos < q[i].pos)
			change(m[++T], false);
		ans[q[i].pos] = now;
		Xor(lca);
	}
	for (int i = 1; i <= Q; i++)
		printf("%lld\n", ans[i]);
}
