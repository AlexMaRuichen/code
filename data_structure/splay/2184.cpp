#include <stdio.h>
#include <algorithm>
using namespace std;
const int inf=~0u>>2;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val;
	bool rev;
	Splay (int x);
	void update();
	void reverse();
}*null=new Splay(-inf),*root=null;
Splay :: Splay (int x)
{
	fa=ls=rs=null;
	val=x;
	rev=0;
	size=x==-inf?0:1;
}
void Splay :: update()
{
	size=ls->size+rs->size+1;
}
void Splay :: reverse()
{
	if(this==null)
		return;
	if(rev)
	{
		ls->rev^=1;
		rs->rev^=1;
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		rev=0;
	}
}
void zig(Splay *x)
{
	Splay *y=x->fa;
	y->reverse();
	x->reverse();
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
	y->reverse();
	x->reverse();
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
	x->update();
	insert(x->rs,y,x);
}

void find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		x->reverse();
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
bool flag;
void print(Splay *x)
{
	if(x==null)
		return;
	x->reverse();
	print(x->ls);
	if(!flag&&x->val!=-1)
		printf("%d",x->val),flag=true;
	else if(x->val!=-1)
		printf(" %d",x->val);
	print(x->rs);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	insert(root,-1,null);	
	for(int i=1;i<=n;i++)
		insert(root,i,null);
	insert(root,-1,null);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		find(root,x,null);
		find(root,y+2,root);
		root->rs->ls->rev^=1;
		swap(root->rs->ls->ls,root->rs->ls->rs);
	}
	print(root);
	puts("");
}
