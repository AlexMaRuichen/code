#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>
#define assign(x) x=++cnt
using namespace std;
const int maxn=1000;
const int maxm=maxn*20;
const int inf=1e9;

int n,m;
int cnt;

int to[maxm];
int next[maxm];
int len[maxm];
int from[maxm];
int cost[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z,int c)
{
	to[++tot]=y;
	from[tot]=x;
	len[tot]=z;
	cost[tot]=c;
	next[tot]=head[x];
	head[x]=tot;
	
	to[++tot]=x;
	from[tot]=y;
	len[tot]=0;
	cost[tot]=-c;
	next[tot]=head[y];
	head[y]=tot;
}

int f[maxn];
queue <int> q;
bool v[maxn];
int pre[maxn];
int S,T;
void init()
{
	memset(head,0,sizeof(head));
	tot=1;
}
bool spfa()
{
	for(int i=1;i<=cnt;i++)
		f[i]=inf;
	v[S]=true;
	f[S]=0;
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
		f=min(len[i],f);
	for(int i=pre[T];i;i=pre[from[i]])
		len[i]-=f,len[i^1]+=f,ans+=f*cost[i];
	return ans;
}
int maximum_cost_flow()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return -ans;
}

int map[30][50];
int in[30][50];
int out[30][50];
int main()
{
	scanf("%d%d",&n,&m);
	assign(S);
	assign(T);
	for(int i=1;i<=m;i++)
		for(int j=1;j<i+n;j++)
			assign(in[i][j]),assign(out[i][j]),scanf("%d",&map[i][j]);

	for(int i=1;i<=m;i++)
		for(int j=1;j<i+n;j++)
			add(in[i][j],out[i][j],1,-map[i][j]);
	for(int i=1;i<=n;i++)
		add(S,in[1][i],1,0);
	for(int i=1;i<n+m;i++)
		add(out[m][i],T,1,0);
	for(int i=1;i<m;i++)
		for(int j=1;j<i+n;j++)
			add(out[i][j],in[i+1][j],1,0),add(out[i][j],in[i+1][j+1],1,0);
	printf("%d\n",maximum_cost_flow());
	
	init();
	for(int i=1;i<=m;i++)
		for(int j=1;j<i+n;j++)
			add(in[i][j],out[i][j],inf,-map[i][j]);
	for(int i=1;i<=n;i++)
		add(S,in[1][i],1,0);
	for(int i=1;i<n+m;i++)
		add(out[m][i],T,inf,0);
	for(int i=1;i<m;i++)
		for(int j=1;j<i+n;j++)
			add(out[i][j],in[i+1][j],1,0),add(out[i][j],in[i+1][j+1],1,0);
	printf("%d\n",maximum_cost_flow());

	init();
	for(int i=1;i<=m;i++)
		for(int j=1;j<i+n;j++)
			add(in[i][j],out[i][j],inf,-map[i][j]);
	for(int i=1;i<=n;i++)
		add(S,in[1][i],1,0);
	for(int i=1;i<n+m;i++)
		add(out[m][i],T,inf,0);
	for(int i=1;i<m;i++)
		for(int j=1;j<i+n;j++)
			add(out[i][j],in[i+1][j],inf,0),add(out[i][j],in[i+1][j+1],inf,0);
	printf("%d\n",maximum_cost_flow());
}
