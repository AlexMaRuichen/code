#include <stdio.h>
#include <string.h>

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

const int maxn = 70;

typedef long long LL;

struct edge
{
	int to, len;
	edge *next;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {};
	void* operator new(size_t);
}*head[maxn], mem[maxn << 1], *p;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, z, head[y]);
}

LL dfs(int x, int fa, LL dis)
{
	LL ans = dis;
	for (edge *p = head[x]; p; p = p->next)
		if (p->to ^ fa)
			relax(ans, dfs(p->to, x, dis + p->len));
	return ans;
}

int cnt;
int fa[maxn];
int RANK[maxn];

int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

bool merge(int x, int y)
{
	x = getfa(x);
	y = getfa(y);
	if (x == y)
		return false;
	if (RANK[x] > RANK[y])
		swap(x, y);
	else if(RANK[x] == RANK[y])
		++RANK[y];
	return fa[x] = y, true;
}

typedef pair<int, pair<int, int> > EDGE;

EDGE e[maxn * maxn];

int x[maxn];
int y[maxn];

inline int dis(int a, int b)
{
	return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

LL kruskal(int n, int k)
{
	for (int i = 1; i <= n; i++)
		fa[i] = i, RANK[i] = 1;
	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n ; j++)
			e[++tot] = make_pair(dis(i, j), make_pair(i, j));
	sort(e + 1, e + tot + 1);
	int size = n;
	for (int i = 1; i <= tot; i++)
	{
		if (merge(e[i].second.first, e[i].second.second))
		{
			add(e[i].second.first, e[i].second.second, e[i].first);
			--size;
		}
		if (size == k)
		{
			LL ans = ~0ull >> 1;
			for (int j = 1; j <= n; j++)
				relax(ans, dfs(j, j, 0));
			return ans;
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int g = 1; g <= T; g++)
	{
		memset(head, 0, sizeof(head));
		p = mem;
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &x[i], &y[i]);
		printf("Case #%d: %lld\n", g, kruskal(n, k));
	}
}