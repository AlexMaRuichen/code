#include <stdio.h>
#include <algorithm>
using namespace std;
const int inf=~0u>>2;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val,add,mx;
	bool rev;
	Splay(int x);
	void update()
	{
		size=ls->size+rs->size+1;
		mx=max(max(ls->mx,rs->mx),val);
	}
	void push_down();
}*null=new Splay(-inf),*root=null;
void Splay :: push_down()
{
	if(add)
	{
		if(ls!=null)
		{
			ls->val+=add;
			ls->add+=add;
			ls->mx+=add;
		}
		if(rs!=null)
		{
			rs->val+=add;
			rs->add+=add;
			rs->mx+=add;
		}
		add=0;
	}
	if(rev)
	{
		ls->rev^=1;
		rs->rev^=1;
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		rev=false;
	}
}
Splay :: Splay(int x)
{
	ls=rs=fa=null;
	size=null?1:0;
	add=0;
	val=mx=x;
	rev=false;
}
void zig(Splay *x)
{
	Splay *y=x->fa;
	y->push_down();
	x->push_down();
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void zag(Splay *x)
{
	Splay *y=x->fa;
	y->push_down();
	x->push_down();
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls=x;
	else
		y->fa->rs=x;
	y->fa=x;
	y->update();
	if(root==y)
		root=x;
}
void splay(Splay *x,Splay *t)
{
	static Splay *y,*z;
	while(true)
	{
		y=x->fa;
		z=y->fa;
		if(y==t)
			break;
		else if(z==t)
		{
			if(x==y->ls)
				zig(x);
			else
				zag(x);
			break;
		}
		else if(x==y->ls)
		{
			if(y==z->ls)
				zig(y),zig(x);
			else
				zig(x),zag(x);
		}
		else
		{
			if(y==z->rs)
				zag(y),zag(x);
			else
				zag(x),zig(x);
		}
	}
	x->update();
}
void insert(Splay* &x,int y,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y);
		x->fa=z;
		splay(x,null);
		return;
	}
	x->push_down();
	insert(x->rs,y,x);
}
void find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		int t=x->ls->size;
		x->push_down();
		if(y<=t)
			x=x->ls;
		else
		{
			y-=t;
			if(y==1)
				break;
			--y;
			x=x->rs;
		}
	}
	splay(x,z);
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	insert(root,inf,null);
	for(int i=1;i<=n;i++)
		insert(root,0,null);
	insert(root,inf,null);
	while(m--)
	{
		static int opt,l,r,v;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&l,&r,&v);
			find(root,l,null);
			find(root,r+2,root);
			root->rs->ls->add+=v;
			root->rs->ls->mx+=v;
			root->rs->ls->val+=v;
		}
		else if(opt==2)
		{
			scanf("%d%d",&l,&r);
			find(root,l,null);
			find(root,r+2,root);
			swap(root->rs->ls->ls,root->rs->ls->rs);
			root->rs->ls->rev^=1;
		}
		else if(opt==3)
		{
			scanf("%d%d",&l,&r);
			find(root,l,null);
			find(root,r+2,root);
			printf("%d\n",root->rs->ls->mx);
		}
	}
}
