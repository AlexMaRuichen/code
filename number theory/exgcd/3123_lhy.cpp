#include <cstdio>
typedef long long ll;
ll a,b,c,k,mod,X,Y,gcdx;
ll exgcd(ll md,ll zz)
{
    if(!zz)
    {
        X=1,Y=0;
        return md;
    }
    ll ans=exgcd(zz,md%zz);
    ll x=X;
    X=Y;
    Y=x-(md/zz)*Y;
    return ans;
}
int main()
{
    while(scanf("%lld%lld%lld%lld",&a,&b,&c,&k)!=EOF)
    {
        if(!a&&!b&&!c&&!k)
            return 0;
        mod=1ll<<k;
        b=((b-a)%mod+mod)%mod;
        ll tmp=exgcd(c,mod);
        if(b%tmp!=0)
        {
            printf("FOREVER\n");
            continue;
        }
        X*=(b/tmp);
        X=(X%(mod/tmp)+(mod/tmp))%(mod/tmp);
        printf("%lld\n",X);
    }
    return 0;
}
