#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod=100003;
ll mul(ll x,ll y);
ll m,n;
ll ans;
int main()
{
	scanf("%lld%lld",&m,&n);
	ans=mul(m,n);
	ans-=(m*mul(m-1,n-1))%mod;
	printf("%lld\n",(ans%mod+mod)%mod);
}
ll mul(ll x,ll y)
{
	ll ans=1;
	while(y)
	{
		if(y&1)
			(ans*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return ans;
}
