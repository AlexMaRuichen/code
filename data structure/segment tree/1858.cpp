#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
struct seg_tree
{
	seg_tree *ls,*rs;
	bool rev;
	int to;
	int lmx[2],rmx[2],mx[2],sum[2],len;
	seg_tree()
	{
		ls=rs=NULL;
		rev=false;
		len=0;
		to=-1;
		for(int i=0;i<2;i++)
			lmx[i]=rmx[i]=mx[i]=sum[i]=0;
	}
	void update()
	{
		for(int i=0;i<2;i++)
		{
			sum[i]=ls->sum[i]+rs->sum[i];
			mx[i]=max(max(ls->mx[i],rs->mx[i]),ls->rmx[i]+rs->lmx[i]);
			if(ls->lmx[i]==ls->len)
				lmx[i]=ls->len+rs->lmx[i];
			else
				lmx[i]=ls->lmx[i];
			if(rs->rmx[i]==rs->len)
				rmx[i]=rs->len+ls->rmx[i];
			else
				rmx[i]=rs->rmx[i];
		}
	}
	void push_down()
	{
		if(to>=0)
		{
			ls->to=to;
			rs->to=to;
			ls->rev=rs->rev=false;
			ls->mx[to]=ls->lmx[to]=ls->rmx[to]=ls->sum[to]=ls->len;
			rs->mx[to]=rs->lmx[to]=rs->rmx[to]=rs->sum[to]=rs->len;
			ls->mx[to^1]=ls->lmx[to^1]=ls->rmx[to^1]=ls->sum[to^1]=0;
			rs->mx[to^1]=rs->lmx[to^1]=rs->rmx[to^1]=rs->sum[to^1]=0;
			to=-1;
		}
		if(rev)
		{
			ls->rev^=1;
			rs->rev^=1;
			swap(ls->sum[0],ls->sum[1]);
			swap(ls->lmx[0],ls->lmx[1]);
			swap(ls->rmx[0],ls->rmx[1]);
			swap(ls->mx[0],ls->mx[1]);
			swap(rs->sum[0],rs->sum[1]);
			swap(rs->lmx[0],rs->lmx[1]);
			swap(rs->rmx[0],rs->rmx[1]);
			swap(rs->mx[0],rs->mx[1]);
			rev=false;
		}	
	}
}*root=new seg_tree();
int c;
void build(seg_tree* &x,int l,int r)
{
	x->len=r-l+1;
	if(l==r)
	{
		scanf("%d",&c);
		x->sum[c]=x->lmx[c]=x->rmx[c]=x->mx[c]=1;
		return;
	}
	int mid=(l+r)>>1;
	x->ls=new seg_tree();
	x->rs=new seg_tree();
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
	x->update();
}
void modify(seg_tree* &x,int l,int r,bool tag,int L,int R)
{
	if(l==L&&r==R)
	{
		x->rev=false;
		x->sum[tag]=x->lmx[tag]=x->rmx[tag]=x->mx[tag]=x->len;
		x->sum[tag^1]=x->lmx[tag^1]=x->rmx[tag^1]=x->mx[tag^1]=0;
		x->to=tag;
		return;
	}
	x->push_down();
	int mid=(L+R)>>1;
	if(mid>=r)
		modify(x->ls,l,r,tag,L,mid);
	else if(mid<l)
		modify(x->rs,l,r,tag,mid+1,R);
	else
		modify(x->ls,l,mid,tag,L,mid),modify(x->rs,mid+1,r,tag,mid+1,R);
	x->update();
}
void reverse(seg_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
	{
		swap(x->sum[0],x->sum[1]);
		swap(x->lmx[0],x->lmx[1]);
		swap(x->rmx[0],x->rmx[1]);
		swap(x->mx[0],x->mx[1]);
		x->rev^=1;
		return;
	}
	x->push_down();
	int mid=(L+R)>>1;
	if(mid>=r)
		reverse(x->ls,l,r,L,mid);
	else if(mid<l)
		reverse(x->rs,l,r,mid+1,R);
	else
		reverse(x->ls,l,mid,L,mid),reverse(x->rs,mid+1,r,mid+1,R);
	x->update();
}
int query_sum(seg_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x->sum[1];
	x->push_down();
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_sum(x->ls,l,r,L,mid);
	else if(mid<l)
		return query_sum(x->rs,l,r,mid+1,R);
	else
		return query_sum(x->ls,l,mid,L,mid)+query_sum(x->rs,mid+1,r,mid+1,R);
}
seg_tree* merge(seg_tree *a,seg_tree *b)
{
	seg_tree *ans=new seg_tree();
	ans->ls=a;
	ans->rs=b;
	ans->len=a->len+b->len;
	ans->update();
	return ans;
}
seg_tree* query_len(seg_tree* &x,int l,int r,int L,int R)
{
	if(l==L&&r==R)
		return x;
	x->push_down();
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_len(x->ls,l,r,L,mid);
	else if(mid<l)
		return query_len(x->rs,l,r,mid+1,R);
	else
	{
		seg_tree *a=query_len(x->ls,l,mid,L,mid);
		seg_tree *b=query_len(x->rs,mid+1,r,mid+1,R);
		return merge(a,b);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	build(root,1,n);
	while(m--)
	{
		static int opt,l,r;
		scanf("%d%d%d",&opt,&l,&r);
		++l,++r;
		if(opt<2)
			modify(root,l,r,opt,1,n);
		else if(opt==2)
			reverse(root,l,r,1,n);
		else if(opt==3)
			printf("%d\n",query_sum(root,l,r,1,n));
		else if(opt==4)
			printf("%d\n",query_len(root,l,r,1,n)->mx[1]);
	}
}

