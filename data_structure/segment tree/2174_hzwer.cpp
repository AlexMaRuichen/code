#include<iostream>
#include<cstdio>
using namespace std;
int n,q,a[100001];
struct data{
   int l,r,mn;
}tr[400001];
void build(int k,int s,int t)
{
	tr[k].l=s;tr[k].r=t;
	if(s==t){tr[k].mn=a[s];return;}
	int mid=(s+t)>>1;
	build(k<<1,s,mid);
	build(k<<1|1,mid+1,t);
	tr[k].mn=min(tr[k<<1].mn,tr[k<<1|1].mn);
}
int ask(int k,int s,int t)
{
	int l=tr[k].l,r=tr[k].r;
	if(s==l&&t==r)return tr[k].mn;
	int mid=(l+r)>>1;
	if(t<=mid)return ask(k<<1,s,t);
	if(s>mid)return ask(k<<1|1,s,t);
	return min(ask(k<<1,s,mid),ask(k<<1|1,mid+1,t));
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	   scanf("%d",&a[i]);
    build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d ",ask(1,x,y));
	}
	return 0;
}
