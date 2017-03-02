#include <stdio.h>
#include <string.h>
#include <algorithm>
#define mod (y-x+1)
using namespace std;
const int inf=~0u>>1;
struct Splay
{
	Splay *ls,*rs,*fa;
	int val,size,mn;
	int add;
	bool rev;
	Splay(int x);
	void update()
	{
		size=ls->size+rs->size+1;
		mn=min(min(ls->mn,rs->mn),val);
	}
	void push_down();
}*null=new Splay(inf),*root=null;
Splay :: Splay(int x)
{
	val=mn=x;
	size=x==inf?0:1;
	ls=rs=fa=null;
	rev=false;
	add=0;
}
void Splay :: push_down()
{
	if(add)
	{
		if(ls!=null)
		{
			ls->add+=add;
			ls->val+=add;
			ls->mn+=add;
		}
		if(rs!=null)
		{
			rs->add+=add;
			rs->val+=add;
			rs->mn+=add;
		}
		add=0;
	}
	if(rev)
	{
		ls->rev^=1;
		rs->rev^=1;
		swap(rs->ls,rs->rs);
		swap(ls->ls,ls->rs);
		rev=false;
	}
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
void find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		x->push_down();
		if(y<=x->ls->size)
			x=x->ls;
		else
		{
			y-=x->ls->size;
			if(y==1)
				break;
			--y;
			x=x->rs;
		}
	}
	splay(x,z);
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
int n,m;
void print(Splay *x)
{
	if(x==null)
		return;
	x->push_down();
	print(x->ls);
	printf("%d ",x->val);
	print(x->rs);
}
int main()
{
	scanf("%d",&n);
	insert(root,~0u>>2,null);
	while(n--)
	{
		static int x;
		scanf("%d",&x);
		insert(root,x,null);
	}
	insert(root,~0u>>2,null);
	scanf("%d",&m);
	while(m--)
	{
		static char s[20];
		static int x,y,z;
		scanf("%s",s);
		if(!strcmp(s,"ADD"))
		{
			scanf("%d%d%d",&x,&y,&z);
			find(root,x,null);
			find(root,y+2,root);
			root->rs->ls->add+=z;
			root->rs->ls->val+=z;
			root->rs->ls->mn+=z;
		}
		else if(!strcmp(s,"REVERSE"))
		{
			scanf("%d%d",&x,&y);
			find(root,x,null);
			find(root,y+2,root);
			swap(root->rs->ls->ls,root->rs->ls->rs);
			root->rs->ls->rev^=1;
		}
		else if(!strcmp(s,"REVOLVE"))
		{
			scanf("%d%d%d",&x,&y,&z);
			z=((z%mod)+mod)%mod;
			if(!z)
				continue;
			find(root,y-z+1,null);
			find(root,y+2,root);
			Splay *tmp=root->rs->ls;
			root->rs->ls=null;
			root->rs->update();
			root->update();
			find(root,x,null);
			find(root,x+1,root);
			root->rs->ls=tmp;
			tmp->fa=root->rs;
			root->rs->update();
			root->update();
		}
		else if(!strcmp(s,"INSERT"))
		{
			scanf("%d%d",&x,&y);
			find(root,x+1,null);
			find(root,x+2,root);
			insert(root->rs->ls,y,root->rs);
		}
		else if(!strcmp(s,"DELETE"))
		{
			scanf("%d",&x);
			find(root,x,null);
			find(root,x+2,root);
			root->rs->ls=null;
			root->rs->update();
			root->update();
		}
		else if(!strcmp(s,"MIN"))
		{
			scanf("%d%d",&x,&y);
			find(root,x,null);
			find(root,y+2,root);
			printf("%d\n",root->rs->ls->mn);
		}
	}
}
