#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

typedef long long LL;

const int maxn = 1e4 + 10;
const int maxm = 1e5 + 10;

struct edge
{
	int to, len;
	edge *next;
	edge() {}
	edge(int to, int len, edge *next) :to(to), len(len), next(next) {}
	void* operator new(size_t);
}*head[maxn], *rev[maxn], mem[maxm << 1];

void* edge :: operator new(size_t)
{
	static edge *p = mem;
	return p++;
}

void add(int x, int y, int z)
{
	head[x] = new edge(y, z, head[x]);
	rev[y] = new edge(x, z, rev[y]);
}

typedef pair<int, int> point;
point heap[maxm];
bool v[maxn];
int f[maxn];
int size;
int n, m, k;

void dijkstra()
{
	size = 0;
	memset(f, 0x3f, sizeof(f));
	heap[++size] = point(0, n);
	f[n] = 0;
	while (size)
	{
		int x = heap[1].second;
		pop_heap(heap + 1, heap + size-- + 1, greater<point>());
		if (v[x])
			continue;
		v[x] = true;
		for (edge *p = rev[x]; p; p = p->next)
			if (f[p->to] > f[x] + p->len)
			{
				f[p->to] = f[x] + p->len;
				heap[++size] = point(f[p->to], p->to);
				push_heap(heap + 1, heap + size + 1, greater<point>());
			}
	}
}

struct data
{
	int id;
	LL dis, g;
	data() {}
	data(int id, LL dis, LL g) :id(id), dis(dis), g(g) {}
};

priority_queue <data> pq;

bool operator < (const data &a, const data &b)
{
	return a.g ^ b.g ? a.g > b.g : a.dis > b.dis;
}

LL Astar()
{
	static LL last;
	size = 0;
	pq.push(data(1, 0, f[1]));
	while (!pq.empty())
	{
		int x = pq.top().id;
		LL dis = pq.top().dis;
		if (x == n)
		{
			if (last ^ dis)
				last = dis, --k;
			if (!k)
				return dis;
		}
		pq.pop();
		for (edge *p = head[x]; p; p = p->next)
			pq.push(data(p->to, dis + p->len, dis + p->len + f[p->to]));
	}
	return -1;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x, y, z; i <= m; i++)
		scanf("%d%d%d", &x, &y, &z),
		add(x, y, z);
	dijkstra();
	if (f[1] == f[0])
		puts("-1");
	else
		printf("%I64d\n", Astar());
}