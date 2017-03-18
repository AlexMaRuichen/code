#include <stdio.h>
#include <algorithm>
using namespace std;
bool map[1010][1010];
int ans[1010][1010];
int n,m;
int maxans;
int main()
{
//	freopen("1239.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&map[i][j]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(map[i][j])
			{
				if(ans[i-1][j-1]&&ans[i][j-1]&&ans[i-1][j])
					ans[i][j]=min(ans[i-1][j-1],min(ans[i-1][j],ans[i][j-1]))+1;
				else
					ans[i][j]=1;
			}
			maxans=max(ans[i][j],maxans);
		}
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//			printf("%d ",ans[i][j]);
//		puts("");
//	}
	printf("%d\n",maxans);
}

