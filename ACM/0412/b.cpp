#include <stdio.h>
#include <algorithm>

template <typename T> inline T& relax(T &a, const T &b)
{
	return (a < b ? a = b : 1), a;
}

using namespace std;

const int maxn=100010;
const int inf = 1e8;

int n,m;

struct Splay
{
    Splay *ls, *rs, *fa;
    int size, val;
    bool rev;
    int change;
    int lmx, rmx, sum, mx;
    Splay();
    Splay(int x);
    void update();
    void push_down();
    void reverse();
    void same(int x);
    void *operator new(size_t);
    void del();
}*null=new Splay(0),*ptr[maxn],mempool[maxn];

Splay::Splay() 
{
    fa = ls = rs = this;
    size = 0;
    val = lmx = rmx = mx = -inf;
    sum = 0;
	rev = false;
	change = inf;
}

Splay :: Splay(int x)
{
    fa = ls = rs = null;
    val = lmx = rmx = mx = sum = x;
    size = 1;
    rev = false;
    change = inf;
}
void Splay::reverse() 
{
    swap(ls, rs);
    swap(lmx, rmx);
    rev ^= 1;
}

void Splay::same(int x) 
{
    sum = size * x;
    val = change = x;
    if (x > 0)
        lmx = rmx = mx = size * x;
    else
        lmx = rmx = mx = x;
}

void Splay :: update()
{
    size = ls->size + rs->size + 1;
    mx = lmx = rmx = sum = val;
	relax(relax(mx, ls->mx), ls->rmx + lmx);
    lmx = max(ls->lmx, ls->sum + lmx);
	relax(rmx, sum + ls->rmx);
    sum += ls->sum;
	relax(relax(mx, rs->mx), rmx + rs->lmx);
	relax(lmx, sum + rs->lmx);
    rmx = max(rs->rmx, rs->sum + rmx);
    sum += rs->sum;
}

void Splay :: push_down()
{
	if(this==fa->ls||this==fa->rs)
		fa->push_down();
	 if (change ^ inf) 
	{
        ls->same(change);
        rs->same(change);
        change = inf;
    }
	if(rev)
	{
		ls->reverse();
		rs->reverse();
		rev=0;
	}
}
void* Splay :: operator new(size_t)
{
	static Splay *p=mempool;
	return p++;
}

void zig(Splay *x)
{
	Splay *y=x->fa;
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->update();
}
void zag(Splay *x)
{
	Splay *y=x->fa;
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else if(y==y->fa->rs)
		y->fa->rs=x;
	y->fa=x;
	y->update();
}
void splay(Splay *x)
{
	Splay *y,*z;
	x->push_down();
	while(x==x->fa->ls||x==x->fa->rs)
	{
		y=x->fa;
		z=y->fa;
		if(x==y->ls)
		{
			if(y==z->ls)
				zig(y);
			zig(x);
		}
		else
		{
			if(y==z->rs)
				zag(y);
			zag(x);
		}
	}
	x->update();
}
void access(Splay *x)
{
	Splay *y=null;
	while(x!=null)
	{
		splay(x);
		x->rs=y;
		x->update();
		y=x;
		x=x->fa;
	}
}
Splay* root(Splay *x)
{
	while(x->fa!=null)
		x=x->fa;
	return x;
}
void move_to_root(Splay *x)
{
	access(x);
	splay(x);
	x->reverse();
}
void link(Splay *x,Splay *y)
{
	move_to_root(x);
	x->fa=y;
}

void query(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	printf("%d\n", max(y->mx, 0));
}

void modify(Splay *x, Splay *y, int z)
{
	move_to_root(x);
	access(y);
	splay(y);
	y->same(z);
}

int main()
{
	scanf("%d",&n);
	for(int i = 1, x; i <= n; i++)
	{
		scanf("%d",&x);
		ptr[i]=new Splay(x);
	}
	for(int i = 1, x, y; i < n; i++)
		scanf("%d%d", &x, &y),
		link(ptr[x], ptr[y]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		static int opt, a, b, c;
		scanf("%d%d%d", &opt, &a, &b);
		if (opt == 1)
			query(ptr[a], ptr[b]);
		else
		{
			scanf("%d", &c);
			modify(ptr[a], ptr[b], c);
		}
	}
}
