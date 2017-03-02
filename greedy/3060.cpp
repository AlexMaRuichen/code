#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=5e4+10;
class DiamondCollector
{
	int n,k;
	int a[maxn];
	int res;
	int ans[maxn];
public:
	int solve()
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int j=1;
		for(int i=1;i<=n;i++)
		{
			while(a[j]-a[i]<=k&&j<=n)
				++j;
			ans[i]=j-i;
		}
		for(int i=n;i;i--)
		{
			res=max(res,ans[i]+ans[i+ans[i]]);
			ans[i]=max(ans[i],ans[i+1]);
		}

		return res;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
