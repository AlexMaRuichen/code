#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <functional>

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

const int maxn = 1010;
const int maxm = 40010;
const int maxq = 20010;
const LL inf = 1e17;


struct edge
{
	int to, len;
	edge *next;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], mem[maxm], *p = mem;

void* edge :: operator new(size_t)
{
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	head[y] = new edge(x, z, head[y]);
}

int qx[maxq];
int qy[maxq];
LL ans[maxq];
LL f[maxn][maxn];
bool v[maxn];
int a[maxn];
typedef pair <LL, int> point;
point heap[maxm];
int n;

void dijkstra(int S)
{
	int size = 0;
	LL *dis = f[S];
	memset(v, 0, sizeof(v));
	heap[++size] = point(0, S);
	dis[S] = 0;
	while (size)
	{
		int x = heap[1].second;
		pop_heap(heap + 1, heap + size-- + 1, greater <point> ());
		if (v[x]) 
			continue;
		v[x] = true;
		for (edge *p = head[x]; p; p = p->next)
			if (a[p->to] <= a[S] && tense(dis[p->to], dis[x] + p->len))
			{
				heap[++size] = point(dis[p->to], p->to);
				push_heap(heap + 1, heap + size + 1, greater <point> ());
			}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int m, q, x, y, z;
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0)
			return 0;
		p = mem;
		memset(f, 0x3f, sizeof(f));
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &x, &y, &z),
			add(x, y, z);
		for (int i = 1; i <= n; i++)
			dijkstra(i);
		scanf("%d", &q);
		for (int i = 1; i <= q; i++)
			scanf("%d%d", &qx[i], &qy[i]),
			ans[i] = inf;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= q; j++)
				tense(ans[j], f[i][qx[j]] + f[i][qy[j]] + a[i]);
		for (int i = 1; i <= q; i++)
			printf("%lld\n", ans[i] < inf ? ans[i] : -1);
		puts("");
	}
}
