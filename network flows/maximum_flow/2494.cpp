#include <stdio.h>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1100;
const int maxm=maxn*20;

int to[maxm];
int next[maxm];
int len[maxm];
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

int S,T=1090;
int dep[maxn];
queue <int> q;
bool bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&dep[to[i]]==-1)
				dep[to[i]]=dep[x]+1,q.push(to[i]);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
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
	if(used^f)
		dep[x]=-1;
	return used;
}
int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,~0u>>1);
	return ans;
}
int n,m,k;
int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=k;i++)
	{
		static int x;
		scanf("%d",&x);
		m+=x;
		add(n+i,T,x);
	}
	for(int i=1;i<=n;i++)
	{
		static int p,x;
		scanf("%d",&p);
		add(S,i,1);
		while(p--)
		{
			scanf("%d",&x);
			add(i,n+x,1);
		}
	}
	if(dinic()^m)
		puts("No Solution!");
	else
		for(int x=1;x<=k;x++,puts(""))
		{
			printf("%d:",x);
			for(int i=head[x+n];i;i=next[i])
				if(!len[i^1]&&to[i]!=T)
					printf(" %d",to[i]);
		}
}
