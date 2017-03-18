#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
const int maxn=110;
const int maxm=110*110;
int n;

int head[maxn];
int head_[maxn];
int to[maxm];
int to_[maxm];
int next[maxm];
int next_[maxm];
int tot;
int tot_;
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

int dfn[maxn];
int size[maxn];
int low[maxn];
int cnt;
bool v[maxn];
bool ins[maxn];
int belong[maxn];
stack <int> s;
int scc;
void dfs(int x)
{
	v[x]=ins[x]=true;
	low[x]=dfn[x]=++cnt;
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

bool indig[maxn];
void process()
{
	if(scc==1)
	{
		printf("1\n0");
		return;
	}
	int ans=0;
	
	int cont=0;
	for(int x=1;x<=scc;x++)
		for(int i=head_[x];i;i=next_[i])
			indig[to_[i]]=true;
	for(int i=1;i<=scc;i++)
		if(!indig[i])
			++cont;
	printf("%d\n",cont);
		
	for(int i=1;i<=scc;i++)
		if(!head_[i])
			++ans;
	printf("%d\n",max(ans,cont));
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x;
		while(scanf("%d",&x)&&x)
			add(i,x);
	}
	tarjan();
	process();
}
