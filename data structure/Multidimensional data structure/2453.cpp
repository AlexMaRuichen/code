#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
struct Treap
{
	Treap *ls,*rs;
	int size,val,cnt,key;
	Treap();
	Treap(int x);
	void update()
	{
		size=ls->size+rs->size+cnt;
	}
}*null=new Treap(),*pos[maxn];
Treap :: Treap()
{
	ls=rs=this;
	size=val=key=cnt=0;
}
Treap :: Treap(int x)
{
	ls=rs=null;
	cnt=size=1;
	val=x;
	key=rand();
}
void zig(Treap *&x)
{
	Treap *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	x=y;
	x->rs->update();
	x->update();
}
void zag(Treap *&x)
{
	Treap *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	x=y;
	x->ls->update();
	x->update();
}
void insert(Treap *&x,int y)
{
	if(x==null)
	{
		x=new Treap(y);
		return;
	}
	if(y==x->val)
		++x->cnt;
	else if(y<x->val)
	{
		insert(x->ls,y);
		if(x->ls->key>x->key)
			zig(x);
	}
	else
	{
		insert(x->rs,y);
		if(x->rs->key>x->key)
			zag(x);
	}
	x->update();
}
void del(Treap *&x,int y)
{
	if(y<x->val)
		del(x->ls,y);
	else if(y>x->val)
		del(x->rs,y);
	else if(x->cnt^1)
		--x->cnt;
	else if(x->ls==null)
		x=x->rs;
	else if(x->rs==null)
		x=x->ls;
	else
	{
		zig(x);
		del(x->rs,y);
		if(x->rs!=null&&x->rs->key>x->key)
			zag(x);
	}
	x->update();
}
int rank(Treap *x,int y)
{
	if(x==null)
		return 0;
	if(y<x->val)
		return rank(x->ls,y);
	else if(y==x->val)
		return x->ls->size;
	else 
		return x->ls->size+x->cnt+rank(x->rs,y);
}
int get_pre(Treap *x,int y)
{
	if(x==null)
		return 0;
	if(y<=x->val)
		return get_pre(x->ls,y);
	else 
		return max(get_pre(x->rs,y),x->val);
}
int get_suc(Treap *x,int y)
{
	if(x==null)
		return ~0u>>2;
	if(y>=x->val)
		return get_suc(x->rs,y);
	else
		return min(get_suc(x->ls,y),x->val);
}
struct seg_tree
{
	seg_tree *ls,*rs;
	Treap *t;
	seg_tree(){ls=rs=NULL,t=null;}
}*root;
int pre[maxn];
int color[maxn];
int last[maxn];
void build(seg_tree *&x,int l,int r)
{
	x=new seg_tree();
	for(int i=l;i<=r;i++)
		insert(x->t,pre[i]);
	if(l==r)
		return;
	int mid=l+r>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
void modify(seg_tree *x,int p,int o,int v,int l,int r)
{
	del(x->t,o);
	insert(x->t,v);
	if(l==r)
		return;
	int mid=l+r>>1;
	if(mid>=p)
		modify(x->ls,p,o,v,l,mid);
	else
		modify(x->rs,p,o,v,mid+1,r);
}
int query(seg_tree *x,int p,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return rank(x->t,p);
	int mid=L+R>>1;
	if(mid>=r)
		return query(x->ls,p,l,r,L,mid);
	else if(mid<l)
		return query(x->rs,p,l,r,mid+1,R);
	else 
		return query(x->ls,p,l,mid,L,mid)+query(x->rs,p,mid+1,r,mid+1,R);
}
int n,m;
int main()
{
	srand(20000612);
	rand();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=1000000;i++)
		pos[i]=null;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&color[i]);
		pre[i]=last[color[i]];
		last[color[i]]=i;
		insert(pos[color[i]],i);
	}
	build(root,1,n);
	for(int i=1;i<=m;i++)
	{
		static char opt[10];
		static int x,y;
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0]=='Q')
			printf("%d\n",query(root,x,x,y,1,n));
		else 
		{
			int nextA=get_suc(pos[color[x]],x);
			int lastB=get_pre(pos[y],x);
			int nextB=get_suc(pos[y],x);
			if(nextA^(~0u>>2))
				modify(root,nextA,x,pre[x],1,n);
			modify(root,x,pre[x],lastB,1,n);
			if(nextB^(~0u>>2))
				modify(root,nextB,lastB,x,1,n);
			del(pos[color[x]],x);
			insert(pos[y],x);
			color[x]=y;
			if(nextA^(~0u>>2))
				pre[nextA]=pre[x];
			pre[x]=lastB;
			if(nextB^(~0u>>2))
				pre[nextB]=x;
		}
	}
}
