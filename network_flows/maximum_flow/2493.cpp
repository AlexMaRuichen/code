#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>
#define in(i) ((i<<1)-1)
#define out(i) (i<<1)
using namespace std;
const int maxn=1010;
const int maxm=100005;
const int inf=1e9;

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

queue <int> q;
int dep[maxn];
int S,T;
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
		ans+=dfs(S,inf);
	return ans;
}
int f[maxn];
int a[maxn];
int n;
int ans;
void init()
{
	memset(head,0,sizeof(head));
	tot=1;
}
int main()
{
	scanf("%d",&n);
	S=0,T=1005;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		int t=0;
		for(int j=1;j<i;j++)
			if(a[j]<=a[i])
				t=max(t,f[j]);
		f[i]=t+1;
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		add(in(i),out(i),1);
		if(f[i]==1)
			add(S,in(i),1);
		if(f[i]==ans)
			add(out(i),T,1);
		for(int j=1;j<i;j++)
			if(a[j]<=a[i]&&f[i]==f[j]+1)
				add(out(j),in(i),1);
	}
	printf("%d\n",dinic());
	init();
	for(int i=1;i<=n;i++)
		if(i==1||i==n)
		{
			add(in(i),out(i),inf);
			if(f[i]==1)
				add(S,in(i),inf);
			if(f[i]==ans)
				add(out(i),T,inf);
			for(int j=1;j<i;j++)
				if(a[j]<=a[i]&&f[i]==f[j]+1)
					add(out(j),in(i),1);
		}
		else
		{
			add(in(i),out(i),1);
			if(f[i]==1)
				add(S,in(i),1);
			if(f[i]==ans)
				add(out(i),T,1);
			for(int j=1;j<i;j++)
				if(a[j]<=a[i]&&f[i]==f[j]+1)
					add(out(j),in(i),1);
		}
	int t=dinic();
	printf("%d\n",t>=inf?n:t);
}
