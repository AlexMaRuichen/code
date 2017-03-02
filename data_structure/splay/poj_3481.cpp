#include <stdio.h>
#include <algorithm>
using namespace std;
const int inf=~0u>>2;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val,name;
 	Splay(int x,int y);
	void update()
	{
		size=ls->size+rs->size+1;
	}
}*null=new Splay(0,0),*root=null;
Splay :: Splay(int x,int y)
{
	size=x==-inf?0:1;
	fa=ls=rs=null;
	val=x;
	name=y;
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
	if(y==root)
		root=x;
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
	if(y==root)
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
		if(z==t)
		{
			if(x==y->ls)
				zig(x);
			else 
				zag(x);
			break;
		}
		if(x==y->ls)
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
void insert(Splay* &x,int y,int g,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y,g);
		x->fa=z;
		splay(x,null);
	}
	else if(x->val>y)
		insert(x->ls,y,g,x);
	else
		insert(x->rs,y,g,x);
}
void qmin(Splay *x)
{
	if(x==null)
		return;
	while(x->ls!=null)
		x=x->ls;
	splay(x,null);
}
void qmax(Splay *x)
{
	if(x==null)
		return;
	while(x->rs!=null)
		x=x->rs;
	splay(x,null);
}
void del()
{
	if(root==null)
		return;
	else if(root->ls==null&&root->rs==null)
		root=null;
	else if(root->ls==null)
		root=root->rs,root->fa=null;
	else if(root->rs==null)
		root=root->ls,root->fa=null;
	else
	{
		Splay *x=root->ls;
		while(x->rs)
			x=x->rs;
		splay(x,root);
		root->ls->rs=root->rs;
		root->rs->fa=root->ls;
		root=root->ls;
		root->fa=null;
		root->update();
	}
}
int main()
{
	int opt;
	while(scanf("%d",&opt)==1&&opt)
	{
		static int x,y;
		if(opt==1)
			scanf("%d%d",&x,&y),insert(root,y,x,null);
		else if(opt==2)
			qmax(root),printf("%d\n",root->name),del();
		else
			qmin(root),printf("%d\n",root->name),del();
	}
}
