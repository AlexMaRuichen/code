#include <bits/stdc++.h>
using namespace std;
#define ll long long 
ll n,pr[31];
int cnt,num[31];
int quit(int x){printf("%d\n",x);exit(0);}
void get(ll x)
{
    cnt=0;
    for(int i=2;(ll)i*i<=x;i++)
        if(x%i==0)
        {
            pr[++cnt]=i;num[cnt]=0;
            while(x%i==0)
                num[cnt]++,x/=i;
        }
    if(x!=1)
        pr[++cnt]=x,num[cnt]=1;
}
ll get_phi(ll x)
{
    ll ret=1;
    for(int i=2;(ll)i*i<=x;i++)
        if(x%i==0)
        {
            ret*=(i-1);x/=i;
            while(x%i==0)
                ret*=i,x/=i;
        }
    if(x!=1)ret*=x-1;
    return ret;
}
ll mul(ll x,ll y)
{
    ll ret=0;
    while(y)
    {
        if(y&1)ret=(ret+x)%n;
        x=(x+x)%n;y>>=1;
    }
    return ret;
}
ll qpow(ll x,ll y)
{
    ll ret=1;
    while(y)
    {
        if(y&1)ret=mul(ret,x);
        x=mul(x,x);y>>=1;
    }
    return ret;
}
int check(ll x)
{
    if(x%4==0)return 0;
    if(x%2==0)x/=2;
    get(x);
    return cnt==1;
}
int find_g(ll x)
{
    ll phi=get_phi(x);
    get(phi);
    for(int g=2;;g++)
    {
        int flag=0;
        for(int i=1;i<=cnt;i++)
            if(qpow(g,phi/pr[i])==1)
                {flag=1;break;}
        if(!flag)return g;
    }
}
int main()
{
    scanf("%lld",&n);
    if(n==2)quit(1);
    if(n==4)quit(2);
    if(!check(n))quit(-1);
    printf("%d\n",find_g(n));
    return 0;
}
