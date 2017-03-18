#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
long long n;
long long ans=1;
long long cnt;
long long t;
int main()
{
	scanf("%lld",&n);
	t=n;
	for(long long i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			cnt=0;
			while(n%i==0)
				n/=i,cnt++;
			if(cnt%2)
				ans*=i;
		}
	}
	if(n!=1)
		ans*=n;
	printf("%lld\n",ans+t+2*(long long)(sqrt(ans*t)));
}
