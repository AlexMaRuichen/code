#include <stdio.h>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;

struct edge 
{
	int to;
	edge *next;
	edge() {}
	edge(int to, edge *next) :to(to), next(next) {}
	void* operator new(size_t);
}*head[maxn], emem[maxn];

void* edge :: operator new(size_t)
{
	static edge *p = emem;
	return p++;
}

void add(int x, int y)
{
	head[x] = new edge(y, head[x]);
}

struct heap
{
	heap *ls, *rs;
	int val, dis, size;
	heap();
	heap(int x);
	void* operator new(size_t);
}*root[maxn], mem[maxn], nil, *null=&nil;

void* heap :: operator new(size_t)
{
	static heap *p = mem;
	return p++;
}

heap :: heap()
{
	ls = rs = this;
	val = size = 0;
	dis = -1;
}

heap :: heap(int x)
{
	ls = rs = null;
	val = x;
	dis = 0;
	size = 1;
}

heap* merge(heap *x, heap *y)
{
	if (x == null)
		return y;
	if (y == null)
		return x;
	if (x->val < y->val)
		swap(x, y);
	x->rs = merge(x->rs, y);
	x->size = x->ls->size + x->rs->size + 1;
	if (x->ls->dis < x->rs->dis)
		swap(x->ls, x->rs);
	x->dis = x->rs->dis + 1;
	return x;
}

void pop(heap *&x)
{
	x = merge(x->ls, x->rs);
}

int sum[maxn];
int l[maxn];
long long ans;
int n, m;

void dfs(int x)
{
	for (edge *p = head[x]; p; p = p->next)
	{
		dfs(p->to);
		root[x] = merge(root[x], root[p->to]);
		sum[x] += sum[p->to];
		while (sum[x] > m)
		{
			sum[x] -= root[x]->val;
			pop(root[x]);
		}
	}
	ans = max(ans, root[x]->size * 1ll * l[x]);
}

int main()
{
	int source;
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n; i++)
	{
		scanf("%d%d%d", &x, &y, &l[i]);
		if (!x)
			source = i;
		else
			add(x, i);
		root[i] = new heap(y);
		sum[i] = y;
	}
	dfs(source);
	printf("%I64d\n", ans);
}