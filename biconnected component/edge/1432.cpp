#include <stdio.h>

#include <algorithm>
#include <stack>
using namespace std;
const int maxn=5010;
const int maxm=20010;
int n,m;

int to[maxm];
int nex[maxm];
int head[maxn];
int tot=1;
void add(int x,int y)
{
	to[++tot]=y;
	nex[tot]=head[x];
	head[x]=tot;

	to[++tot]=x;
	nex[tot]=head[y];
	head[y]=tot;
}
int deg[maxn];
int cnt;
int dfn[maxn];
int low[maxn];
int fa[maxn];
bool bridge[maxm];
int belong[maxn];
int ebc;
int ans;
stack <int> s;
bool ins[maxn];
void dfs(int x)
{
	dfn[x]=low[x]=++cnt;
	ins[x]=true;
	s.push(x);
	for(int i=head[x];i;i=nex[i])
		if(!dfn[to[i]])
		{
			fa[to[i]]=i,
			dfs(to[i]),
			low[x]=min(low[x],low[to[i]]);
			if(low[to[i]]>dfn[x])
				++ans,bridge[i]=true;
		}
		else if(i^fa[x]^1&&ins[to[i]])
			low[x]=min(low[x],dfn[to[i]]);
	if(low[x]==dfn[x])
	{
		int now=0;
		++ebc;
		while(now^x)
		{
			now=s.top();
			s.pop();
			ins[now]=false;
			belong[now]=ebc;
		}
	}
}
void rebuild()
{
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=nex[i])
			if(belong[to[i]]!=belong[x])
				++deg[belong[x]];
}
void tarjan()
{
	dfs(1);
	rebuild();
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	tarjan();
	printf("%d\n",ans);
	ans=0;
	for(int i=1;i<=ebc;i++)
		if(deg[i]==1)
			++ans;
	printf("%d\n",ans+1>>1);
}
