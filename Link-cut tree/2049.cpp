#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int maxn = 10010;

struct Splay
{
	Splay *ls, *rs, *fa;
	bool rev;
	Splay();
	Splay(int x);
	void push_down();
	void reverse();
	void* operator new(size_t);
}*ptr[maxn], mem[maxn], nil, *null = &nil;

void* Splay :: operator new(size_t)
{
	static Splay *p = mem;
	return p++;
}

Splay :: Splay()
{
	ls = rs = fa = this;
	rev = false;
}

Splay :: Splay(int x)
{
	ls = rs = fa = null;
	rev = false;
}

void Splay :: push_down()
{
	if (this == fa->ls || this == fa->rs)
		fa->push_down();
	if (rev)
	{
		ls->reverse();
		rs->reverse();
		rev = false;
	}
}

void Splay :: reverse()
{
	rev ^= 1;
	swap(ls, rs);
}

void zig(Splay *x)
{
	Splay *y = x->fa;
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if (y == y->fa->ls)
		y->fa->ls = x;
	else if (y == y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
}

void zag(Splay *x)
{
	Splay *y = x->fa;
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if (y == y->fa->ls)
		y->fa->ls = x;
	else if (y == y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
}

void splay(Splay *x)
{
	x->push_down();
	Splay *y, *z;
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
}

void access(Splay *x)
{
	Splay *y = null;
	while (x != null)
	{
		splay(x);
		x->rs = y;
		y = x;
		x = x->fa;
	}
}

void move_to_root(Splay *x)
{
	access(x);
	splay(x);
	x->reverse();
}

void link(Splay *x, Splay *y)
{
	move_to_root(x);
	x->fa = y;
}

void cut(Splay *x, Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	x->fa = null;
	y->ls = null;
}

bool query(Splay *x, Splay *y)
{
	access(x);
	splay(x);
	while (y->fa != null)
		y = y->fa;
	return x == y;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		ptr[i] = new Splay(i);
	while (m--)
	{
		static char s[10];
		static int x,y;
		scanf("%s%d%d", s, &x, &y);
		if (!strcmp(s, "Query"))
			puts(query(ptr[x], ptr[y]) ? "Yes" : "No");
		else if (!strcmp(s, "Connect"))
			link(ptr[x], ptr[y]);
		else if (!strcmp(s, "Destroy"))
			cut(ptr[x], ptr[y]);
	}
}
