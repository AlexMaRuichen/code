#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=300010;
int n,m;
struct Splay
{
	Splay *ls,*rs,*fa;
	int val,sum;
	bool rev;
	Splay(int x);
	Splay(){};
	void reverse();
	void update();
	void push_down();
	void* operator new(size_t);
}*null=new Splay(0),*ptr[maxn],mempool[maxn];
Splay :: Splay(int x)
{
	ls=rs=fa=null;
	sum=val=x;
	rev=false;
}
void Splay :: reverse()
{
	rev^=1;
	swap(ls,rs);
}
void Splay :: update()
{
	sum=ls->sum^rs->sum^val;
}
void Splay :: push_down()
{
	if(this==fa->ls||this==fa->rs)
		fa->push_down();
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
	if(root(x)==root(y))
		return;
	move_to_root(x);
	x->fa=y;
}
void cut(Splay *x,Splay *y)
{
	if(root(x)!=root(y)||x==y)
		return;
	move_to_root(x);
	access(y);
	splay(y);
	if(y->ls==x)
	{
		x->fa=null;
		y->ls=null;
		y->update();
	}
}
void query(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	printf("%d\n",y->sum);
}
void modify(Splay *x,int y)
{
	splay(x);
	x->val=y;
	x->update();
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		ptr[i]=new Splay(x);
	}
	for(int i=1;i<=m;i++)
	{
		static int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==0)
			query(ptr[x],ptr[y]);
		else if(opt==1)
			link(ptr[x],ptr[y]);
		else if(opt==2)
			cut(ptr[x],ptr[y]);
		else if(opt==3)
			modify(ptr[x],y);
	}
}
