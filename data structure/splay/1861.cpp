#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=80010;
int a[maxn];
int n,m;
struct Splay
{
	Splay *ls,*rs,*fa;
	int size,val;
	Splay(){}
	Splay(int x);
	void update()
	{
		size=ls->size+rs->size+1;
	}
	void* operator new(size_t);
}*root,*null=new Splay(0),*ptr[maxn],Tdata[maxn];
void* Splay :: operator new(size_t)
{
	static Splay *p=Tdata;
	return p++;
}
Splay :: Splay(int x)
{
	size=null?1:0;
	val=x;
	ls=rs=fa=null;
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
	if(y->fa->ls==y)
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
	Splay *y,*z;
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
		else if(x==y->rs)
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
Splay* build(int l,int r)
{
	if(l>r)
		return null;
	int mid=l+r>>1;
	Splay *x=ptr[a[mid]];
	x->ls=build(l,mid-1);
	x->rs=build(mid+1,r);
	x->ls->fa=x->rs->fa=x;
	x->update();
	return x;
}
void build()
{
	root=new Splay(~0u>>1);
	root->rs=new Splay(~0u>>1);
	root->rs->ls=build(1,n);
	root->rs->ls->fa=root->rs;
	root->rs->update();
	root->rs->fa=root;
	root->update();
}
void insert(Splay *x,int y)
{
	find(root,y,null);
	find(root,y+1,root);
	root->rs->ls=x;
	root->rs->ls->fa=root->rs;
	root->rs->update();
	root->update();
}
void del(int x)
{
	find(root,x,null);
	find(root,x+2,root);
	root->rs->ls=null;
	root->rs->update();
	root->update();
}
int qrank(Splay *x)
{
	int ans=x->ls->size;
	while(x!=root)
	{
		if(x==x->fa->rs)
			ans+=x->fa->ls->size+1;
		x=x->fa;
	}
	return ans;
}
void insert()
{
	static int x,y,rank;
	scanf("%d%d",&x,&y);
	rank=qrank(ptr[x]);
	del(rank);
	insert(ptr[x],rank+y);
}
void top()
{
	static int x,y,rank;
	scanf("%d%d",&x,&y);
	rank=qrank(ptr[x]);
	del(rank);
	insert(ptr[x],1);
}
void bottom()
{
	static int x,y,rank;
	scanf("%d%d",&x,&y);
	rank=qrank(ptr[x]);
	del(rank);
	insert(ptr[x],n);
}
void ask()
{
	static int x;
	scanf("%d",&x);
	printf("%d\n",qrank(ptr[x])-1);
}
void query()
{
	static int x;
	scanf("%d",&x);
	find(root,x+1,null);
	printf("%d\n",root->val);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),ptr[i]=new Splay(i);
	build();
	for(int i=1;i<=m;i++)
	{
		static char opt[10];
		scanf("%s",opt);
		if(!strcmp(opt,"Top"))
			top();
		else if(!strcmp(opt,"Bottom"))
			bottom();
		else if(!strcmp(opt,"Insert"))
			insert();
		else if(!strcmp(opt,"Ask"))
			ask();
		else if(!strcmp(opt,"Query"))
			query();
	}
}
