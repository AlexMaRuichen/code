#include <stdio.h>
#include <algorithm>
using namespace std;

struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val;
	Splay(int x);
	void push_up()
	{
		size=ls->size+rs->size+1;
	}
}*null=new Splay(0),*root=null;
Splay:: Splay(int x)
{
	size=x?1:0;
	val=x;
	fa=ls=rs=null;
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
	y->push_up();
	if(root==y)
		root=x;
}
void splay(Splay *x,Splay *tar)
{
	static Splay *y,*z;
	while(true)
	{
		y=x->fa,z=y->fa;
		if(y==tar)
			break;
		if(z==tar)
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
	x->push_up();
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
	if(y>=x->val)
		insert(x->rs,y,x);
	else
		insert(x->ls,y,x);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		insert(root,x,root);
	}
	for(int i=1;i<=n;i++)
	{
		find(root,i,null);
		printf("%d\n",root->val);
	}
}
