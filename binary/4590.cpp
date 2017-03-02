#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
int l,k,x[maxn];
ll sum;
ll ansmin,ansmax;
int check(ll h)
{
	ll tmp=0,ans=0;
	for(int i=1;i<=l;i++)
	{
		tmp=max(tmp+x[i],0ll);    
		if(tmp>=h)
			tmp=0,ans++;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&l,&k);
	for(int i=1;i<=l;i++)
	{
		scanf("%d",&x[i]);
		sum+=x[i];
	}
	ll L=0,R=sum;
	ll mid;
	ll l=0,r=1ll<<50;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)>k)
			L=mid,l=mid+1;
		else
			r=mid-1;
	}
	l=0,r=1ll<<50;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)>=k)
			l=mid+1;
		else
			R=mid,r=mid-1;
	}
	L++,R--;
	if(check(L)!=k||check(R)!=k)
	{
		puts("-1");
		return 0;
	}
	printf("%lld %lld\n",L,R);
}
