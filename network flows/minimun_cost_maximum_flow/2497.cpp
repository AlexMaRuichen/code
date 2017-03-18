#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=2010;
const int maxm=1000001;
int N,p,m,F,n,s,S,T=2005;
int ans;

int to[maxm];
int next[maxm];
int len[maxm];
int cost[maxm];
int head[maxn];
int from[maxm];
int tot=1;
void add(int x,int y,int z,int a)
{
	to[++tot]=y;
	from[tot]=x;
	len[tot]=z;
	cost[tot]=a;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	from[tot]=y;
	len[tot]=0;
	cost[tot]=-a;
	next[tot]=head[y];
	head[y]=tot;
}

int f[maxn];
queue <int> q;
bool v[maxn];
int pre[maxn];
bool spfa()
{
	for(int i=0;i<=T;i++)
		f[i]=~0u>>2;
	q.push(S);
	f[S]=0;
	v[S]=true;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
		{
			if(len[i]&&f[to[i]]>f[x]+cost[i])
			{
				f[to[i]]=f[x]+cost[i];
				pre[to[i]]=i;
				if(!v[to[i]])
					v[to[i]]=true,q.push(to[i]);
			}
		}
		v[x]=false;
	}
	return f[T]!=~0u>>2;
}
void mcf()
{
	int i,x=~0u>>1;
	i=pre[T];
	while(i)
	{
		x=min(len[i],x);
		i=pre[from[i]];
	}
	i=pre[T];
	while(i)
	{
		len[i]-=x;
		len[i^1]+=x;
		ans+=x*cost[i];
		i=pre[from[i]];
	}
}

int main()
{
	scanf("%d%d%d%d%d%d",&N,&p,&m,&F,&n,&s);
	for(int i=1;i<=N;i++)
	{
		if(i+1<=N)
			add(i,i+1,~0u>>2,0);
		if(i+m<=N)
			add(i,i+m+N,~0u>>2,F);
		if(i+n<=N)
			add(i,i+n+N,~0u>>2,s);
		add(S,N+i,~0u>>2,p);
	}
	for(int i=1;i<=N;i++)
	{
		static int x;
		scanf("%d",&x);
		add(0,i,x,0);
		add(N+i,T,x,0);
	}
	while(spfa())
		mcf();
	printf("%d\n",ans);
}
