#include <stdio.h>
#include <algorithm>
using namespace std;
struct segment_tree
{
	int l,r,x;
}t[262150];
int m,n;
int a[100001];
void build(int x,int l,int r);
int query(int x,int l,int r);
int modify(int x,int p,int v);
int opt,ql,qr;
bool s;
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	build(1,1,m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&opt,&ql,&qr);
		if(opt==1)
			if(!s)
				printf("%d",query(1,ql,qr)),s=true;
			else
				printf(" %d",query(1,ql,qr));
		else
			modify(1,ql,qr);
			
	}
}
void build(int x,int l,int r)
{
	t[x].l=l;
	t[x].r=r;
	if(l==r)
	{
		t[x].x=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x].x=min(t[x<<1].x,t[x<<1|1].x);
}
int query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	if(L==l&&R==r)
		return t[x].x;
	int mid=(L+R)>>1;
	if(r<=mid)
		return query(x<<1,l,r);
	if(l>mid)
		return query(x<<1|1,l,r);
	return min(query(x<<1,l,mid),query(x<<1|1,mid+1,r));
}
int modify(int x,int p,int v)
{
	if(t[x].l==t[x].r&&t[x].l==p)	
		return t[x].x=v;
	int mid=(t[x].l+t[x].r)>>1;
	if(p<=mid)
		modify(x<<1,p,v);
	if(p>mid)
		modify(x<<1|1,p,v);
	t[x].x=min(t[x<<1].x,t[x<<1|1].x);
}
