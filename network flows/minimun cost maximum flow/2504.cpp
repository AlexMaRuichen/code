#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=120;
const int maxm=maxn*maxn*4;
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
	from[tot]=x;
	len[tot]=z;
	cost[tot]=c;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	from[tot]=y;
	cost[tot]=-c;
	head[y]=tot;
}

queue <int> q;
bool v[maxn];
int f[maxn];
int pre[maxn];
int S=119,T=118;
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
	int f=inf,ans=0;
	for(int i=pre[T];i;i=pre[from[i]])
		f=min(f,len[i]);
	for(int i=pre[T];i;i=pre[from[i]])
		len[i]-=f,len[i^1]+=f,ans+=cost[i]*f;
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}

void init()
{
	memset(head,0,sizeof(head));
	tot=1;
}

int n,m;
int a[maxn];
int c[maxn][maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)	
		for(int j=n+1;j<=n+m;j++)
			scanf("%d",&c[i][j]);
			
	for(int i=1;i<=n;i++)
		add(S,i,a[i],0);
	for(int i=n+1;i<=n+m;i++)
		add(i,T,a[i],0);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n+m;j++)
			add(i,j,inf,c[i][j]);
	printf("%d\n",MCMF());
	
	init();
	for(int i=1;i<=n;i++)
		add(S,i,a[i],0);
	for(int i=n+1;i<=n+m;i++)
		add(i,T,a[i],0);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n+m;j++)
			add(i,j,inf,-c[i][j]);
	printf("%d\n",-MCMF());

}
