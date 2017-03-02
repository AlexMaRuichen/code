#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#include <functional>
using namespace std;
const int maxn=510;
const int maxm=124750*2+10;
const int inf=1e9;
int n,m;

struct list
{
	int to,len,cost;
	list *next;
	list(){}
	list(int t,int l,int c,list *n):to(t),len(l),cost(c),next(n){}
	void* operator new(size_t);
}*listhead[maxn],listmempool[maxm];
void* list:: operator new(size_t)
{
	static list *p=listmempool;
	return p++;
}
void addlist(int x,int y,int z,int c)
{
	listhead[x]=new list(y,z,c,listhead[x]);
	listhead[y]=new list(x,z,c,listhead[y]);
}

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *n):to(t),len(l),next(n){}
	void* operator new(size_t);
}*edgehead[maxn],edgemempool[maxm];
void* edge:: operator new(size_t)
{
	static edge *p=edgemempool;
	return p++;
}
void addedge(int x,int y,int z)
{
	edgehead[x]=new edge(y,z,edgehead[x]);
	edgehead[y]=new edge(x,0,edgehead[y]);
	edgehead[x]->rev=edgehead[y];
	edgehead[y]->rev=edgehead[x];
}

int size;
int f[maxn];
bool v[maxn];
int dijkstra()
{
	memset(f,0x3f,sizeof(f));
	f[n]=0;
	int T=n;
	while(T--)
	{
		int x=0;
		for(int i=1;i<=n;i++)
			if((!x||f[x]>f[i])&&!v[i])
				x=i;
		v[x]=true;
		for(list *p=listhead[x];p;p=p->next)
			if(f[p->to]>f[x]+p->len)
				f[p->to]=f[x]+p->len;
	}
	return f[1];
}
void rebuild()
{
	for(int x=1;x<=n;x++)
		for(list *p=listhead[x];p;p=p->next)
			if(p->len+f[p->to]==f[x])
				addedge(x,p->to,p->cost);
}

queue <int> q;
int dep[maxn];
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
		for(edge *p=edgehead[x];p;p=p->next)
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
	for(edge *p=edgehead[x];p;p=p->next)
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
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z,c;
		scanf("%d%d%d%d",&x,&y,&z,&c);
		addlist(x,y,z,c);
	}
	S=1,T=n;
	printf("%d\n",dijkstra());
	rebuild();
	printf("%d\n",dinic());
}
