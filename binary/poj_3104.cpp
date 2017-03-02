#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
long long n,k;
long long a[100010];
long long mr;
long long f;
bool check(long long x)
{
	long long ans=0;
	for(int i=1;i<=n;i++)
		if(a[i]>x)
			ans+=ceil((a[i]-x)*1.0/(k-1));
	return ans<=x;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		mr=mr>a[i]?mr:a[i];
	}
	scanf("%lld",&k);
	if(k==1)
	{
		printf("%lld\n",mr);
		return 0;
	}
	long long l=0;
	long long r=mr;
	while(l<r)
	{
		long long mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%lld\n",r);
}
