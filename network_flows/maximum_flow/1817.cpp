#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=210;

int n,m;
int to[maxn<<1];
int next[maxn<<1];
int len[maxn<<1];
int head[maxn];
int tot=1;
void add(int x,int y,int z)
{
	to[++tot]=y;
	next[tot]=head[x];
	len[tot]=z;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	head[y]=tot;
}

queue <int> q;
int dep[maxn];
bool bfs(int S,int T)
{
	memset(dep,-1,sizeof(dep));
	q.push(S);
	dep[S]=1;	
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(dep[to[i]]==-1&&len[i])
				dep[to[i]]=dep[x]+1,q.push(to[i]);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==m)
		return f;
	int w,used=0;
	for(int i=head[x];i;i=next[i])
		if(len[i]&&dep[to[i]]==dep[x]+1)
		{
			w=dfs(to[i],min(len[i],f-used));
			len[i]-=w;
			len[i^1]+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used!=f)
		dep[x]=-1;
	return used;
}
int dinic()
{
	int ans=0;
	while(bfs(1,m))
		ans+=dfs(1,~0u>>1);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	printf("%d\n",dinic());
}
