#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;
map <pair<int,int>,ll> m;
vector <int> v;
ll n,g;
const int M=999911659;
ll ans;
ll a[10];
void init()
{
	m[make_pair(2,0)]=1;
	m[make_pair(3,0)]=1;
	m[make_pair(4679,0)]=1;
	m[make_pair(35617,0)]=1;
	int i;
	for(i=1;i<=2;i++)
		m[make_pair(2,i)]=(m[make_pair(2,i-1)]*i)%2;
	for(i=1;i<=3;i++)
		m[make_pair(3,i)]=(m[make_pair(3,i-1)]*i)%3;
	for(i=1;i<=4679;i++)
		m[make_pair(4679,i)]=(m[make_pair(4679,i-1)]*i)%4679;
	for(i=1;i<=35617;i++)
		m[make_pair(35617,i)]=(m[make_pair(35617,i-1)]*i)%35617;
}
ll mul(ll x,ll y,int mod)
{
	ll a=1;
	while(y)
	{
		if(y&1)
			a=(a*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return a;
}
ll c(int n,int k,int mod)
{
	if(n<k)
		return 0;
	return m[make_pair(mod,n)]*mul(m[make_pair(mod,k)]*m[make_pair(mod,n-k)],mod-2,mod)%mod;
}
ll lucas(int n,int m,int mod)
{
	if(m==0)
		return 1;
	if(n<mod&&m<mod)
		return c(n,m,mod);
	return lucas(n/mod,m/mod,mod)*c(n%mod,m%mod,mod)%mod;
}
void crt(int k)
{
	a[1]=(a[1]+lucas(n,k,2))%2;
	a[2]=(a[2]+lucas(n,k,3))%3;
	a[3]=(a[3]+lucas(n,k,4679))%4679;
	a[4]=(a[4]+lucas(n,k,35617))%35617;
}
void ex_gcd(ll a,ll b,ll &x,ll&y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	ex_gcd(b,a%b,x,y);
	ll tmp=x;
	x=y;
	y=tmp-(a/b)*y;
	return;
}
void solve()
{
	ll m=M-1;
	ll x,y;
	ex_gcd(m/2,2,x,y);
	ans=(ans+m/2*x*a[1])%m;
	ex_gcd(m/3,3,x,y);
	ans=(ans+m/3*x*a[2])%m;
	ex_gcd(m/4679,4679,x,y);
	ans=(ans+m/4679*x*a[3])%m;
	ex_gcd(m/35617,35617,x,y);
	ans=(ans+m/35617*x*a[4])%m;  
	if(ans<0)
		ans+=m;
}
int main()
{
	init();
	scanf("%lld%lld",&n,&g);
	if(g==M)
	{
		puts("0");
		return 0;
	}
	for(long long i=1;i*i<=n;i++)
	{
		if(n%i==0)
		{
			crt(i);
			if(i*i!=n)
				crt(n/i);
		}
	}
	solve();
	printf("%lld\n",mul(g,ans,M)%M);
}
