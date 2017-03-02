#include <bits/stdc++.h>
using namespace std;
const int maxn=2e4+10;
const int maxm=1e6;
const int inf=1e9+10;
int n,m;
int a[maxn];
struct Treap
{
	Treap *ls,*rs;
	int val,size,cnt,key;
	Treap(){}
	Treap(int x);
	void update();
	void* operator new(size_t);
}*null=new Treap(inf),mempool[maxm];
queue <Treap*> q;
void* Treap :: operator new(size_t)
{
	static Treap *p=mempool;
	if(!q.empty())
	{
		Treap *tmp=q.front();
		q.pop();
		return tmp;
	}
	return p++;
}
Treap :: Treap (int x)
{
	ls=rs=null;
	val=x,cnt=1,size=x^inf?1:0;
	key=rand();
}
void Treap :: update()
{
	if(this==null)
		return;
	size=ls->size+rs->size+cnt;
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
	if(x->val>y)	insert(x->ls,y);
	else if(x->val<y)	insert(x->rs,y);
	else	x->cnt++;
	x->update();
}
void del(Treap *&x,int y)
{
	if(x->val>y)	del(x->ls,y);
	else if(x->val<y)	del(x->rs,y);
	else
	{
		if(x->cnt^1)	x->cnt--;
		else if(x->ls==null)
			q.push(x),x=x->rs;
		else if(x->rs==null)
			q.push(x),x=x->ls;
		else
		{
			zag(x);
			del(x->ls,y);
			if(x->ls!=null&&x->ls->key>x->key)
				zig(x);
		}
	}
	x->update();
}
int prev(Treap *x,int y)
{
	int ret=0;
	while(x!=null)
		if(x->val>=y)
			x=x->ls;
		else
			ret+=(x->ls?x->ls->size:0)+x->cnt,x=x->rs;
	return ret;
}
int next(Treap *x,int y)
{
	int ret=0;
	while(x!=null)
		if(x->val<=y)
			x=x->rs;
		else
			ret+=(x->rs?x->rs->size:0)+x->cnt,x=x->ls;
	return ret;
}
struct seg_tree
{
	seg_tree *ls,*rs;
	Treap *t;
	seg_tree(){ls=rs=NULL;t=null;}
}*root;
void build(seg_tree *&x,int l,int r)
{
	x=new seg_tree();
	for(int i=l;i<=r;++i)
		insert(x->t,a[i]);
	if(l==r)
		return;
	int mid=l+r>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
void MODIFY(seg_tree *x,int p,int v,int l,int r)
{
	del(x->t,a[p]);
	insert(x->t,v);
	if(l==r)
		return;
	int mid=l+r>>1;
	if(p<=mid)	MODIFY(x->ls,p,v,l,mid);
	else	MODIFY(x->rs,p,v,mid+1,r);
}
int PREV(seg_tree *x,int l,int r,int k,int L,int R)
{
	if(l>r)
		return 0;
	if(l<=L&&R<=r)
		return prev(x->t,k);
	int mid=L+R>>1;
	int ret=0;
	if(l<=mid)	ret+=PREV(x->ls,l,r,k,L,mid);
	if(r>mid)	ret+=PREV(x->rs,l,r,k,mid+1,R);
	return ret;
}
int NEXT(seg_tree *x,int l,int r,int k,int L,int R)
{
	if(l>r)
		return 0;
	if(l<=L&&R<=r)
		return next(x->t,k);
	int mid=L+R>>1;
	int ret=0;
	if(l<=mid)	ret+=NEXT(x->ls,l,r,k,L,mid);
	if(r>mid)	ret+=NEXT(x->rs,l,r,k,mid+1,R);
	return ret;
}
int sum;
void work()
{
	int x,y;
	scanf("%d%d",&x,&y);
	if(a[x]==a[y])
	{
		printf("%d\n",sum);
		return;
	}
	if(x>y)	swap(x,y);
	if(a[x]<a[y])	sum++;
	else	sum--;
	sum+=(NEXT(root,x+1,y-1,a[x],1,n)-PREV(root,x+1,y-1,a[x],1,n));
	sum-=(NEXT(root,x+1,y-1,a[y],1,n)-PREV(root,x+1,y-1,a[y],1,n));
	MODIFY(root,x,a[y],1,n);
	MODIFY(root,y,a[x],1,n);
	swap(a[x],a[y]);
	printf("%d\n",sum);
}
int main()
{
	srand(20150227);
	rand();
	int c=clock();
	null->ls=null->rs=null;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	build(root,1,n);
	scanf("%d",&m);
	for(int i=2;i<=n;++i)
		sum+=NEXT(root,1,i-1,a[i],1,n);
	printf("%d\n",sum);
	for(int i=1;i<=m;++i)
		work();
	fprintf(stderr,"%lf\n",double(clock()-c)/CLOCKS_PER_SEC);
}

