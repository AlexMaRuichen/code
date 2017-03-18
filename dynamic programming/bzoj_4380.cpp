#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=60;
const int maxm=4e3+10;
int n,m;
int t[maxm];
int f[maxn][maxn][maxm];
int g[maxn][maxn][maxm];
int h[maxn][maxm];
int M[500010];
int num;
int inv[maxm];
int pre[maxn][maxn][maxm];
int l[maxm];
int r[maxm];
int w[maxm];
int ans[maxn];

void dfs(int l,int r,int k)
{
	if(l>r)
		return;
	int mid=f[l][r][k];
	int t=pre[l][r][k];
	ans[mid]=inv[t];
	dfs(l,mid-1,t);
	dfs(mid+1,r,t);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l[i],&r[i],&w[i]);
		t[++t[0]]=w[i];
	}
	sort(t+1,t+m+1);
	for(int i=1;i<=m;i++)
		if(t[i]!=t[i-1]||i==1)
			M[t[i]]=++num,inv[num]=t[i];
	for(int i=1;i<=m;i++)
		w[i]=M[w[i]];
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=1;k<=m;k++)
				g[i][j][k]=-0x3fffffff;
	for(int i=n;i>0;i--)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=1;k<=m;k++)
				for(int x=i;x<=j;x++)
					h[x][k]=0;
			for(int k=1;k<=m;k++)
				if(l[k]>=i&&r[k]<=j)
					for(int x=l[k];x<=r[k];x++)
						h[x][w[k]]++;
			for(int x=i;x<=j;x++)
				for(int k=m-1;k>0;k--)
					h[x][k]+=h[x][k+1];
			for(int x=i;x<=j;x++)
				for(int k=1;k<=m;k++)
					if(g[i][x-1][k]+g[x+1][j][k]+inv[k]*h[x][k]>g[i][j][k])
					{
						g[i][j][k]=g[i][x-1][k]+g[x+1][j][k]+inv[k]*h[x][k];
						f[i][j][k]=x,pre[i][j][k]=k;
					}
			for(int k=m;k>0;k--)
				if(g[i][j][k+1]>g[i][j][k])
				{
					g[i][j][k]=g[i][j][k+1];
					pre[i][j][k]=pre[i][j][k+1];
					f[i][j][k]=f[i][j][k+1];
				}
		}
	}
	dfs(1,n,1);
	printf("%d\n",g[1][n][1]);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
