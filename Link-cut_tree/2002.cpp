#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=200010;
int n,m;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size;
	void update()
	{
		size=ls->size+rs->size+1;
	}
	Splay();
	void* operator new(size_t);
}*null=new Splay,*ptr[maxn],Tdata[maxn],*root;
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata;
	return p++;
}
Splay :: Splay()
{
	ls=rs=fa=null;
	size=1;
}
void zig(Splay *x)
{
	Splay *y=x->fa;
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y->fa->ls==y)
		y->fa->ls=x;
	else if(y->fa->rs==y)
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
	if(y->fa->ls==y)
		y->fa->ls=x;
	else if(y->fa->rs==y)
		y->fa->rs=x;
	y->fa=x;
	y->update();
}
void splay(Splay *x)
{
	Splay *y,*z;
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
			if(y==x->rs)
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
void link(Splay *x,Splay *y)
{
	access(x);
	splay(x);
	x->ls->fa=null;
	x->ls=null;
	x->fa=y;
	x->update();
}
void query()
{
	static int x;
	scanf("%d",&x);
	++x;
	access(ptr[x]);
	splay(ptr[x]);
	printf("%d\n",ptr[x]->size);
}
void modify()
{
	static int x,y;
	scanf("%d%d",&x,&y);
	++x;
	if(x+y<=n)
		root=ptr[x+y];
	else
		root=null;
	link(ptr[x],root);
}
int main()
{
	null->size=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		ptr[i]=new Splay;
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		if(i+x<=n)
			ptr[i]->fa=ptr[i+x];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		static int opt;
		scanf("%d",&opt);
		if(opt==1)
			query();
		else
			modify();
	}
}
