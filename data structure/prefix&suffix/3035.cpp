#include <stdio.h>
#include <bitset>
#include <algorithm>
using namespace std;
const int maxn=50010;
class SubsequencesSummingToSevens
{
	int n;
	int mod[maxn];
	int last[7];
	bitset <7> v;
public:
	int solve()
	{
		int ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			static int x;
			scanf("%d",&x);
			mod[i]=(mod[i-1]+x)%7;
			if(!last[mod[i]])
				last[mod[i]]=i;
		}
		for(int i=n;i&&v.count()<7;i--)
			if(!v[mod[i]])
				ans=max(ans,i-last[mod[i]]),v[mod[i]]=true;
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
