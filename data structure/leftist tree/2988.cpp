#include <stdio.h>

#include <algorithm>

using namespace std;

const int maxn = 100010;

struct heap
{
	heap *ls, *rs;
	int val, dis;
	heap();
	heap(int x);
	void* operator new(size_t);
}*root[maxn], mem[maxn], nil, *null = &nil;

void* heap :: operator new(size_t)
{
	static heap *p = mem;
	return p++;
}

heap :: heap()
{
	ls = rs = this;
	val = 0;
	dis = -1;
}

heap :: heap(int x)
{
	ls = rs = null;
	val = x;
	dis = 0;
}

heap* merge(heap *x, heap *y)
{
	if (x == null)
		return y;
	if (y == null)
		return x;
	if (x->val > y->val)
		swap(x, y);
	x->rs = merge(x->rs, y);
	if (x->ls->dis < x->rs->dis)
		swap(x->ls, x->rs);
	x->dis = x->rs->dis + 1;
	return x;
}

int fa[maxn];
int Rank[maxn];

int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

void merge(int x, int y)
{
	if (Rank[x] > Rank[y])
		swap(x, y);
	else if (Rank[x] == Rank[y])
		++Rank[y];
	fa[x] = y;
	root[y] = merge(root[y], root[x]);
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		root[i] = new heap(i),
		fa[i] = i;
	while(m--)
	{
		int opt;
		scanf("%d", &opt);
		if (opt == 0)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x = getfa(x);
			y = getfa(y);
			if (x ^ y)
				merge(x, y);
		}
		else
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", root[getfa(x)]->val);
		}
	}
}