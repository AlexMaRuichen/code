#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a,b,c,x1,y1,x2,y2;
ll x,y;
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
	y=tmp-(a/abs(b))*y;
	return g;
}
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld",&a,&b,&c,&x1,&x2,&y1,&y2);
	c=-c;
	if(a==0&&b==0&&c!=0)
	{
		puts("0");
		return 0;
	}
	else if(a==0&&b==0&&c==0)
	{
		printf("%lld\n",(x2-x1+1)*(y2-y1+1));
		return 0;
	}
	else if(a==0&&b!=0&&c!=0)
	{
		if(c%b==0&&y1<=c/b&&y2>=c/b)
			printf("%lld\n",(x2-x1+1));
		else
			puts("0");
		return 0;
	}
	else if(a!=0&&b==0&&c!=0)
	{
		if(c%a==0&&x1<=c/a&&x2>=c/a)
			printf("%lld\n",(y2-y1+1));
		else
			puts("0");
		return 0;
	}
	else if(a==0&&b!=0&&c==0)
	{
		if(0>=y1&&0<=y2)
			printf("%lld\n",(x2-x1+1));
		else
			puts("0");
		return 0;
	}
	else if(a!=0&&b==0&&c==0)
	{
		if(0>=x1&&0<=x2)
			printf("%lld\n",(y2-y1+1));
		else
			puts("0");
		return 0;
	}
	ll gcd=ex_gcd(a,b,x,y);
	if(c%gcd)
	{
		puts("0");
		return 0;
	}	
	a/=gcd;
	b/=gcd;
	c/=gcd;
	x*=c;
	y*=c;	
	ll X1=((x1-x)/a*a+x)>=x1?(x1-x)/a*a+x:(x1-x)/a*a+x+abs(a);
	ll X2=((x2-x)/a*a+x)<=x2?(x2-x)/a*a+x:(x2-x)/a*a+x-abs(a);
	ll Y1=((y1-y)/b*b+y)>=y1?(y1-y)/b*b+y:(y1-y)/b*b+y+abs(b);
	ll Y2=((y2-y)/b*b+y)<=y2?(y2-y)/b*b+y:(y2-y)/b*b+y-abs(b);
	ll X1_=(c-b*Y2)/a;
    ll X2_=(c-b*Y1)/a;
    ll ansl,ansr;
    if(a*b>0)
    {
		ansl=max(X1,X1_);
		ansr=min(X2,X2_);
	}
	else
	{
		ansl=min(X1,X1_);
		ansr=max(X2,X2_);	
	}
	printf("%lld\n",abs(ansr-ansl)/abs(b)+1);
}

