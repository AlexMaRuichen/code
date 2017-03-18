#include <bitset>
using namespace std;
const int maxn=1e7;
int mod;
bitset <maxn+10> v;
int prime[664600];
void linear_shaker()
{
    for(register int i=2;i<=maxn;i++)
    {
        if(!v[i])
            prime[++prime[0]]=i;
        for(register int j=1;j<=prime[0]&&i*prime[j]<=maxn;j++)
        {
            v[i*prime[j]]=true;
            if(i%prime[j]==0)
                break;
        }
    }
}
 
int inv[maxn+10];
void inverse()
{
    inv[1]=1;
    for(register int i=2;i<=maxn&&i<mod;i++)
        inv[i]=(mod-mod/i)*1ll*inv[mod%i]%mod;
}
 
int fac[maxn+10];
void factorial()
{
    fac[0]=1;
    for(register int i=1;i<=maxn;i++)
        fac[i]=fac[i-1]*1ll*i%mod;
}
 
int ans[maxn+10];
void pre()
{
    ans[1]=1;
    for(register int i=2;i<=maxn;i++)
        if(!v[i])
            ans[i]=ans[i-1]*1ll*(i-1)%mod*inv[i%mod]%mod;
        else
            ans[i]=ans[i-1];
}
 
int main()
{
    int T;
    scanf("%d%d",&T,&mod);
    linear_shaker();
    inverse();
    factorial();
    pre();
    int n,m;
    while(T--)
    {
        scanf("%d%d",&n,&m);
        printf("%lld\n",fac[n]*1ll*ans[m]%mod);
    }
}
