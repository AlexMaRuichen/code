#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Treap
{
	Treap *ls,*rs;
	int val,cnt,key,size;
	Treap (int x);
}*root,*ans;
Treap::Treap (int x)
{
	ls=rs=NULL;
	val=x;
	cnt=size=1;
	key=rand();
}
void push_up(Treap *&x)
{
	x->size=x->cnt;
	if(x->ls)
		x->size+=x->ls->size;
	if(x->rs)
		x->size+=x->rs->size;	
}
void zig(Treap *&x)
{
	Treap *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	if(x) push_up(x);
	x=y;
	if(x) push_up(x);
}
void zag(Treap *&x)
{
	Treap *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	if(x) 
		push_up(x);
	x=y;
	if(x)
		push_up(x);
}
void insert(Treap *&x,int y)
{
	if(x==NULL)
	{
		x=new Treap(y);
		return;
	}
	else if(y==x->val)
	{
		x->cnt++;
	}
	else if(y>x->val)
	{
		insert(x->rs,y);
		if(x->rs->key>x->key)
			zig(x);
	}
	else if(y<x->val)
	{
		insert(x->ls,y);
		if(x->ls->key>x->key)
			zag(x);
	}
	if(x)
		push_up(x);
}
void del(Treap *&x,int y)
{
	if(x==NULL)
		return;
	if(x->val<y)
		del(x->rs,y);
	else if(x->val>y)
		del(x->ls,y);
	else
	{
		if(x->cnt>1)
			x->cnt--;
		else if(!x->ls)
			x=x->rs;
		else if(!x->rs)
			x=x->ls;
		else 
		{
			if(x->ls->key>x->rs->key)
			{
				zig(x);
				del(x->ls,y);
			}
			else
			{
				zag(x);
				del(x->rs,y);
			}
		}
	}
	if(x) 
		push_up(x);
}
int query_rankk(Treap *&x,int y)
{
	if(x==NULL)
		return 0;
	int leftsize=(x->ls?x->ls->size:0);
	if(x->val==y)
		return leftsize+1;
	else if(x->val<y)
		return leftsize+x->cnt+query_rankk(x->rs,y);
	else 
		return query_rankk(x->ls,y);
}
int query_numk(Treap *&x,int y)
{
	if(x==NULL)
		return 0;
	int leftsize=(x->ls?x->ls->size:0);
	if(leftsize>=y)
		return query_numk(x->ls,y);
	else if(leftsize+x->cnt<y)
		return query_numk(x->rs,y-leftsize-x->cnt);
	else 
		return x->val; 
}/*
int query_pre(Treap *x,int y)
{
	if(x==NULL)
		return 0;
	else if(y<x->val)
		return query_pre(x->ls,y);
	else return max(x->val,query_pre(x->rs,y));
}
int query_sec(Treap *x,int y)
{
	if(x==NULL)
		return ~0u>>1;
	if(y>x->val)
		return query_sec(x->rs,y);
	else return min(x->val,query_sec(x->ls,y));
}*/
void query_pre(Treap *x,int y)
{
    if(x==NULL)
    	return;
    if(x->val<y)
	{
		ans=x;
		query_pre(x->rs,y);
	}
    else query_pre(x->ls,y);
}
void query_sec(Treap *x,int y)
{
	if(x==NULL)
		return;
	if(x->val>y)
	{
		ans=x;
		query_sec(x->ls,y);
	}
	else query_sec(x->rs,y);
}
int n;
int main()
{
//	freopen("input4.in","r",stdin);
//	freopen("ans.out","w",stdout);
	srand(20000612);
	rand();
	scanf("%d",&n);
	int opt,x;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1)
			insert(root,x);
		else if(opt==2)
			del(root,x);
		else if(opt==3)
			printf("%d\n",query_rankk(root,x));
		else if(opt==4)
			printf("%d\n",query_numk(root,x));
		else if(opt==5)
		{
			ans=NULL;
			query_pre(root,x);
			printf("%d\n",ans->val);
		}
		else if(opt==6)
		{
			ans=NULL;
			query_sec(root,x);
			printf("%d\n",ans->val);
		}
	}
	return 0;
}












