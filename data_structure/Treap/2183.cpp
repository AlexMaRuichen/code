#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n;
struct Treap
{
	Treap *ls,*rs;
	int cnt,size,val,key;
	Treap(int x)
	{
		ls=rs=NULL;
		cnt=size=1;
		val=x;
		key=rand();
	}
}*root,*ans;
void update(Treap* &x)
{
	x->size=x->cnt;
	if(x->ls)
		x->size+=x->ls->size;
	if(x->rs)
		x->size+=x->rs->size;
}
void zig(Treap* &x)
{
	Treap *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	if(x)
		update(x);
	x=y;
	if(x)
		update(x);
}
void zag(Treap* &x)
{
	Treap *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	if(x)
		update(x);
	x=y;
	if(x)
		update(x);
}
void insert(Treap* &x,int v)
{
	if(!x)
	{
		x=new Treap(v);
		return;
	}	
	else if(v==x->val)
		++x->cnt;
	else if(v>x->val)
	{
		insert(x->rs,v);
		if(x->rs->key>x->key)
			zig(x);
	}
	else if(v<x->val)
	{
		insert(x->ls,v);
		if(x->ls->key>x->key)
			zag(x);
	}
	if(x)
		update(x);
}
void del(Treap* &x,int v)
{
	if(x==NULL)
		return;
	if(x->val<v)
		del(x->rs,v);
	else if(x->val>v)
		del(x->ls,v);
	else if(x->cnt>1)
		--x->cnt;
	else if(!x->ls)
		x=x->rs;
	else if(!x->rs)
		x=x->ls;
	else if(x->ls->key>x->rs->key)
		zig(x),del(x->ls,v);
	else
		zag(x),del(x->rs,v);
}
int query_rank(Treap* &x,int y)
{
	if(!x)
		return 0;
	int l=(x->ls?x->ls->size:0);
	if(x->val==y)
		return l+1;
	else if(x->val>y)
		return l+x->cnt+query_rank(x->rs,y);
	else
		return query_rank(x->ls,y);
}
int query_num(Treap* &x,int y)
{
	if(!x)
		return 0;
	int l=(x->ls?x->ls->size:0);
	if(l>=y)
		return query_num(x->ls,y);
	else if(l+x->cnt<y)
		return query_num(x->rs,y-l-x->cnt);
	else
		return x->val;
}
void query_pre(Treap* &x,int y)
{
	if(!x)
		return;
	if(x->val<y)
		ans=x,query_pre(x->rs,y);
	else
		query_pre(x->ls,y);		
}
void query_suc(Treap* &x,int y)
{
	if(!x)
		return;
	if(x->val>y)
		ans=x,query_suc(x->ls,y);
	else
		query_suc(x->rs,y);
}
int main()
{
	srand(20000612);
	rand();
	scanf("%d",&n);
	while(n--)
	{
		static int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
			insert(root,x);
		else if(opt==2)
			del(root,x);
		else if(opt==3)
			printf("%d\n",query_rank(root,x));
		else if(opt==4)
			printf("%d\n",query_num(root,x));
		else if(opt==5)
			query_pre(root,x),printf("%d\n",ans->val);
		else if(opt==6)
			query_suc(root,x),printf("%d\n",ans->val);
	}
}
