#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <stack>
using namespace std;
const int maxn=4010;
const int maxm=20010;
int n,m;
map <string,int> maps;
string str[2];

int head[maxn];
int to[maxm];
int next[maxm];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}

int dfn[maxn];
int low[maxn];
bool v[maxn];
bool ins[maxn];
stack <int> s;
int size[maxn];
int cnt;
int scc;
int belong[maxn];
void dfs(int x)
{
	v[x]=ins[x]=true;
	s.push(x);
	dfn[x]=low[x]=++cnt;
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
void tarjan()
{
	for(int i=1;i<=n;i++)
		if(!v[i])
			dfs(i);
}

void process()
{
	for(int i=1;i<=n;i++)
		if(size[belong[i]]>1)
			puts("Unsafe");
		else
			puts("Safe");
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>str[0]>>str[1];
		maps[str[0]]=maps[str[1]]=i;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>str[0]>>str[1];
		add(maps[str[0]],maps[str[1]]);
	}
	tarjan();
	process();
}
