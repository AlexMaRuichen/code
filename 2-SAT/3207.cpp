#include <stdio.h>
#include <algorithm>
#include <stack>
#define assign(x) x=++id
using namespace std;
const int maxn=1010<<1;
const int maxm=510*510<<2;

int to[maxm];
int next[maxm];
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

int n,m;
int x[maxn];
int y[maxn];
int low[maxn];
int dfn[maxn];
bool v[maxn];
bool ins[maxn];
int cnt;
int scc;
int belong[maxn];
stack <int> s;
int in[maxn];
int out[maxn];
int id;
void dfs(int x)
{
	v[x]=ins[x]=true;
	low[x]=dfn[x]=++cnt;
	s.push(x);
	for(int i=head[x];i;i=next[i])
		if(!v[to[i]])
			dfs(to[i]),low[x]=min(low[to[i]],low[x]);
		else if(ins[to[i]])
			low[x]=min(dfn[to[i]],low[x]);
	if(low[x]==dfn[x])
	{
		int now=0;
		++scc;
		while(now^x)
		{
			now=s.top();
			s.pop();
			ins[now]=false;
			belong[now]=scc;
		}
	}
}
void tarjan()
{
	for(int i=1;i<=id;i++)
		if(!v[i])
			dfs(i);
}

bool check()
{
	for(int i=1;i<=m;i++)
		if(belong[in[i]]==belong[out[i]])
			return false;
	return true;
}

void build()
{
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			if((x[j]>x[i]&&x[j]<y[i]&&y[j]>y[i])||(x[j]<x[i]&&y[j]>x[i]&&y[j]<y[i]))
				add(in[i],out[j]),add(in[j],out[i]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		assign(in[i]),assign(out[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		if(x[i]>y[i])
			swap(x[i],y[i]);
	}
	build();
	tarjan();
	if(check())
		puts("panda is telling the truth...");
	else
		puts("the evil panda is lying again");
}
