#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=5000010;
ll a[maxn];
ll n;
ll sa,sb,sc,sd;
ll mod;
ll m;
ll ans;
ll f(ll x)
{
	return (sa*x%mod*x%mod*x%mod+sb*x%mod*x%mod+sc*x%mod+sd)%mod;
}
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&sa,&sb,&sc,&sd,&a[1],&mod);
	for(int i=2;i<=n;i++)
		a[i]=(f(a[i-1])+f(a[i-2]))%mod;
	for(int i=1;i<=n;i++)
	{
		m=max(m,a[i]);
		ans=max(ans,m-a[i]+1>>1);
	}
	printf("%lld\n",ans);
}
