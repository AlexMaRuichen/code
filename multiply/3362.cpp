#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int log=20;
int fa[log+1][maxn];
int dis[maxn];
int depth[maxn];

int to[maxn<<1];
int next[maxn<<1];
int len[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y,int z)
{
	to[++tot]=y;
	len[tot]=z;
	next[tot]=head[x];
	head[x]=tot;

	to[++tot]=x;
	len[tot]=z;
	next[tot]=head[y];
	head[y]=tot;
}

void dfs(int x)
{
	depth[x]=depth[fa[0][x]]+1;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa[0][x])
		{
			fa[0][to[i]]=x;
			dis[to[i]]=dis[x]+len[i];
			dfs(to[i]);
		}
}
int ans;
int getfa(int x,int y)
{
	for(int i=0;i<=log;i++)
		if((1<<i)&y)
			x=fa[i][x];
	return x;
}
int lca(int x,int y)
{
	if(depth[x]<depth[y])
		swap(x,y);
	x=getfa(x,depth[x]-depth[y]);
	if(x==y)
		return x; 
	for(int i=log;i>=0;i--)
		if(fa[i][x]!=fa[i][y])
		{
			x=fa[i][x];
			y=fa[i][y];
		}
	return fa[0][x];
}
int n,m;
int k;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d%*s",&x,&y,&z);
		add(x,y,z);
	}
	dfs(1);
	scanf("%d",&k);
	while(k--)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",dis[x]+dis[y]-2*dis[lca(x,y)]);
	}
}
