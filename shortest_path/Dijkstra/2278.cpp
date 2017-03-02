#include <stdio.h>
#include <algorithm>
#include <utility>
#include <string.h>
using namespace std;
const int maxn=110;
int f[maxn];
bool v[maxn];
int pre[maxn];
int fpre[maxn];
int map[maxn][maxn];
int n,m;
void dijkstra()
{
	memset(f,0x3f,sizeof(f));
	memset(v,0,sizeof(v));
	f[1]=0;
	for(int i=1;i<=n;i++)
	{
		int x=-1;
		for(int j=1;j<=n;j++)
			if(!v[j]&&(x==-1||f[j]<f[x]))
				x=j;
		v[x]=true;
		for(int j=1;j<=n;j++)
			if(f[j]>f[x]+map[x][j])
				f[j]=f[x]+map[x][j],pre[j]=x;
	}
}
int ans;
int main()
{
	memset(map,0x3f,sizeof(map));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		scanf("%d",&map[x][y]);
		map[y][x]=map[x][y];
	}
	dijkstra();
	int plen=f[n];
	memcpy(fpre,pre,sizeof(pre));
	for(int i=n;fpre[i];i=fpre[i])
	{
		map[i][fpre[i]]*=2;
		map[fpre[i]][i]*=2;
		dijkstra();
		ans=max(ans,f[n]-plen);
		map[i][fpre[i]]/=2;
		map[fpre[i]][i]/=2;
	}
	printf("%d\n",ans);
}
