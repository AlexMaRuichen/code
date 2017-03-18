#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=110;
const int maxm=maxn*20;
const int inf=1e9;

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
int pre[maxn];
queue <int> q;
bool spfa()
{
	for(int i=1;i<maxn;i++)
		f[i]=inf;
	q.push(S);
	v[S]=true;
	f[S]=0;
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

int n;
int a[maxn];
int ave;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),add(S,i,a[i],0),ave+=a[i];
	for(int i=1;i<n;i++)
		add(i,i+1,inf,1);
	for(int i=2;i<=n;i++)
		add(i,i-1,inf,1);
	add(1,n,inf,1);
	add(n,1,inf,1);
	ave/=n;
	for(int i=1;i<=n;i++)
		add(i,T,ave,0);
	printf("%d\n",MCMF());
}
