#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#define inf 0x7fffffff
#define ll long long
#define N 100005
#define M 5000005
using namespace std;
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll ans;
int n,m,sz;
int A[30],B[30];
int num[N],pos[N],a1[N],a2[N];
int t[N],root[N];
int ls[M],rs[M],sum[M];
inline int lowbit(int x){return x&(-x);}
inline int getans(int x)
{
	int tmp=0;
	for(int i=x;i;i-=lowbit(i))
	    tmp+=t[i];
	return tmp;
}
void update(int &y,int l,int r,int x)
{
    if(!y)y=++sz;
    sum[y]++;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)update(ls[y],l,mid,x);
    else update(rs[y],mid+1,r,x);
}
int askmore(int x,int y,int num)
{
	A[0]=B[0]=0;int tmp=0;x--;
	for(int i=x;i;i-=lowbit(i))A[++A[0]]=root[i];
	for(int i=y;i;i-=lowbit(i))B[++B[0]]=root[i];
	int l=1,r=n;
	while(l!=r)
	{
		int mid=(l+r)>>1;
        if(num<=mid)
        {
            for(int i=1;i<=A[0];i++)tmp-=sum[rs[A[i]]];
            for(int i=1;i<=B[0];i++)tmp+=sum[rs[B[i]]];
            for(int i=1;i<=A[0];i++)A[i]=ls[A[i]];
            for(int i=1;i<=B[0];i++)B[i]=ls[B[i]];
            r=mid;
        }
		else
        {
            for(int i=1;i<=A[0];i++)A[i]=rs[A[i]];
            for(int i=1;i<=B[0];i++)B[i]=rs[B[i]];
            l=mid+1;
        }
	}
	return tmp;
}
int askless(int x,int y,int num)
{
	A[0]=B[0]=0;int tmp=0;x--;
	for(int i=x;i;i-=lowbit(i))A[++A[0]]=root[i];
	for(int i=y;i;i-=lowbit(i))B[++B[0]]=root[i];
	int l=1,r=n;
	while(l!=r)
	{
		int mid=(l+r)>>1;
        if(num>mid)
        {
            for(int i=1;i<=A[0];i++)tmp-=sum[ls[A[i]]];
            for(int i=1;i<=B[0];i++)tmp+=sum[ls[B[i]]];
            for(int i=1;i<=A[0];i++)A[i]=rs[A[i]];
            for(int i=1;i<=B[0];i++)B[i]=rs[B[i]];
            l=mid+1;
        }
		else
        {
            for(int i=1;i<=A[0];i++)A[i]=ls[A[i]];
            for(int i=1;i<=B[0];i++)B[i]=ls[B[i]];
            r=mid;
        }
	}
	return tmp;
}
int main()
{
	n=read();m=read();
    for(int i=1;i<=n;i++)
    {
    	num[i]=read();pos[num[i]]=i;
    	a1[i]=getans(n)-getans(num[i]);
    	ans+=a1[i];
    	for(int j=num[i];j<=n;j+=lowbit(j))
    	    t[j]++;
    }
    memset(t,0,sizeof(t));
    for(int i=n;i>=1;i--)
    {
    	a2[i]=getans(num[i]-1);
    	for(int j=num[i];j<=n;j+=lowbit(j))
    	    t[j]++;
    }
    for(int i=1;i<=m;i++)
    {
    	printf("%lld\n",ans);
    	int x=read();x=pos[x];
    	ans-=(a1[x]+a2[x]-askmore(1,x-1,num[x])-askless(x+1,n,num[x]));
        for(int j=x;j<=n;j+=lowbit(j))update(root[j],1,n,num[x]);
	}
	return 0;
}
