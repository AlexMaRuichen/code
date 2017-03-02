#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=110;
const double eps=1e-7;
const double inf=1e9;
struct edge
{
	int to;
	double len;
	edge *next,*rev;
	edge(){}
	edge(int to,double len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t);
}*head[maxn],mem[maxn*maxn],*g=mem;
void* edge :: operator new(size_t)
{
	return g++;
}
void add(int x,int y,double z)
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
	for(int i=1;i<=T;i++)
		dep[i]=-1;
	q.push(S);
	dep[S]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len>eps&&dep[p->to]<0)
				dep[p->to]=dep[x]+1,q.push(p->to);
	}
	return dep[T]^-1;
}
double dfs(int x,double f)
{
	if(x==T)
		return f;
	double w,used=0;
	for(edge *p=head[x];p;p=p->next)
		if(p->len>eps&&dep[p->to]==dep[x]+1)
		{
			w=dfs(p->to,min(f-used,p->len));
			p->len-=w;
			p->rev->len+=w;
			used+=w;
			if(f-used<eps)
				return f;
		}
	if(f-used>eps)
		dep[x]=-1;
	return used;
}
int b[maxn];
int a[maxn];
int n,m;
bool dinic(double x)
{
	for(edge *p=mem;p!=g;p+=2)
		p->len+=p->rev->len,p->rev->len=0;
	for(edge *p=head[S];p;p=p->next)
		p->len=x*b[p->to-n];
	while(bfs())
		dfs(S,inf);
	for(edge *p=head[T];p;p=p->next)
		if(p->rev->len>eps)
			return false;
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=n+m+1,T=n+m+2;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	bool v;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{	
			scanf("%d",&v);
			if(v)
				add(i+n,j,inf);
		}
	for(int i=1;i<=m;i++)
		add(S,n+i,0);
	for(int i=1;i<=n;i++)
		add(i,T,a[i]);
	double l=0,r=1e7,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		dinic(mid)?r=mid:l=mid;
	}
	printf("%lf\n",l);
}
