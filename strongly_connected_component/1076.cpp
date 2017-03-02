#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
const int maxn=1e4+10;
const int maxm=5e4+10;
stack <int> st;
int n,m;
int dfn[maxn];
int low[maxn];
int scc;
int head[maxn];
int head_[maxn];
int to[maxm];
int to_[maxm];
int next[maxm];
int next_[maxm];
int tot;
int tot_;
bool v[maxn];
bool ins[maxn];
int belong[maxn];
int size[maxn];
int cnt;
int ans;
int dig[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}
void add_(int x,int y)
{
	to_[++tot_]=y;
	next_[tot_]=head_[x];
	head_[x]=tot_;
}
void dfs(int x)
{
	v[x]=ins[x]=true;
	low[x]=dfn[x]=++cnt;
	st.push(x);
	for(int i=head[x];i;i=next[i])
		if(!v[to[i]])
		{
			dfs(to[i]);
			low[x]=min(low[x],low[to[i]]);
		}
		else if(ins[to[i]])
			low[x]=min(low[x],dfn[to[i]]);
	if(low[x]==dfn[x])
	{
		++scc;
		int now=0;
		while(now!=x)
		{
			now=st.top();
			st.pop();
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
				add_(belong[x],to[i]);
}
void tarjan()
{
	for(int i=1;i<=n;i++)
		if(!v[i])
			dfs(i);
	rebuild();
}
void process()
{
	for(int i=1;i<=scc;i++)
		if(!head_[i])
		{
			if(!ans)
				ans=size[i];
			else
			{
				ans=0;
				return;
			}
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}	
	tarjan();
	process();
	printf("%d\n",ans);
}
