#include <stdio.h>
#include <algorithm>
using namespace std;
struct segment_tree
{
	int l,r,x;
}t[400001];
int a[100001],m,n;
void build(int x,int l,int r);
int query(int x,int l,int r);
int ql,qr;
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	build(1,1,m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&ql,&qr);
		if(i==1)
			printf("%d",query(1,ql,qr));
		else
			printf(" %d",query(1,ql,qr));
	}
		
}
int query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	if(l==L&&r==R)
		return t[x].x;
	int mid=(L+R)>>1;
	if(r<=mid)
		return query(x<<1,l,r);
	if(l>mid)
		return query((x<<1)|1,l,r);
	return min(query(x<<1,l,mid),query((x<<1)|1,mid+1,r));
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
	build((x<<1)|1,mid+1,r);
	t[x].x=min(t[x<<1].x,t[(x<<1)|1].x);
}
