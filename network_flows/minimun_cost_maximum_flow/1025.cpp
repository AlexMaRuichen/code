#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=110;
const int maxm=maxn*maxn*20;
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
bool v[maxn];
queue <int> q;
int pre[maxn];
int S=maxn-1,T=maxn-2;
bool spfa()
{
	for(int i=1;i<maxn;i++)
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
	int w=inf,ans=0;
	for(int i=pre[T];i;i=pre[from[i]])
		w=min(w,len[i]);
	for(int i=pre[T];i;i=pre[from[i]])
		len[i]-=w,len[i^1]+=w,ans+=w*cost[i];
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}

int k;
int map[maxn][maxn];
int a[maxn];
int b[maxn];
int main()
{
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			scanf("%d",&map[i][j]),add(i,j,inf,map[i][j]);
	scanf("%d",&a[0]);
	for(int i=1;i<=a[0];i++)
		scanf("%d",&a[i]);
	scanf("%d",&b[0]);
	for(int i=1;i<=b[0];i++)
		scanf("%d",&b[i]);
		
	for(int i=1;i<=a[0];i++)
		add(S,a[i],1,0);
	for(int i=1;i<=b[0];i++)
		add(b[i],T,1,0);
		
	printf("%d\n",MCMF());
}
