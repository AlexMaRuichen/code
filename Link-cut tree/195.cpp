#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 200010;

struct Splay
{
	Splay *ls, *rs, *fa;
	int sum;
	bool val;
	Splay();
	Splay(int x);
	void update();
	void* operator new(size_t);
}mem[maxn], nil, *null = &nil;

Splay :: Splay()
{
	ls = rs = fa = this;
	sum = val = 0;
}

Splay :: Splay(int x)
{
	ls = rs = fa = null;
	sum = val = x;
}

void Splay :: update()
{
	sum = ls->sum + rs->sum + val;
}

void* Splay :: operator new(size_t)
{
	static Splay *p = mem;
	return p++;
}

void zig(Splay *x)
{
	static Splay *y;
	y = x->fa;
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if (y == y->fa->ls)
		y->fa->ls = x;
	else if (y == y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
	y->update();
}

void zag(Splay *x)
{
	static Splay *y;
	y = x->fa;
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if (y == y->fa->ls)
		y->fa->ls = x;
	else if (y == y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
	y->update();
}

void splay(Splay *x)
{
	static Splay *y, *z;
	while (x == x->fa->ls || x == x->fa->rs)
	{
		y = x->fa;
		z = y->fa;
		if (x == y->ls)
		{
			if (y == z->ls)
				zig(y);
			zig(x);
		}
		else 
		{
			if (y == z->rs)
				zag(y);
			zag(x);
		}
	}
	x->update();
}

Splay* access(Splay *x)
{	
	Splay *y = null;
	while (x != null)
	{
		splay(x);
		x->rs = y;
		x->update();
		y = x;
		x = x->fa;
	}
	return y;
}

void cut(Splay *x)
{
	access(x);
	splay(x);
	x->ls->fa = null;
	x->ls = null;
	x->update();
}

void link(Splay *x, Splay *y)
{
	splay(x);
	x->fa = y;
}

struct node
{
	int pos, opt;
	Splay *x, *y;
	node() {}
	node(int pos, int opt, Splay *x, Splay *y) :pos(pos), opt(opt), x(x), y(y) {}
}q[maxn << 2];

bool operator < (const node &a, const node &b)
{
	return a.pos ^ b.pos ? a.pos < b.pos : a.opt < b.opt;
}

int ans[maxn];
int l[maxn];
int r[maxn];

Splay *b[maxn];

int main()
{
	int n, m, cnt, tot = 0;
	scanf("%d%d", &n, &m);
	b[cnt = 1] = new Splay(1);
	l[1] = 1;
	r[1] = n;
	Splay *cur = new Splay(0);
	link(cur, b[1]);
	for (int i = 1, x, y, opt, k; i <= m; i++)
	{
		scanf("%d", &opt);
		if (!opt)
		{
			++cnt;
			scanf("%d%d", &l[cnt], &r[cnt]);
			b[cnt] = new Splay(1);
			q[++tot] = node(1, i - m, b[cnt], cur);
		}
		else if (opt == 1)
		{
			scanf("%d%d%d", &x, &y, &k);
			x = max(x, l[k]);
			y = min(y, r[k]);
			if (x <= y)
			{
				Splay *tmp = new Splay(0);
				if (x > 1)
					link(tmp, cur);
				q[++tot] = node(x, i - m, tmp, b[k]);
				q[++tot] = node(y + 1, i - m, tmp, cur);
				cur = tmp;
			}
		}
		else
		{
			scanf("%d%d%d", &k, &x, &y);
			q[++tot] = node(k, i, b[x], b[y]);
		}
	}
	sort(q + 1, q + tot + 1);
/*	for (int i = 1; i <= tot; i++)
		printf("%d %d %d %d\n", q[i].pos, q[i].pos, q[i].x - mem, q[i].y - mem);*/
	memset(ans, -1, sizeof(ans));
	for (int i = 1, k = 1; i <= n; i++)
		for (; k <= tot && q[k].pos == i; k++)
			if (q[k].opt > 0)
			{
				access(q[k].x);
				splay(q[k].x);
				ans[q[k].opt] = q[k].x->sum;
				Splay *tmp = access(q[k].y);
				splay(q[k].y);
				ans[q[k].opt] += q[k].y->sum;
				access(tmp);
				splay(tmp);
				ans[q[k].opt] -= tmp->sum << 1; 
			}
			else
			{
				cut(q[k].x);
				link(q[k].x, q[k].y);
			}
	for (int i = 1; i <= m; i++)
		if (~ans[i])
			printf("%d\n", ans[i]);
}	