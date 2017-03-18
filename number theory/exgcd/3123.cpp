#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a,b,c,bit,mod;
ll x,y;
ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	ll g=ex_gcd(b,a%b,x,y);
	ll tmp=x;
	x=y;
	y=tmp-(a/b)*y;
	return g;
}
int main()
{
	while(scanf("%lld%lld%lld%lld",&a,&b,&c,&bit)==4&&(a!=0||b!=0||c!=0||bit!=0))
	{	
		if((b-a)==0)
		{
			puts("0");
			continue;
		}
		mod=1ll<<bit;
		ll A=c;
		ll B=mod;
		ll C=((b-a)%mod+mod)%mod;
		ll g=ex_gcd(A,B,x,y);
		if((b-a)%g)
		{
			puts("FOREVER");
			continue;
		}
		(x+=mod)%=mod;
		ll k=C/g;
		mod/=g;
		printf("%lld\n",(x*k%mod+mod)%mod);
	}
}
