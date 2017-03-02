#include <stdio.h>
#include <algorithm>
using namespace std;
struct seg_tree
{
	seg_tree *ls,*rs;
	int lmx,rmx,mx,len;
	int lazy,state;
	seg_tree()
	{
		ls=rs=NULL;
		lmx=rmx=mx=len=0;
		lazy=0;
		state=1;
	}
	void update()
	{
		mx=max(max(ls->mx,rs->mx),ls->rmx+rs->lmx);
		if(ls->lmx==ls->len)
			lmx=ls->len+rs->lmx;
		else
			lmx=ls->lmx;     
		if(rs->rmx==rs->len)
			rmx=rs->len+ls->rmx;
		else
			rmx=rs->rmx;     
		
	}
	void push_down()
	{
		if(lazy)
		{
			ls->state=lazy;
			rs->state=lazy;
			ls->lazy=lazy;
			rs->lazy=lazy;
			if(ls->state<0)
			{
				ls->mx=ls->lmx=ls->rmx=0;
				rs->mx=rs->lmx=rs->rmx=0;
			}
			else
			{
				ls->mx=ls->lmx=ls->rmx=ls->len;
				rs->mx=rs->lmx=rs->rmx=rs->len;
			}
			lazy=0;
		}
	}
}*root;
void build(seg_tree* &x,int l,int r)
{
	x->len=r-l+1;
	if(l==r)
	{
		x->mx=x->lmx=x->rmx=1;
		return;
	}
	int mid=(l+r)>>1;
	x->ls=new seg_tree();
	x->rs=new seg_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
	x->update();
}
int query(seg_tree* &x,int len,int l,int r)
{
	if(len==r-l+1)
		return l;
	int mid=(l+r)>>1;
	x->push_down();
	if(x->ls->mx>=len)
		return query(x->ls,len,l,mid);
	else if(x->ls->rmx+x->rs->lmx>=len)
		return	mid-x->ls->rmx+1;
	else 
		return query(x->rs,len,mid+1,r);
}
void modify(seg_tree* &x,int tag,int l,int r,int L,int R)
{
	if(l==L&&r==R)
	{
		x->lazy=tag;
		if(tag>0)
			x->mx=x->lmx=x->rmx=x->len;
		else
			x->mx=x->lmx=x->rmx=0;
		return;
	}
	x->push_down();
	int mid=(L+R)>>1;
	if(mid>=r)
		modify(x->ls,tag,l,r,L,mid);
	else if(mid<l)
		modify(x->rs,tag,l,r,mid+1,R);
	else
		modify(x->ls,tag,l,mid,L,mid),modify(x->rs,tag,mid+1,r,mid+1,R);
	x->update();
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	root=new seg_tree();
	build(root,1,n);
	while(m--)
	{
		static int opt,x,y;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&x);
			if(root->mx<x)
				puts("0");
			else
			{
				y=query(root,x,1,n);
				printf("%d\n",y);
				modify(root,-1,y,y+x-1,1,n);
			}
		}
		else
		{
			scanf("%d%d",&x,&y);
			modify(root,1,x,x+y-1,1,n);
		}
	}
}
