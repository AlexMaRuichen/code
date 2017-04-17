#include<cstdio>
#include<iostream>
#define mo 1000000007
using namespace std;
int n,m;
const int lim=1000000;
int prime[lim/10+5],mu[lim+5];
int sf[lim+5],f[lim+5],invf[lim+5],sg[lim+5],g[lim+5],invg[lim+5];
bool vis[lim+5];
int qr(int x,int y)
{
    int t=1;
    for (;y;y>>=1,x=1LL*x*x%mo)
        if (y&1) t=1LL*t*x%mo;
    return t;
}
void init()
{
    mu[1]=1;
    for (int i=2;i<=lim;++i)
    {
        if (!vis[i])
            prime[++prime[0]]=i,
            mu[i]=-1;
        for (int j=1;j<=prime[0]&&i*prime[j]<=lim;++j)
        {
            vis[i*prime[j]]=1;
            if (i%prime[j])
                mu[i*prime[j]]=-mu[i];
            else
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
    f[0]=0;
    sf[1]=1;
    f[1]=1;
    g[1]=1;
    sg[1]=1;
    invg[0]=invg[1]=invf[0]=invf[1]=1;
    for (int i=2;i<=lim;++i)
    {
        f[i]=f[i-1]+f[i-2];
        if (f[i]>=mo) f[i]-=mo;
        sf[i]=1LL*sf[i-1]*f[i]%mo;
        g[i]=1;
    }
    invf[lim]=qr(sf[lim],mo-2);
    for (int i=lim;i>=2;--i)
        invf[i-1]=1LL*invf[i]*f[i]%mo,
        invf[i]=1LL*invf[i]*sf[i-1]%mo;
    for (int i=2;i<=lim;++i)
    {
        for (int j=1;i*j<=lim;++j)
        if (mu[j]==1)
            g[i*j]=1LL*g[i*j]*f[i]%mo;
        else if (mu[j]==-1)
            g[i*j]=1LL*g[i*j]*invf[i]%mo;
        sg[i]=1LL*sg[i-1]*g[i]%mo;
    }
    invg[lim]=qr(sg[lim],mo-2);
    for (int i=lim;i>=2;--i) invg[i-1]=1LL*invg[i]*g[i]%mo;
	for (int i = 0; i <= 10; i++)
		printf("%d ", invg[i]);
	puts("");
}
void work()
{
    scanf("%d%d",&n,&m);
    int t;
    if (n>m) swap(n,m);
    int ans=1;
    for (int last,t,i=1;i<=n;i=last+1)
        last=min(n/(n/i),m/(m/i)),
        ans=1LL*ans*qr(1LL*sg[last]*invg[i-1]%mo,1LL*(n/i)*(m/i)%(mo-1))%mo;
    printf("%d\n",ans);
}
int main()
{
    init();
    int T;
    for (scanf("%d",&T);T;--T) work();
    return 0;
}
