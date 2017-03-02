#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAXN=262200;
typedef long long ll;
struct segment_tee
{
	int l,r,lazy;
	ll x;
}t[MAXN];
int n;
int a[MAXN];
int m;
void build(int x,int l,int r);
ll query(int x,int l,int r);
void push_down(int x);
void modify(int x,int l,int r,int v);
int opt,qx,qy,c;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&qx,&qy,&c);
			modify(1,qx,qy,c);
		}
		if(opt==2)
		{
			scanf("%d%d",&qx,&qy);
			printf("%lld\n",query(1,qx,qy));
		}	
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
	t[x].x=t[x<<1].x+t[x<<1|1].x;
}
void push_down(int x)
{
	if(t[x].lazy)
	{
		if(t[x].l!=t[x].r)
		{
			t[x<<1].lazy+=t[x].lazy;
			t[x<<1|1].lazy+=t[x].lazy;
			t[x<<1].x+=t[x].lazy*(t[x<<1].r-t[x<<1].l+1);
			t[x<<1|1].x+=t[x].lazy*(t[x<<1|1].r-t[x<<1|1].l+1);
			t[x].lazy=0;
		}
}
	}
ll query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	push_down(x);  
    if(l==L&&R==r)
        return t[x].x;
    int mid=(L+R)>>1;
    if(mid>=r)
        return query(x<<1,l,r);
    else if(mid<l)
        return query(x<<1|1,l,r);
    else 
    	return query(x<<1,l,mid)+query(x<<1|1,mid+1,r);
}
void modify(int x,int l,int r,int v)
{	
    if(l==t[x].l&&r==t[x].r)
    {
        t[x].lazy+=v;
        t[x].x+=v*(r-l+1);
        return;
    }
    push_down(x);
    int mid=(t[x].l+t[x].r)>>1;
    if(mid>=r)
        modify(x<<1,l,r,v);
    else if(l>mid)
        modify(x<<1|1,l,r,v);
    else
    {
        modify(x<<1,l,mid,v);
        modify(x<<1|1,mid+1,r,v);
    }
	t[x].x=t[x<<1].x+t[x<<1|1].x;
}
