#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=210;
const int maxm=maxn*maxn*2;
const int inf=1e9;
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
	for(int i=1;i<=n;i++)
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

int main()
{
	scanf("%d",&n);
	S=1,T=n;
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d",&x);
		while(x--)
			scanf("%d",&y),add(i,y,i^1&&y^n?inf:1);
	}
	printf("%d\n",dinic());
}
