#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=450;
const int maxm=maxn*maxn;

int to[maxm<<1];
int next[maxm<<1];
int len[maxm<<1];
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

int dep[maxn];
queue <int> q;
int S,T;
bool bfs()
{
	q.push(S);
	memset(dep,-1,sizeof(dep));
	dep[S]=1;
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
int n,m;
int cnt;
int main()
{
	scanf("%d%d",&n,&m);
	S=0,T=n+m+1;
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(S,i,x);
		cnt+=x;
	}
	for(int i=n+1;i<=n+m;i++)
	{
		static int x;
		scanf("%d",&x);
		add(i,T,x);
		for(int j=1;j<=n;j++)
			add(j,i,1);
	}
	if(dinic()==cnt)
	{
		puts("1");
		for(int x=1;x<=n;x++,puts(""))
		{
			bool flag=false;
			for(int i=head[x];i;i=next[i])
				if(!len[i])
				{
					if(!flag)
						printf("%d",to[i]-n),flag=true;
					else
						printf(" %d",to[i]-n);
				}
		}
	}
	else
		puts("0");
}
