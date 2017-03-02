#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
int mod;
int mul(long long x,long long y);
long long k,x;
long long c;
int main()
{
	scanf("%d%d%lld%lld",&n,&m,&k,&x);
	mod=n/__gcd(n,m);
	c=mul(10,(long long)k);
	printf("%lld\n",(x+m*c)%n);
}
int mul(long long x,long long y)
{
	long long ans=1;
	while(y)
	{
		if(y&1)
			(ans*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return ans;
}
