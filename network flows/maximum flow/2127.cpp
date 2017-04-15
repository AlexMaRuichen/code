#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=100010;
const int inf=1e9;
struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int dep[maxn];
int S,T;
int cnt;
bool bfs()
{
	static queue <int> q;
	for(int i=1;i<=cnt;i++)
		dep[i]=-1;
	q.push(S);
	dep[S]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&dep[p->to]<0)
				dep[p->to]=dep[x]+1,q.push(p->to);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(edge *p=head[x];p;p=p->next)
		if(p->len&&dep[p->to]==dep[x]+1)
		{
			w=dfs(p->to,min(p->len,f-used));
			p->len-=w;
			p->rev->len+=w;
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
	int ans=0,t;
	while(bfs())
		while((t=dfs(S,inf)))
			ans+=t;
	return ans;
}
int map[110][110];
int main()
{
	int n,m,sum=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			assign(map[i][j]);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(S,map[i][j],x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(map[i][j],T,x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(S,++cnt,x);
			add(cnt,map[i][j],inf);
			add(cnt,map[i+1][j],inf);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(++cnt,T,x);
			add(map[i][j],cnt,inf);
			add(map[i+1][j],cnt,inf);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(S,++cnt,x);
			add(cnt,map[i][j],inf);
			add(cnt,map[i][j+1],inf);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			add(++cnt,T,x);
			add(map[i][j],cnt,inf);
			add(map[i][j+1],cnt,inf);
		}
	printf("%d\n",sum-dinic());
}
