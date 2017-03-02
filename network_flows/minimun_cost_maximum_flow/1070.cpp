#include <stdio.h>
#include <algorithm>
#include <queue>
#include <map>
#define assign(x) x=++cnt
using namespace std;
const int maxn=1000;
const int maxm=maxn*maxn;
const int inf=1e9;
int n,m;
int cnt;
int a[70][15];

struct edge
{
	int to,from,len,cost;
	edge *next,*rev;
	edge(){}
	edge(int t,int f,int l,int c,edge *n):to(t),from(f),len(l),cost(c),next(n){}
	void* operator new(size_t);	
}*head[maxn],mempool[maxm];
void* edge :: operator new(size_t)
{
	static edge *p=mempool;
	return p++;
}
void add(int x,int y,int z,int c)
{
	head[x]=new edge(y,x,z,c,head[x]);
	head[y]=new edge(x,y,0,-c,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

edge *pre[maxn];
int f[maxn];
bool v[maxn];
queue <int> q;
int S,T;
bool spfa()
{
	for(int i=1;i<=cnt;i++)
		f[i]=inf;
	f[S]=0;
	v[S]=true;
	q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(p->len&&f[p->to]>f[x]+p->cost)
			{
				f[p->to]=f[x]+p->cost;
				pre[p->to]=p;
				if(!v[p->to])
					v[p->to]=true,q.push(p->to);
			}
		v[x]=false;
	}
	return f[T]^inf;
}
map <int,int> maps;
int tech[10];
int car[65];
int t[10];
int augment()
{
	int w=inf,ans=0,id=maps[pre[T]->from];
	for(edge *p=pre[T];p;p=pre[p->from])
		w=min(w,p->len);
	for(edge *p=pre[T];p;p=pre[p->from])
		p->len-=w,p->rev->len+=w,ans+=w*p->cost;
	assign(tech[id]);
	maps[tech[id]]=id;
	++t[id];
	for(int i=1;i<=n;i++)
		add(car[i],tech[id],1,a[i][id]*t[id]);
	add(tech[id],T,1,0);
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
	scanf("%d%d",&m,&n);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		assign(car[i]),add(S,car[i],1,0);
	for(int i=1;i<=m;i++)
		assign(tech[i]),++t[i],add(tech[i],T,1,0),maps[tech[i]]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			add(car[i],tech[j],1,a[i][j]);
		}
	printf("%.2lf\n",1.0*MCMF()/n);
}
