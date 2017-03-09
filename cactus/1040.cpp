#include <stdio.h>

#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 1e6 + 10;
const int inf = ~0u >> 2;

struct edge
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*old[maxn], *head[maxn], mem[maxn << 2];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void oadd(int x, int y)
{
	old[x] = new edge(y, old[x]);
	old[y] = new edge(x, old[y]);
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
}

int cnt, top;
int dep[maxn];
int low[maxn];
int stack[maxn];

void dfs(int x, int fa)
{
	dep[x] = low[x] = dep[fa] + 1;
	stack[++top] = x;
	for (edge *p = old[x]; p; p = p->next)
		if (p->to ^ fa)
		{
			if (!dep[p->to])
			{
				dfs(p->to, x);
				low[x] = min(low[x], low[p->to]);
				if (low[p->to] > dep[x])
					add(x, p->to);
			}
			else if (dep[p->to] < dep[x])
			{
				++cnt;
				low[x] = min(low[x], dep[p->to]);
				int now = 0, pos = top;
				while ((now = stack[pos--])^ p->to)
					add(cnt, now);
				add(p->to, cnt);
			}
		}
	--top;
}

void print(int x, int fa)
{
	printf("%d:", x);
	for (edge *p = head[x]; p; p = p->next)
		printf("%d ", p->to);
	puts("");
	for (edge *p = head[x]; p; p = p->next)
		print(p->to, x);
}

int n, m;
int a[maxn];
ll f[2][maxn];
ll g[2][maxn];

void dp(int x, int fa)
{
//	printf("%d %d\n", x, fa);
	if (x <= n)
	{
		f[0][x] = 0, f[1][x] = a[x];
		for (edge *p = head[x]; p; p = p->next)
		{
			dp(p->to, x);
			if (p->to <= n)
				f[0][x] += max(f[0][p->to], f[1][p->to]),
				f[1][x] += f[0][p->to];
		}
	}
	else
	{
		for (edge *p = head[x]; p; p = p->next)
			dp(p->to, x);
		int top = 0;
		g[0][++top] = f[0][fa];
		g[1][top] = f[1][fa];
//		printf("%d ", fa);
		for (edge *p = head[x]; p; p = p->next)
//			printf("%d ", p->to),
			g[0][++top] = f[0][p->to],
			g[1][top] = f[1][p->to];
//		puts("");
		for (int i = top - 1; i; i--)
			g[0][i] += max(g[0][i + 1], g[1][i + 1]),
			g[1][i] += g[0][i + 1];
		f[0][fa] = g[0][1];
		for (int i = 1; i < top ; i++)
			g[0][i] -= max(g[0][i + 1], g[1][i + 1]),
			g[1][i] -= g[0][i + 1];
		g[1][top] = -inf;	
		for (int i = top - 1; i; i--)
			g[0][i] += max(g[0][i + 1], g[1][i + 1]),
			g[1][i] += g[0][i + 1];
		f[1][fa] = g[1][1];
	}
}

ll ans = 0;

int main()
{
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++)
		scanf("%d%d", &a[i], &x),
		oadd(i, x);
	cnt = n;
	for (int i = 1; i <= n; i++)
		if (!dep[i])
			dfs(i, i),
			dp(i, i),
			ans += max(f[0][i], f[1][i]);
//	print(1, 1);
	printf("%lld\n", ans);
}