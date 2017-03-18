#include <stdio.h>
#include <algorithm>
using namespace std;
const int inf=~0u>>2;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val,cnt;
	Splay(int x);
	void update();
}*null=new Splay(-inf),*root=null;
void Splay :: update()
{
	size=cnt+ls->size+rs->size;
}
Splay :: Splay(int x)
{
	fa=ls=rs=null;
	val=x;
	size=cnt=x==-inf?1:0;
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
	if(y==root);
		root=x;
}
void splay(Splay *x,Splay *t)
{
	Splay *y,*z;
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
	}
	else if(y==x->val)
	{
		++x->cnt;
		splay(x,null);
		return;
	}
	else if(y>x->val)
		insert(x->rs,y,x);
	else
		insert(x->ls,y,x);
}
int q_rank(Splay *x,int y,Splay *z)
{
	while(x->val!=y)
		if(x->val>y)
			x=x->ls;
		else if(x->val<y)
			x=x->rs;
	splay(x,z);
	return root->ls->size+1;
}
int q_num(Splay *x,int y,Splay *z)
{
	while(true)
	{
		if(y<=x->ls->size)
			x=x->ls;
		else
		{
			y-=x->ls->size;
			if(y<=x->cnt)
				break;
			y-=x->cnt;
			x=x->rs;
		}
	}
	splay(x,z);
	return root->val;
}
int pre(Splay *x,int y,Splay *z)
{
	Splay *ans;
	while(x!=null)
		if(x->val<y)
			ans=x,x=x->rs;
		else
			x=x->ls;
	splay(ans,z);
	return root->val;
}
int suc(Splay *x,int y,Splay *z)
{
	Splay *ans;
	while(x!=null)
		if(x->val>y)
			ans=x,x=x->ls;
		else
			x=x->rs;
	splay(ans,z);
	return root->val;
}
void print(Splay *x)
{
	if(x==null)
		return;
	printf("%d -> %d ls:%d rs:%d\n",x->fa->val,x->val,x->ls->val,x->rs->val);
	print(x->ls);
	print(x->rs);
}
void del(Splay *x,int y)
{
    while(x->val!=y)
    	if(x->val>y)
    		x=x->ls;
    	else
    		x=x->rs;
	if(x->cnt>1)
	{
		--x->cnt;
		splay(x,null);
	}
	else
	{
		splay(x,null);
		if(x->ls==null&&x->rs==null)
			root=null;
		else if(x->ls==null)
		{
			root=x->rs;
			x->rs->fa=null;
			root->update();
		}
		else if(x->rs==null) 
		{
			root=x->ls;
			x->ls->fa=x->fa;
			root->update();
		}
		else 
		{
			Splay *p=x->ls;
			while(p->rs!=null)
				p=p->rs;
			splay(p,x);
			root=x->ls;
			x->ls->fa=null;
			x->rs->fa=x->ls;
			x->ls->rs=x->rs;
			root->update();
		}
	}
}
int main()
{
	freopen("input2.in","r",stdin);
//	freopen("splay.in","r",stdin);
//	freopen("splay.out","w",stdout);
	int n;
	scanf("%d",&n);
	while(n--)
	{
		static int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
			insert(root,x,root);
		else if(opt==2)
			del(root,x);
		else if(opt==3)
			printf("%d\n",q_rank(root,x,null));
		else if(opt==4)
			printf("%d\n",q_num(root,x,null));
		else if(opt==5)
			printf("%d\n",pre(root,x,null));
		else if(opt==6)
			printf("%d\n",suc(root,x,null));
	}
}
