#include <stdio.h>
#include <algorithm>
using namespace std;

const int maxn = 300010;

typedef long long LL;

struct heap
{
	heap *ls, *rs;
	LL val, dis, mul, add, lab;
	heap();
	heap(LL x, int lab);
	void* operator new(size_t);
	void push_down();
	void update();
	void pow(LL x);
	void plus(LL x);
}*root[maxn], *node[maxn], mem[maxn], nil, *null = &nil;

void* heap :: operator new(size_t)
{
	static heap *p = mem;
	return p++;
}

heap :: heap()
{
	ls = rs = this;
	add = val = 0;
	dis = -1;
	mul = 1;
}

heap :: heap(LL x, int l)
{
	ls = rs = null;
	lab = l;
	val = x;
	dis = add = 0;
	mul = 1;
}

void heap :: push_down()
{
	if (mul ^ 1)
	{
		ls->pow(mul);
		rs->pow(mul);
		mul = 1;
	}
	if (add)
	{
		ls->plus(add);
		rs->plus(add);
		add = 0;
	}
}

void heap :: pow(LL x)
{
	val *= x;
	add *= x;
	mul *= x;
}

void heap :: plus(LL x)
{
	val += x;
	add += x;
}

void heap :: update()
{
	if (ls->dis < rs->dis)
		swap(ls, rs);
	dis = rs->dis + 1;
}

heap* merge(heap *x, heap *y)
{
	if (x == null)
		return y;
	if (y == null)
		return x;
	x->push_down();
	y->push_down();
	if (x->val > y->val)
		swap(x, y);
	x->rs = merge(x->rs, y);
	x->update();
	return x;
}

void pop(heap *&x)
{
	x = merge(x->ls, x->rs);
}


int ans[maxn];
int die[maxn];
LL h[maxn];
bool v[maxn];
bool a[maxn];
LL b[maxn];
int n, m;
int dep[maxn];
int pos[maxn];
int fa[maxn];

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

void bfs()
{
	static int q[maxn], r, t;
	q[++r] = 1;
	while(r ^ t)
	{
		int x = q[++t];
		dep[x] = dep[fa[x]] + 1;
		for(edge *p = head[x]; p; p = p->next)
			q[++r] = p->to;
	}
	for(int j=n; j; j--)
	{
		int x = q[j];
		for(edge *p = head[x]; p; p = p->next)
			root[x] = merge(root[x], root[p->to]);
		while(root[x] != null && root[x]->val < h[x] )
		{
			die[root[x]->lab] = x;
			++ans[x];
			root[x]->push_down();
			root[x]=merge(root[x]->ls, root[x]->rs);
		}
		if(root[x] != null)
		{
			if(a[x] == 0)
				root[x]->plus(b[x]);
			else
				root[x]->pow(b[x]);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &h[i]), root[i] = null;
	for (int i = 2; i <= n; i++)
	{
		scanf("%d%d%lld", &fa[i], &a[i], &b[i]);
		add(fa[i], i);
	}
	for (int i = 1, x; i <= m; i++)
	{
		scanf("%lld%d", &x, &pos[i]);
		node[i] = new heap(x, i);
		root[pos[i]] = merge(root[pos[i]], node[i]);
	}
	bfs();
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	for (int i = 1; i <= m; i++)
		printf("%d\n", dep[pos[i]] - dep[die[i]]);
}