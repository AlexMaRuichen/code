#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=2500;
const int maxm=5000;
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
int S=maxn-1,T=maxn-2;
queue <int> Q;
int pre[maxn];
bool spfa()
{
	for(int i=1;i<maxn;i++)
		f[i]=inf;
	f[S]=0;
	v[S]=true;
	Q.push(S);
	while(!Q.empty())
	{
		int x=Q.front();
		Q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&f[to[i]]>f[x]+cost[i])
			{
				f[to[i]]=f[x]+cost[i];
				pre[to[i]]=i;
				if(!v[to[i]])
					v[to[i]]=true,Q.push(to[i]);
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

int n,p,q;
int cnt;
int in[40][40];
int out[40][40];
int main()
{
	scanf("%d%d%d",&n,&q,&p);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			assign(in[i][j]),assign(out[i][j]);
			
	add(S,in[1][1],n,0);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
		{
			static int x;
			scanf("%d",&x);
			if(x^1)
				add(in[i][j],out[i][j],inf,0);
			if(x==2)
				add(in[i][j],out[i][j],1,-1);
		}
	for(int i=1;i<=p;i++)
		for(int j=1;j<q;j++)
			add(out[i][j],in[i][j+1],inf,0);
	for(int i=1;i<p;i++)
		for(int j=1;j<=q;j++)
			add(out[i][j],in[i+1][j],inf,0);
	add(out[p][q],T,inf,0);

	printf("%d\n",-MCMF());
}
