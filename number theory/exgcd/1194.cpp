#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll X,Y;
ll ex_gcd(ll a,ll b,ll &X,ll &Y)
{
	if(b==0)
	{
		X=1;
		Y=0;
		return a;
	}
	ll g=ex_gcd(b,a%b,X,Y);
	ll tmp=X;
	X=Y;
	Y=tmp-(a/b)*Y;
	return g;
}
ll n,m,x,y,l;
int main()
{
	scanf("%lld%lld%lld%lld%lld",&x,&y,&n,&m,&l);
	ll a=((n-m)+l)%l;
	ll b=l;
	ll c=((y-x)+l)%l;
	ll g=ex_gcd(a,b,X,Y);
	if(c%g)
	{
		puts("Impossible");
		return 0;
	}
	ll k=c/g;
	X*=k;
	l/=g;
    ((X%=l)+=l)%=l;  
	printf("%lld\n",X);
}


