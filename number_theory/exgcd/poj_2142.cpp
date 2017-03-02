#include <stdio.h>
#include <algorithm>
#define abs(x) ((x)>0?(x):-(x))
using namespace std;
typedef long long ll;
ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	ll g=ex_gcd(b,a%b,x,y);
	ll tmp=x;
	x=y;
	y=tmp-a/b*y;
	return g;
}
ll a,b,d;
int main()
{
	while(scanf("%lld%lld%lld",&a,&b,&d)==3&&(a||b||d))
	{
		bool flag=false;
		ll x=0,y=0;
		if(a<b)
			swap(a,b),flag=true;
		ll gcd=ex_gcd(a,b,x,y);
		a/=gcd;
		b/=gcd;
		d/=gcd;
		x*=d;
		y*=d;
		ll t=y/a;
		while(y-a*t<0)	
			--t;
		ll x1,x2,y1,y2;
		x1=abs(x+b*t);
		y1=abs(y-a*t);
		++t;
		x2=abs(x+b*t);
		y2=abs(y-a*t);
		ll rx,ry;
		if((x1+y1<x2+y2)||(x1+y1==x2+y2&&x1*a+y1*b<x2*a+y2*b))
			rx=x1,ry=y1;
		else
			rx=x2,ry=y2;
		if(flag)
			printf("%lld %lld\n",ry,rx);
		else
			printf("%lld %lld\n",rx,ry);
	}
}
