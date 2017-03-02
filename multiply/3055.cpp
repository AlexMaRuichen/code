#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int log=18;
int n,k;
int fa[log+1][maxn];
int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;

	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}
int depth[maxn];
void dfs(int x)
{
	depth[x]=depth[fa[0][x]]+1;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa[0][x])
			dfs(to[i]);
}
bool deg[maxn];
int root;
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
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		fa[0][y]=x;
		add(x,y);
		deg[y]=true;
	}
	for(int i=1;i<=n;i++)
		if(!deg[i])
		{
			root=i;
			break;
		}
	dfs(root);
	while(k--)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
}
