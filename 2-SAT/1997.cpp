#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stack>
#define in(i) (i<<1)
#define out(i) (i<<1|1)
#define inv(i) (i&1?i^1:i|1)
using namespace std;
const int maxn=1210;
const int maxm=maxn*maxn;
int n,m;

int to[maxm];
int next[maxm];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}

int belong[maxn];
int dfn[maxn];
int low[maxn];
bool v[maxn];
bool ins[maxn];
stack <int> s;
int cnt;
int scc;
void dfs(int x)
{
	dfn[x]=low[x]=++cnt;
	v[x]=ins[x]=true;
	s.push(x);
	for(int i=head[x];i;i=next[i])
		if(!v[to[i]])
			dfs(to[i]),
			low[x]=min(low[to[i]],low[x]);
		else if(ins[to[i]])
			low[x]=min(dfn[to[i]],low[x]);
	if(dfn[x]==low[x])
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
	for(int i=1;i<=m;i++)
	{
		if(!v[in(i)])
			dfs(in(i));
		if(!v[out(i)])
			dfs(out(i));
	}
}

void init()
{
	memset(head,0,sizeof(head));
	memset(v,0,sizeof(v));
	tot=0;
	cnt=0;
	scc=0;
}
int x[maxn<<2];
int y[maxn<<2];
int pos[maxn];
int c[maxn];
void build()
{
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			if((x[j]<x[i]&&y[j]>x[i]&&y[j]<y[i])||(x[j]>x[i]&&x[j]<y[i]&&y[j]>y[i]))
				add(in(i),out(j)),add(in(j),out(i)),add(out(j),in(i)),add(out(i),in(j));
}
bool check()
{
	for(int i=1;i<=m;i++)
		if(belong[in(i)]==belong[out(i)])
			return false;
	return true;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(m>n*3-6)
		{
			for(int i=1;i<=m;i++)
				scanf("%*d%*d");
			for(int i=1;i<=n;i++)
				scanf("%*d");
			puts("NO");
			continue;
		}
		init();
		for(int i=1;i<=m;i++)
			scanf("%d%d",&x[i],&y[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&c[i]),pos[c[i]]=i;	
		for(int i=1;i<=m;i++)
		{
			x[i]=pos[x[i]];
			y[i]=pos[y[i]];
			if(x[i]>y[i])
				swap(x[i],y[i]);
		}
		build();
		tarjan();
		if(check())
			puts("YES");
		else
			puts("NO");
	}
}
