#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=10010;
int n,m;
struct Splay
{
	Splay *ls,*rs,*fa;
	bool rev;
	Splay();
	void reverse()
	{
		if(this==fa->ls||this==fa->rs)
			fa->reverse();
		if(rev)
		{
			swap(ls,rs);
			ls->rev^=1;
			rs->rev^=1;
			rev=0;
		}
	}
	void* operator new(size_t);
}*null=new Splay,*ptr[maxn],Tdata[maxn];
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata;
	return p++;
}
Splay :: Splay()
{
	ls=rs=fa=null;
	rev=false;
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
}
void splay(Splay *x)
{
	Splay *y,*z;
	x->reverse();
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
}
void access(Splay *x)
{
	Splay *y=null;
	while(x!=null)
	{
		splay(x);
		x->rs=y;
		y=x;
		x=x->fa;
	}
}
void link(Splay *x,Splay *y)
{
	access(x);
	splay(x);
	x->rev^=1;
	x->reverse();
	x->ls=null;
	x->fa=y;
}
void cut(Splay *x,Splay *y)
{
	access(x);
	splay(x);
	x->rev^=1;
	x->reverse();
	x->rs=null;
	access(y);
	x->rs=null;
	splay(y);
	y->fa=null;
}
void query(Splay *x,Splay *y)
{
	access(x);
	splay(x);
	while(y->fa!=null)
		y=y->fa;
	if(y==x)
		puts("Yes");
	else
		puts("No");
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		ptr[i]=new Splay;
	for(int i=1;i<=m;i++)
	{
		static char s[10];
		static int x,y;
		scanf("%s%d%d",s,&x,&y);
		if(!strcmp(s,"Query"))
			query(ptr[x],ptr[y]);
		else if(!strcmp(s,"Connect"))
			link(ptr[x],ptr[y]);
		else if(!strcmp(s,"Destroy"))
			cut(ptr[x],ptr[y]);
	}
}
