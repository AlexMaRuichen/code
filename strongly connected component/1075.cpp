#include <stdio.h>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e6+10;
int n,m,mod;
int ans;

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
int digree[maxn];
void add_(int x,int y)
{
	to_[++tot_]=y;
	next_[tot_]=head_[x];
	head_[x]=tot_;
	digree[y]++;
}

typedef pair<int,int> point;
stack <int> s;
bool ins[maxn];
bool v[maxn];
int size[maxn];
int scc;
int low[maxn];
int dfn[maxn];
int cnt;
int belong[maxn];
void dfs(int x)
{
	s.push(x);
	ins[x]=v[x]=true;
	low[x]=dfn[x]=++cnt;
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
		++scc;
		int now=0;
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
	set <point> sets;
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=next[i])
			if(belong[x]!=belong[to[i]]&&(sets.insert(point(belong[x],belong[to[i]])).second))
				add_(belong[x],belong[to[i]]);
}
void tarjan()
{
	for(int i=1;i<=n;i++)
		if(!v[i])
			dfs(i);
	rebuild();
}

int f[maxn];
int g[maxn];
queue <int> q;
void topological_sort()
{
	for(int i=1;i<=scc;i++)
	{
		if(!digree[i])
			q.push(i);
		f[i]=size[i];
		g[i]=1;
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head_[x];i;i=next_[i])
		{
			--digree[to_[i]];
			if(!digree[to_[i]])
				q.push(to_[i]);
			if(f[x]+size[to_[i]]>f[to_[i]])
			{
				f[to_[i]]=f[x]+size[to_[i]];
				g[to_[i]]=g[x];
			}
			else if(f[x]+size[to_[i]]==f[to_[i]])
				g[to_[i]]=(g[to_[i]]+g[x])%mod;
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}

	tarjan();

	topological_sort();

	int M=0;
	for(int i=1;i<=scc;i++)
	{
		if(f[i]>M)
			M=f[i],ans=g[i];
		else if(f[i]==M)
			ans=(ans+g[i])%mod;
	}

	printf("%d\n%d\n",M,ans);
}
