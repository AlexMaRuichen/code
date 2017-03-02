#include <stdio.h>
#include <stack>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=1e3+10;
const int maxm=6e3+10;
int T;
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

int to_[maxm];
int next_[maxm];
int head_[maxn];
int tot_;
int in[maxn];
int out[maxn];
void add_(int x,int y)
{
	to_[++tot_]=y;
	next_[tot_]=head_[x];
	head_[x]=tot;
	++in[y];
	++out[x];
}

stack <int> s;
int low[maxn];
int dfn[maxn];
int cnt;
bool v[maxn];
bool ins[maxn];
int scc;
int size[maxn];
int belong[maxn];
void dfs(int x)
{
	low[x]=dfn[x]=++cnt;
	ins[x]=v[x]=true;
	s.push(x);
	for(int i=head[x];i;i=next[i])
		if(!v[to[i]])
		{
			dfs(to[i]);
			low[x]=min(low[x],low[to[i]]);
		}
		else if(ins[to[i]])
			low[x]=min(low[x],dfn[to[i]]);
	if(dfn[x]==low[x])
	{
		int now=0;
		++scc;
		while(now!=x)
		{
			now=s.top();
			s.pop();
			ins[now]=false;
			belong[now]=scc;
			++size[scc];
		}
	}
}
void rebuild()
{
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=next[i])
			if(belong[x]!=belong[to[i]])
				add_(belong[x],belong[to[i]]);
}
void tarjan()
{
	for(int i=1;i<=n;i++)
		if(!v[i])
			dfs(i);
	rebuild();
}

queue <int> q;
int f[maxn];
void process()
{
	int ans1,ans2;
	ans1=ans2=0;
	for(int i=1;i<=scc;i++)
	{
		if(in[i]==0)
			++ans1;
		if(out[i]==0)
			++ans2;
	}
	if(ans1==1&&ans2==1)
		puts("Yes");
	else
		puts("No");
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scc=0;
		tot=0;
		tot_=0;
		memset(head,0,sizeof(int)*(n+10));
		memset(head_,0,sizeof(int)*(n+10));
		memset(v,0,sizeof(int)*(n+10));
		memset(in,0,sizeof(int)*(n+10));
		memset(out,0,sizeof(int)*(n+10));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}

		tarjan();

		process();
	}
}
