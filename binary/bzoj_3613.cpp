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
ll f(ll x)
{
	return (sa*x%mod*x%mod*x%mod+sb*x%mod*x%mod+sc*x%mod+sd)%mod;
}
bool check(ll x)
{
	ll d=~0ull>>1;
	for(int i=n;i;i--)
	{
		if(a[i]<=d)
			d=min(d,a[i]+x);
		else if(a[i]-d>x)
			return false;	
	}
	return true;
}
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&sa,&sb,&sc,&sd,&a[1],&mod);
	for(int i=2;i<=n;i++)
	{
		a[i]=(f(a[i-1])+f(a[i-2]))%mod;
		m=m>a[i]?m:a[i];
	}
	ll l=1,r=mod-1,mid;
	while(r-l>1)
	{
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%lld\n",check(l)?l:r);
}
