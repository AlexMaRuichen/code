#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
typedef long long ll;
const int maxn=1010;
const int maxm=2.1e5+10;
const ll inf=1e18;
int cnt;
int n,m;

struct list
{
	int to;
	ll len;
	list *next;
	list(){}
	list(int t,ll l,list *n):to(t),len(l),next(n){};
	void* operator new(size_t);
}*listhead[maxn],listmempool[maxm];
void* list :: operator new(size_t)
{
	static list *p=listmempool;
	return p++;
}
void addlist(int x,int y,ll z)
{
	listhead[x]=new list(y,z,listhead[x]);
	listhead[y]=new list(x,z,listhead[y]);
}

struct edge
{
	int to;
	ll len;
	edge *next,*rev;
	edge(){}
	edge(int t,ll l,edge *n):to(t),len(l),next(n){}
	void* operator new(size_t);
}*edgehead[maxn],edgemempool[maxm];
void* edge :: operator new(size_t)
{
	static edge *p=edgemempool;
	return p++;
}
void addedge(int x,int y,ll z)
{
	edgehead[x]=new edge(y,z,edgehead[x]);
	edgehead[y]=new edge(x,0,edgehead[y]);
	edgehead[x]->rev=edgehead[y];
	edgehead[y]->rev=edgehead[x];
}

bool v[maxn];
ll f[maxn];
int in[maxn];
int out[maxn];
void dijkstra()
{
	for(int i=1;i<=n;i++)
		f[i]=inf;
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
}
void rebuild()
{
	for(int x=1;x<=n;x++)
		for(list *p=listhead[x];p;p=p->next)
			if(f[p->to]+p->len==f[x])
				addedge(out[x],in[p->to],inf);
}

int S,T;
int dep[maxn];
queue <int> q;
bool bfs()
{
	for(int i=1;i<=cnt;i++)
		dep[i]=-1;
	q.push(S);
	dep[S]=1;
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
ll dfs(int x,ll f)
{
	if(x==T)
		return f;
	ll w,used=0;
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
ll dinic()
{
	ll ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		assign(in[i]),assign(out[i]);
	S=in[1],T=out[n];
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		addlist(x,y,z);
	}
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		if(i==1||i==n)
			addedge(in[i],out[i],inf);
		else
			addedge(in[i],out[i],x);
	}
	dijkstra();
	rebuild();
	printf("%lld\n",dinic());
	
}
