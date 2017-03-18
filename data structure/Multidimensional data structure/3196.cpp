#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;
const int inf=1e9;
const int maxn=50010;
const int N=50000;
int n,m;

struct Treap
{
	Treap *ls,*rs;
	int size,val,cnt,key;
	Treap(){}
	Treap(int x);
	void update();
}*null=new Treap(inf);
void Treap :: update()
{
	if(this==null)
		return;
	size=ls->size+rs->size+cnt;
}
Treap :: Treap(int x)
{
	ls=rs=null;
	size=x^inf?1:0;
	val=x;
	cnt=1;
	key=rand();
}
void zig(Treap* &x)
{
	Treap *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	x=y;
	x->rs->update();
	x->update();
}
void zag(Treap* &x)
{
	Treap *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	x=y;
	x->ls->update();
	x->update();
}
void insert(Treap* &x,int y)
{
	if(x==null)
	{
		x=new Treap(y);
		return ;
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
void del(Treap* &x,int y)
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
int pre(Treap *x,int y)
{
	if(x==null)
		return -inf;
	if(y<=x->val)
		return pre(x->ls,y);
	else	
		return max(pre(x->rs,y),x->val);
}
int suc(Treap *x,int y)
{
	if(x==null)
		return inf;
	if(y>=x->val)
		return suc(x->rs,y);
	else
		return min(suc(x->ls,y),x->val);
}
struct seg_tree
{
	seg_tree *ls,*rs;
	Treap *t;
	seg_tree(){ls=rs=NULL;t=null;}
}*root;
int a[maxn];
void build(seg_tree* &x,int l,int r)
{
	x=new seg_tree();
	for(int i=l;i<=r;i++)
		insert(x->t,a[i]);
	if(l==r)
		return;
	int mid=l+r>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
int RANK(seg_tree *x,int k,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return rank(x->t,k);
	int mid=L+R>>1;
	if(mid>=r)
		return RANK(x->ls,k,l,r,L,mid);
	else if(mid<l)
		return RANK(x->rs,k,l,r,mid+1,R);
	else
		return RANK(x->ls,k,l,mid,L,mid)+RANK(x->rs,k,mid+1,r,mid+1,R);
}
int PRE(seg_tree *x,int k,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return pre(x->t,k);
	int mid=L+R>>1;
	if(mid>=r)
		return PRE(x->ls,k,l,r,L,mid);
	else if(mid<l)
		return PRE(x->rs,k,l,r,mid+1,R);
	else
		return max(PRE(x->ls,k,l,mid,L,mid),PRE(x->rs,k,mid+1,r,mid+1,R));
}
int SUC(seg_tree *x,int k,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return suc(x->t,k);
	int mid=L+R>>1;
	if(mid>=r)
		return SUC(x->ls,k,l,r,L,mid);
	else if(mid<l)
		return SUC(x->rs,k,l,r,mid+1,R);
	else
		return min(SUC(x->ls,k,l,mid,L,mid),SUC(x->rs,k,mid+1,r,mid+1,R));
}
int KTH(seg_tree *x,int k,int l,int r)
{
	int L=0,R=1e8+10,mid;
	while(L<R)
	{
		mid=L+R>>1;
		if(RANK(x,mid,l,r,1,n)<k)
			L=mid+1;
		else
			R=mid;
	}
	if(RANK(x,L,l,r,1,n)>=k)
		L=PRE(x,L,l,r,1,n);
	return L;
}
void MODIFY(seg_tree *x,int p,int v,int l,int r)
{
	del(x->t,a[p]);
	insert(x->t,v);
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(mid>=p)
		MODIFY(x->ls,p,v,l,mid);
	else
		MODIFY(x->rs,p,v,mid+1,r);
}
int main()
{
	srand(20000612);
	rand();
	scanf("%d%d",&n,&m);
	null->ls=null->rs=null;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(root,1,n);
	for(int i=1;i<=m;i++)
	{
		static int opt,x,y;
		scanf("%d",&opt);
		if(opt==1)
			scanf("%d%d%d",&opt,&x,&y),printf("%d\n",RANK(root,y,opt,x,1,n)+1);
		else if(opt==2)
			scanf("%d%d%d",&opt,&x,&y),printf("%d\n",KTH(root,y,opt,x));
		else if(opt==3)
			scanf("%d%d",&x,&y),MODIFY(root,x,y,1,n),a[x]=y;
		else if(opt==4)
			scanf("%d%d%d",&opt,&x,&y),printf("%d\n",PRE(root,y,opt,x,1,n));
		else if(opt==5)
			scanf("%d%d%d",&opt,&x,&y),printf("%d\n",SUC(root,y,opt,x,1,n));
	}
}
