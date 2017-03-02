#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
const int maxn=1e3+10;
const int maxm=1e4+10;
stack <int> st;
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
int cnt;
int scc;
int belong[maxn];
int ans;
int n,m;
int dfn[maxn];
int low[maxn];
int size[maxn];
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
	v[x]=true;
	ins[x]=true;
	st.push(x);
	dfn[x]=low[x]=++cnt;
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
				add_(belong[x],belong[to[i]]);
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
		if(size[i]>1)
			++ans;
	printf("%d\n",ans);
	ans=0;
	for(int i=1;i<=scc;i++)
		if(!head_[i]&&size[i]>1)
		{
			if(!ans)
				ans=i;
			else
			{
				puts("-1");
				return;
			}
		}
	if(ans)
	{
		for(int i=1;i<=n;i++)
			if(belong[i]==ans)
				printf("%d ",i);
		puts("");
	}
	else
		puts("-1");
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
}
