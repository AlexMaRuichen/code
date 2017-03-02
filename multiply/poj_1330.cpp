#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e4+10;
const int log=14;
int T;
int fa[log+1][maxn];
int n;
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
int root;
bool deg[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		memset(deg,0,sizeof(deg));
		memset(fa,0,sizeof(fa));
		memset(head,0,sizeof(head));
		tot=0;
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
		int x,y;
		scanf("%d%d",&x,&y);
		if(depth[x]<depth[y])
			swap(x,y);
		for(int i=0;i<=log;i++)
			if((1<<i)&(depth[x]-depth[y]))
				x=fa[i][x];
		if(x==y)
		{
			printf("%d\n",x);
			continue;
		}
		for(int i=log;i>=0;i--)
			if(fa[i][x]!=fa[i][y])
				x=fa[i][x],y=fa[i][y];
		printf("%d\n",fa[0][x]);
	}
}
