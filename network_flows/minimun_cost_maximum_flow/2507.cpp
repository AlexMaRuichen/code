#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=20*20;
const int maxm=maxn*20;
const int inf=1e9;

int to[maxm];
int next[maxm];
int len[maxm];
int cost[maxm];
int from[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z,int c)
{
	to[++tot]=y;
	next[tot]=head[x];
	len[tot]=z;
	cost[tot]=c;
	from[tot]=x;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	cost[tot]=-c;
	from[tot]=y;
	head[y]=tot;
}

int f[maxn];
int S=maxn-1,T=maxn-2;
bool v[maxn];
queue <int> q;
int pre[maxn];
bool spfa()
{
	for(int i=1;i<maxn;i++)
		f[i]=inf;
	f[S]=0;
	v[S]=true;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&f[to[i]]>f[x]+cost[i])
			{
				f[to[i]]=f[x]+cost[i];
				pre[to[i]]=i;
				if(!v[to[i]])
					v[to[i]]=true,q.push(to[i]);
			}
		v[x]=false;
	}
	return f[T]^inf;
}
int augment()
{
	int w=inf,ans=0;
	for(int i=pre[T];i;i=pre[from[i]])
		w=min(w,len[i]);
	for(int i=pre[T];i;i=pre[from[i]])
		len[i]-=w,len[i^1]+=w,ans+=cost[i]*w;
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}

int a,b,P,Q;
int cnt;
int id[20][20];
int main()
{
	scanf("%d%d%d%d",&a,&b,&P,&Q);
	for(int i=0;i<=P;i++)
		for(int j=0;j<=Q;j++)
			assign(id[i][j]);
	
	for(int i=0;i<=P;i++)
		for(int j=0;j<Q;j++)
		{
			static int x;
			scanf("%d",&x);
			add(id[i][j],id[i][j+1],1,-x);
			add(id[i][j],id[i][j+1],inf,0);
		}

	for(int j=0;j<=Q;j++)
		for(int i=0;i<P;i++)
		{
			static int x;
			scanf("%d",&x);
			add(id[i][j],id[i+1][j],1,-x);
			add(id[i][j],id[i+1][j],inf,0);
		}
	for(int i=1;i<=a;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(S,id[y][z],x,0);
	}
	for(int i=1;i<=b;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(id[y][z],T,x,0);
	}
	
	printf("%d\n",-MCMF());
}
