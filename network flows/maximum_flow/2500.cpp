#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#define assign(x) (x=++cnt)
#define moon(x) (id[x][25])
using namespace std;
const int maxn=600;
const int maxm=2500;
const int inf=1e9;

int id[50][50];
int h[50];
int s[50];
int stop[50][50];
int to[maxm];
int next[maxm];
int len[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z)
{
	to[++tot]=y;
	next[tot]=head[x];
	len[tot]=z;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	head[y]=tot;
}

int S=590,T;
int cnt;
int dep[maxn];
queue <int> q;
bool bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&dep[to[i]]==-1)
				dep[to[i]]=dep[x]+1,q.push(to[i]);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(int i=head[x];i;i=next[i])
		if(len[i]&&dep[to[i]]==dep[x]+1)
		{
			w=dfs(to[i],min(len[i],f-used));
			len[i]-=w;
			len[i^1]+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used^f)
		dep[x]=-1;
	return used;
}
int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}

int n,m,k;
int fa[maxn];
int rank[maxn];
void init()
{
	for(int i=1;i<=599;i++)
		rank[i]=1,fa[i]=i;
}
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
	if(rank[x]>rank[y])
		swap(x,y);
	else if(rank[x]==rank[y])
		++rank[y];
	fa[x]=y;
}

void print(int x)
{
	for(int i=0;i<=n;i++)
		printf("%d:%d\n",i,id[x][i]);
	printf("moon:%d\n",moon(x));
}
int main()
{
	freopen("home10.in","r",stdin);
//	freopen("home.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	init();
	assign(moon(0));
	for(int i=0;i<=n;i++)
		assign(id[0][i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&h[i],&s[i]);
		for(int j=0;j<s[i];j++)
		{
			scanf("%d",&stop[i][j]);
			stop[i][j]=(stop[i][j]^-1?stop[i][j]:25);
			if(j)
				merge(stop[i][j],stop[i][j-1]);
		}
	}
//	print(0);
	if(getfa(0)^getfa(25))
		return puts("0"),0;
	add(S,id[0][0],k);
	int ans=0;
	for(int i=1;;i++)
	{
		for(int j=0;j<=n;j++)
			assign(id[i][j]);
		assign(moon(i));
		for(int j=1;j<=m;j++)
			add(id[i-1][stop[j][(i-1)%s[j]]],id[i][stop[j][i%s[j]]],h[j]);
		for(int j=0;j<=n;j++)
			add(id[i-1][j],id[i][j],inf);
		add(moon(i-1),moon(i),inf);
		T=moon(i);
		ans+=dinic();
//		printf("%d\n",ans);
		if(ans>=k)
			return printf("%d\n",i),0;
//		print(i);
	}
}
