#include <stdio.h>
#include <algorithm>
#include <string.h>
#define dis(x,y) ((x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second))
using namespace std;
int f[1010][1010];
int g[1010][1010];
int n,m;
typedef pair<int,int> point;
point H[1010];
point G[1010];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&H[i].first,&H[i].second);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&G[i].first,&G[i].second);
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	f[1][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
		{
			if(!(i==1&&j==0))
				f[i][j]=min(f[i-1][j]+dis(H[i-1],H[i]),g[i-1][j]+dis(G[j],H[i]));
			g[i][j]=min(f[i][j-1]+dis(H[i],G[j]),g[i][j-1]+dis(G[j-1],G[j]));
		}
	printf("%d\n",f[n][m]);
}
