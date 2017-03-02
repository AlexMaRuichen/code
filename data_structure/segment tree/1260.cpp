#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=500010;
const int inf=~0u>>2;
int n,m;
struct segment_tree
{
	int l,r,sum,lm,rm,m;
	segment_tree()
	{
		l=r=sum=0;
		lm=rm=m=-inf;
	}
}t[1048580];
int a[maxn];
void update(segment_tree &x,segment_tree a,segment_tree b)
{
	x.sum=a.sum+b.sum;
	x.lm=max(a.lm,a.sum+b.lm);
	x.rm=max(b.rm,b.sum+a.rm);
	x.m=max(a.rm+b.lm,max(a.m,b.m));
}
void build(int x,int l,int r)
{
	t[x].l=l;
	t[x].r=r;
	if(l==r)
	{
		t[x].m=t[x].sum=t[x].lm=t[x].rm=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	update(t[x],t[x<<1],t[x<<1|1]);
}
void modify(int x,int p,int v)
{
	int L=t[x].l;
	int R=t[x].r;
	if(L==R&&L==p)
	{
		t[x].m=t[x].sum=t[x].lm=t[x].rm=v;
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=p)
		modify(x<<1,p,v);
	if(mid<p)
		modify(x<<1|1,p,v);
	update(t[x],t[x<<1],t[x<<1|1]);
}
segment_tree query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	if(l==L&&R==r)
		return t[x];
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x<<1,l,r);
	else if(mid<l)
		return query(x<<1|1,l,r);
	else
	{
		segment_tree a=query(x<<1,l,mid);
		segment_tree b=query(x<<1|1,mid+1,r);
		segment_tree ans;
		update(ans,a,b);
		return ans;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			if(x>y)
				swap(x,y);
			segment_tree tmp=query(1,x,y);
			printf("%d\n",max(tmp.m,max(tmp.lm,tmp.rm)));
		}
		if(opt==2)
			modify(1,x,y);
	}	
}
