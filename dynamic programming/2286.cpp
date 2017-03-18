#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=250010;
const int log=18;
const ll inf=~0ull>>1;
struct edge
{
	int to,len;
	edge *next;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t);
}*head[maxn],mem[maxn<<1],*g=mem;
void* edge :: operator new(size_t)
{
	return g++;
}
void add(int x,int y,int z=0)
{
	head[x]=new edge(y,z,head[x]);
}
int fa[log+1][maxn];
int dis[log+1][maxn];
int dfn[maxn];
int dep[maxn];
void init(int x)
{
	static int cnt;
	dfn[x]=++cnt;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]],
		dis[i][x]=min(dis[i-1][x],dis[i-1][fa[i-1][x]]);
	for(edge *&p=head[x];p;p=p->next)
		if(p->to^fa[0][x])
		{
			fa[0][p->to]=x;
			dis[0][p->to]=p->len;
			dep[p->to]=dep[x]+1;
			init(p->to);
		}
}
int get(int x,int y)
{
	for(int i=0;i<=log;i++)
		if(y&(1<<i))
			x=fa[i][x];
	return x;
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	x=get(x,dep[x]-dep[y]);
	if(x==y)
		return x;
	for(int i=log;~i;i--)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
pair <int,int> p[maxn];
int stack[maxn];
int top;
bool v[maxn];
ll f[maxn];
int k;
void build()
{
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
		scanf("%d",&p[i].second),p[i].first=dfn[p[i].second],v[p[i].second]=true;
	sort(p+1,p+k+1);
	top=0;
	stack[++top]=1;
	for(int i=1;i<=k;i++)
	{
		int lca=LCA(p[i].second,stack[top]);
		while(dep[stack[top]]>dep[lca])
		{
			if(dep[stack[top-1]]<=dep[lca])
			{
				add(lca,stack[top--]);
				if(lca^stack[top])
					stack[++top]=lca;
				break;
			}
			add(stack[top-1],stack[top]);
			--top;
		}
		stack[++top]=p[i].second;
	}
	while(top-1)
		add(stack[top-1],stack[top]),--top;
}
int dist(int x,int y)
{
	int ans=~0u>>1;
	for(int i=log;~i;i--)
		if(dep[fa[i][x]]>=dep[y])
			ans=min(ans,dis[i][x]),x=fa[i][x];
	return ans;
}
void clear(int x)
{
	v[x]=false;
	f[x]=0;
	for(edge *&p=head[x];p;p=p->next)
		clear(p->to);
}
void dfs(int x)
{
	for(edge *p=head[x];p;p=p->next)
	{
		dfs(p->to);
		f[x]+=min(f[p->to],ll(dist(p->to,x)));
	}
	if(v[x])
		f[x]=inf;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dep[1]=1;
	init(1);
	g=mem;
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		g=mem;
		build();
		dfs(1);
		printf("%lld\n",f[1]);
		clear(1);
	}
}
