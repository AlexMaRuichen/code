#include <stdio.h>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int maxn=2e5+10;
const int mod=10007;
int n;
int w[maxn];

int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}

int fa[maxn];

int mx[maxn];
int sum[maxn];
int f[maxn];
long long ans;
int maxans;
int mxs[maxn];
int sums[maxn];

void dfs(int x,int fa)
{
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa)
		{
			dfs(to[i],x);
			mx[x]=max(mx[x],w[to[i]]);
			sum[x]=(sum[x]+w[to[i]])%mod;
			mxs[x]=max(mxs[x],w[x]*mx[to[i]]);
			mxs[x]=max(mxs[x],mxs[to[i]]);
			sums[x]=(sums[x]+w[x]*sum[to[i]])%mod;
			sums[x]=(sums[x]+sums[to[i]])%mod;
		}
	int t1=0,t2=0;
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa)
		{
			mxs[x]=max(mxs[x],t1*w[to[i]]);
			sums[x]=(sums[x]+t2*w[to[i]])%mod;
			t1=max(t1,w[to[i]]);
			t2=(t2+w[to[i]])%mod;
		}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	dfs(1,1);
	printf("%d %d",mxs[1],(sums[1]<<1)%mod);
}
