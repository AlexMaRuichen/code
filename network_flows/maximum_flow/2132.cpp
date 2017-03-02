#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
#define judge(x,y) (x>=1&&x<=n&&y>=1&&y<=m)
using namespace std;
const int maxn=110*110;
const int maxm=1e6+10;
const int inf=1e9;
int n,m;
int cnt;

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *n):to(t),len(l),next(n){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm];
void* edge :: operator new(size_t)
{
	static edge *p=mempool;
	return p++;
}
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

queue <int> q;
int dep[maxn];
int S,T;
bool bfs()
{
	for(int i=1;i<=cnt;i++)
		dep[i]=-1;
	dep[S]=1;
	q.push(S);
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
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
int sum;
int id[110][110];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int main()
{
	scanf("%d%d",&n,&m);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			assign(id[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			if((i+j)&1)
				add(S,id[i][j],x);
			else
				add(id[i][j],T,x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			if((i+j)&1)
				add(id[i][j],T,x);
			else
				add(S,id[i][j],x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			for(int k=0;k<4;k++)
				if(judge(i+dx[k],j+dy[k]))
					add(id[i][j],id[i+dx[k]][j+dy[k]],x),add(id[i+dx[k]][j+dy[k]],id[i][j],x),sum+=x;
		}
	printf("%d\n",sum-dinic());
}
