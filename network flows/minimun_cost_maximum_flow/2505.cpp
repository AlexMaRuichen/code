#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=110;
const int maxm=maxn*maxn*10;
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

queue <int> q;
int f[maxn];
bool v[maxn];
int pre[maxn];
int S=maxn-1,T=maxn-2;
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
		len[i]-=f,len[i^1]+=f,ans+=f*cost[i];
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
	tot=1;
	memset(head,0,sizeof(head));
}
int n;
int map[maxn][maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n<<1;j++)
			scanf("%d",&map[i][j]);
	
	for(int i=1;i<=n;i++)
		add(S,i,1,0);
	for(int i=n+1;i<=n<<1;i++)
		add(i,T,1,0);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n<<1;j++)
			add(i,j,1,map[i][j]);
	printf("%d\n",MCMF());
	
	init();
	for(int i=1;i<=n;i++)
		add(S,i,1,0);
	for(int i=n+1;i<=n<<1;i++)
		add(i,T,1,0);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n<<1;j++)
			add(i,j,1,-map[i][j]);
	printf("%d\n",-MCMF());

}
