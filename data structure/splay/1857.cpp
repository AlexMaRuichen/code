#include <stdio.h>
#include <algorithm>
using namespace std;
struct Splay
{
	Splay *ls,*rs,*fa;
	int val;
	Splay (int x);
}*null=new Splay(0),*root=null;
Splay :: Splay (int x)
{
	val=x;
	ls=rs=fa=null;
}
inline void zig(Splay *x)
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
	if(root==y)
		root=x;
}
inline void zag(Splay *x)
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
	if(root==y)
		root=x;
}
inline void splay(Splay *x,Splay *t)
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
}
inline void insert(Splay* &x,int y,Splay *z)
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
inline void process()
{
	Splay *x;
	if(root->ls!=null)
	{
		x=root->ls;
		while(x->rs!=null)
			x=x->rs;
		splay(x,root);
	}
	if(root->rs!=null)
	{
		x=root->rs;
		while(x->ls!=null)
			x=x->ls;
		splay(x,root);
	}
}
int n,ans;
int main()
{
	scanf("%d",&n);
	scanf("%d",&ans);
	insert(root,ans,null);
	--n;
	while(n--)	
	{
		static int x,t;
		t=~0u>>1;
		scanf("%d",&x);
		insert(root,x,null);
		process();
		if(root->ls!=null)
			t=min(t,abs(x-root->ls->val));
		if(root->rs!=null)
			t=min(t,abs(x-root->rs->val));
		ans+=t;
	}	
	printf("%d\n",ans);
}
