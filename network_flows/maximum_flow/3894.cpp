#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
#define judge(x,y) (x>=1&&x<=n&&y>=1&&y<=m)
using namespace std;
const int maxn=110*110*3;
const int maxm=1e6+10;
const int inf=1e9;
int cnt;
int n,m;

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

int dep[maxn];
queue <int> q;
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

int art[110][110];
int sci[110][110];
int sart[110][110];
int ssci[110][110];
int id[110][110];
int ida[110][110];
int idb[110][110];
int sum;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int main()
{
	scanf("%d%d",&n,&m);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			assign(id[i][j]);
			assign(ida[i][j]);
			assign(idb[i][j]);
			scanf("%d",&art[i][j]);
			sum+=art[i][j];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&sci[i][j]),sum+=sci[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&sart[i][j]),sum+=sart[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&ssci[i][j]),sum+=ssci[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			add(S,id[i][j],art[i][j]);
			add(id[i][j],T,sci[i][j]);
			add(S,ida[i][j],sart[i][j]);
			add(idb[i][j],T,ssci[i][j]);
			add(ida[i][j],id[i][j],inf);
			add(id[i][j],idb[i][j],inf);
			for(int k=0;k<4;k++)
				if(judge(i+dx[k],j+dy[k]))
					add(ida[i][j],id[i+dx[k]][j+dy[k]],inf),
					add(id[i+dx[k]][j+dy[k]],idb[i][j],inf);
		}
	printf("%d\n",sum-dinic());
}
