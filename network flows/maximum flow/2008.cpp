#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
queue <int> q;
const int maxn=110;
int to[maxn*maxn];
int next[maxn*maxn];
int len[maxn*maxn];
int tot=1;
int head[maxn];
int depth[maxn];
int fa[maxn];
int n,m;
int ans;
int S,T;
void add(int x,int y,int z)
{
	to[++tot]=y;
	len[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	len[tot]=0;
	next[tot]=head[y];
	head[y]=tot;
}
bool bfs()
{
	int c;
	memset(depth,-1,sizeof(depth));
	q.push(0);
	depth[0]=0;
	while(!q.empty())
	{
		c=q.front();
		q.pop();
		for(int i=head[c];i;i=next[i])
			if(len[i]&&depth[to[i]]<0)
				q.push(to[i]),depth[to[i]]=depth[c]+1;
	}
	return depth[n+1]!=-1;
}
int dfs(int x,int f)
{
	if(x==n+1)
		return f;
	int used=0,w;
	for(int i=head[x];i;i=next[i])
		if(len[i]&&depth[to[i]]==depth[x]+1)	
		{
			w=dfs(to[i],min(f-used,len[i]));
			if(w)
				fa[x]=to[i];
			len[i]-=w;
			len[i^1]+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used!=f)
		depth[x]=-1;
	return used;
}
void dinic()
{
	while(bfs())
		ans+=dfs(0,~0u>>2);
}
int main()
{
	scanf("%d%d",&m,&n);
	int x,y;
	S=0;
	T=n+1;
	while(scanf("%d%d",&x,&y)&&x!=-1)
		add(x,y,1);
	for(int i=1;i<=m;i++)
		add(S,i,1);
	for(int i=m+1;i<=n;i++)
		add(i,T,1);
	dinic();
	if(ans)
	{
		printf("%d\n",ans);
		for(int i=1;i<=m;i++)
			if(fa[i])
				printf("%d %d\n",i,fa[i]);
	}
	else
		puts("No Solution!");
}
