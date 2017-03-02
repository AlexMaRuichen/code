#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
ll r,l,b;
ll a[maxn];
ll sum[maxn];
ll ans;
bool check(ll l,ll r)
{
	ll mid=(r+l+1)>>1;
	ll sum1=(mid-l)*a[mid]-(sum[mid]-sum[l]);
	ll sum2=sum[r]-sum[mid]-(r-mid)*a[mid];
	return sum1+sum2>b;
}
int main()
{
	scanf("%lld%lld%lld",&r,&l,&b);
	for(int i=1;i<=r;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(ll i=1,j=0;i<=r;i++)
	{
		while(check(j,i))
			j++;
		ans=max(ans,i-j);
	}
	printf("%lld\n",ans);	
}
