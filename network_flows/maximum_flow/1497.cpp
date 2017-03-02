#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=55010;
const int maxm=310010;
const int inf=1e9;
int n,m;
int cnt;

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *n):to(t),len(l),next(n){}
	inline void* operator new(size_t);
}*head[maxn],mempool[maxm],*p=mempool;
inline void* edge :: operator new(size_t)
{
	return p++;
}
inline void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

int dep[maxn];
queue <int> q;
int S,T;
inline bool bfs()
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
inline int dfs(int x,int f)
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
inline int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
int sta[maxn];
int pla[maxn];
int sum;
int main()
{
	scanf("%d%d",&n,&m);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
	{
		static int x;
		assign(sta[i]);
		scanf("%d",&x);
		add(S,sta[i],x);
	}
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		assign(pla[i]);
		scanf("%d%d%d",&x,&y,&z);
		add(sta[x],pla[i],inf);
		add(sta[y],pla[i],inf);
		add(pla[i],T,z);
		sum+=z;
	}
	printf("%d\n",sum-dinic());
}
