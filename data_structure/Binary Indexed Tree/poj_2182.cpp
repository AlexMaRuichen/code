#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int ans[maxn];
int t[maxn];
int cnt;
int n;
void dfs(int x)
{
	ans[x]=++cnt;
	if(cnt==n)
		return;
	for(int i=n;i>x;i--)
		if(t[i])
		{
			t[i]--;
			if(!t[i])
				dfs(i);
		}
}
int main()
{	
	freopen("gen.out","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	register int i;
	for(i=2;i<=n;i++)
		scanf("%d",&t[i]);
	for(int i=n;i>=1;i--)
		if(!t[i])
		{
			dfs(i);
			if(cnt==n)
				break;
		}
	for(i=1;i<=n;i++)
		printf("%d\n",ans[i]);
}
