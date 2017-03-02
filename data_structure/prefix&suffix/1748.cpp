#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2e5+10;
typedef long long ll;
ll s,t;
int n,m;
int w[maxn];
int v[maxn];
int l[maxn];
int r[maxn];
int L,R,mid;
ll sum[maxn],cnt[maxn];
ll ans=1ll<<60;
int main()
{
	scanf("%d%d%lld",&n,&m,&s);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&w[i],&v[i]),R=max(R,w[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&l[i],&r[i]);
	++R;
	while(L<=R)
	{
		t=0;
		mid=(L+R)>>1;
		sum[0]=cnt[0]=0;
		for(int i=1;i<=n;i++)
		{
			sum[i]=sum[i-1];
			cnt[i]=cnt[i-1];
			if(w[i]>=mid)
				sum[i]+=v[i],++cnt[i];
		}
		for(int i=1;i<=m;i++)
		{
			t+=(sum[r[i]]-sum[l[i]-1])*(cnt[r[i]]-cnt[l[i]-1]);
			if(t>=s<<1)
				break;
		}
		ans=min(abs(t-s),ans);
		if(t>=s)
			L=mid+1;
		else
			R=mid-1;
	}
	printf("%lld\n",ans);
}
