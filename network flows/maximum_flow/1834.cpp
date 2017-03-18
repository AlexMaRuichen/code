#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=1010;
const int inf=1e9;
struct edge
{
	int to,from,len,cost;
	edge *next,*rev;
	edge(){}
	edge(int to,int from,int len,int cost,edge *next):to(to),from(from),len(len),cost(cost),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y,int z,int c)
{
	head[x]=new edge(y,x,z,c,head[x]);
	head[y]=new edge(x,y,0,-c,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int dep[maxn];
queue <int> q;
int S,T;
bool bfs()
{
	for(int i=1;i<=T;i++)
		dep[i]=-1;
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(!p->cost&&p->len&&dep[p->to]<0)
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
		if(!p->cost&&p->len&&dep[p->to]==dep[x]+1)
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
edge *pre[maxn];
bool spfa()
{
	static bool v[maxn];
	for(int i=1;i<=S;i++)
		dep[i]=inf;
	dep[S]=0;
	v[S]=true;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&dep[p->to]>dep[x]+p->cost)
			{
				dep[p->to]=dep[x]+p->cost;
				pre[p->to]=p;
				if(!v[p->to])
					v[p->to]=true,q.push(p->to);
			}
		v[x]=false;
	}
	return dep[T]^inf;
}
int augment()
{
	int w=inf,ans=0;
	for(edge *p=pre[T];p;p=pre[p->from])
		w=min(w,p->len);
	for(edge *p=pre[T];p;p=pre[p->from])
		p->len-=w,p->rev->len+=w,ans+=w*p->cost;
	return ans;
}
int MCMF()
{
	int ans=0;
	while(spfa())
		ans+=augment();
	return ans;
}
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	S=1,T=n;
	for(int i=1;i<=m;i++)
	{
		static int x,y,c,w;
		scanf("%d%d%d%d",&x,&y,&c,&w);
		add(x,y,c,0);
		add(x,y,inf,w);
	}
	printf("%d ",dinic());
	S=n+1;
	add(S,1,k,0);
	printf("%d\n",MCMF());
}
