#include <stdio.h>
typedef long long ll;
ll n,tmp;
ll prime[100];
int c[100];
int cnt;
ll ans;
ll phi;
int main()
{
	scanf("%lld",&tmp);
	n=tmp;
	register ll i;
	for(i=2;i*i<=n;i++)
		if(!(tmp%i))
		{
			prime[++cnt]=i;
			while(!(tmp%i))	
				tmp/=i,c[cnt]++;
		}
	if(tmp!=1)
	{
		prime[++cnt]=tmp;
		c[cnt]++;
	}
	phi=n;
	for(i=1;i<=cnt;i++)
	{
		phi/=prime[i];
		phi*=prime[i]-1;
	}
	for(i=1;i<=cnt;i++)
		if(c[i]==1)
			ans+=phi/(prime[i]-1);
		else
			ans+=phi/prime[i];
	printf("%lld\n",ans);
}
