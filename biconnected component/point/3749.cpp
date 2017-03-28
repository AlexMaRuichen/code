#include <stdio.h>
#include <algorithm>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;
const int maxn=5010;
const int maxm=20010;
int n,m,q;

int to[maxm];
int nex[maxm];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	nex[tot]=head[x];
	head[x]=tot;
	
	to[++tot]=x;
	nex[tot]=head[y];
	head[y]=tot;
}

int dfn[maxn];
int low[maxn];
int size[maxn];
int cnt;
stack <int> s;
vector <int> belong[maxn];
int pbc;
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++cnt;
	s.push(x);
	for(int i=head[x];i;i=nex[i])
		if(to[i]!=fa)
		{
			if(!dfn[to[i]])
			{
				dfs(to[i],x);
				low[x]=min(low[x],low[to[i]]);
				if(low[to[i]]>=dfn[x])
				{
					++pbc;
					int now=0;
					while(now^to[i])
					{
						now=s.top();
						s.pop();
						++size[pbc];
						belong[now].push_back(pbc);
					}
					++size[pbc];
					belong[x].push_back(pbc);
				}
			}
			else if(dfn[to[i]]<dfn[x])
				low[x]=min(low[x],dfn[to[i]]);
		}
}
void tarjan()
{
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,0);
}
int fa[maxn];
int Rank[maxn];
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	x=getfa(x);
	y=getfa(y);
	if(x==y)
		return;
	if(Rank[x]>Rank[y])
		swap(x,y);
	else if(Rank[x]==Rank[y])
		++Rank[y];
	fa[x]=y;
}
void init()
{
	tot=0;
	cnt=0;
	pbc=0;
	for(int i=1;i<=n;i++)
		belong[i].clear(),fa[i]=i,Rank[i]=1,head[i]=size[i]=0,dfn[i]=low[i]=0;
}
char* check(int x,int y)
{
	if(getfa(x)^getfa(y))
		return "zero";
	for(int i=0;i<belong[x].size();i++)
		for(int j=0;j<belong[y].size();j++)
			if(belong[x][i]==belong[y][j]&&size[belong[x][i]]>2)
				return "two or more";
	return "one";
}
int T;
int main()
{
	while(scanf("%d%d%d",&n,&m,&q)==3&&(n|m|q))
	{
		init();
		for(int i=1;i<=m;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			add(x+1,y+1);
			merge(x+1,y+1);
		}
		tarjan();
		printf("Case %d:\n",++T);
		for(int i=1;i<=q;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			puts(check(x+1,y+1));
		}
	}
}
