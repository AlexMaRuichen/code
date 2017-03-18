#include <stdio.h>
#include <algorithm>
using namespace std;
int delta,m;
struct Splay 
{
	Splay *ls,*rs,*fa;
	int val,size;
	Splay(int x);
	void update();
}*null=new Splay(0),*root=null;
Splay :: Splay(int x)
{
	val=x;
	size=x?1:0;
	fa=rs=ls=null;
}
void Splay :: update()
{
	size=1+ls->size+rs->size;
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
void insert(Splay* &x,int y,Splay *z)
{
	if(x==null)
	{
		x=new Splay(y);
		x->fa=z;
		splay(x,null);
		return;
	}
	if(x->val>y)
		insert(x->ls,y,x);
	else
		insert(x->rs,y,x);
}
int ans;
void del(Splay* &x)
{
	while(true)
	{
		if(x==null)
			return;
		if(x->ls)	
			del(x->ls);
		if(x->val+delta<m)
			++ans,x->rs->fa=x->fa,x=x->rs;
		else
			break;
	}
	if(x!=null)
		x->update();
}
void find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		if(y<=x->rs->size)
			x=x->rs;
		else
		{
			y-=x->rs->size;
			if(y==1)
				break;
			--y;
			x=x->ls;
		}
	}
	splay(x,z);
}
int main()
{	
	int n;
	scanf("%d%d",&n,&m);
	while(n--)
	{
		static char s[5];
		static int x;
		scanf("%s%d",s,&x);
		if(s[0]=='I') 
			if(x>=m)
				insert(root,x-delta,null);
		if(s[0]=='A')
			delta+=x;
		if(s[0]=='S')
			delta-=x,del(root);
		if(s[0]=='F')
		{
			if(x>root->size)
				puts("-1");
			else 
				find(root,x,null),printf("%d\n",root->val+delta);
		}
	}
	printf("%d\n",ans);
}
