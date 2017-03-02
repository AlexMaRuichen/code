#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=210;
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
bool bfs()
{
	static queue <int> q;
	for(int i=1;i<=T;i++)
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
bool map[110][110];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	S=n*2+1,T=n*2+2;
	for(int i=1;i<=n;i++)
		add(S,i,1),add(i+n,T,1);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=true;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j]|=map[i][k]&map[k][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(map[i][j])
				add(i,j+n,inf);
	printf("%d\n",n-dinic());
}
