#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
const int maxn=210;
int map[maxn][maxn];
int n;
int K;
int m;
int q;
int ans;
int tmp;
long long sum;
int main()
{
	scanf("%d%d%d%d",&n,&m,&K,&q);
	memset(map,0x3f,sizeof(map));
	register int i,j,k;
	for(i=1;i<=m;++i)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		scanf("%d",&map[x][y]);
	}
	for(i=1;i<=n;++i)
		map[i][i]=0;
	for(k=1;k<=n;++k)
		for(i=1;i<=n;++i)
			for(j=1;j<=n;++j)
				map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
	for(i=1;i<=q;++i)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		tmp=~0u>>1;
		for(j=1;j<=K;++j)
			if(map[x][j]!=1061109567&&map[j][y]!=1061109567)
				tmp=min(tmp,map[x][j]+map[j][y]);
		if(tmp!=~0u>>1)
			++ans,sum+=tmp;
	}
	printf("%d\n%lld\n",ans,sum);
}
