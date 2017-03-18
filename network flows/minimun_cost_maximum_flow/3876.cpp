#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=310;
const int inf=1e9;
struct edge
{
	int to,from,len,cost;
	edge *next,*rev;
	edge(){}
	edge(int to,int from,int len,int cost,edge *next):to(to),from(from),len(len),cost(cost),next(next){}
	void* operator new(size_t);
}*head[maxn],mempool[1000010];
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
int S,T;
int n;
int cnt;
int f[maxn];
bool v[maxn];
edge *pre[maxn];
queue <int> q;
bool spfa()
{
	for(int i=1;i<=n;i++)
		f[i]=inf;
	v[S]=true;
	f[S]=0;
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
int augment()
{
	int ans=0,w=inf;
	for(edge *p=pre[T];p;p=pre[p->from])
		w=min(w,p->len);
	for(edge *p=pre[T];p;p=pre[p->from])
		p->len-=w,p->rev->len+=w,ans+=p->cost*w;
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
	scanf("%d",&n);
	S=n+1;
	T=n+2;
	for(int i=1;i<=n;i++)
	{
		int w;
		scanf("%d",&w);
		add(i,T,w,0);
		while(w--)
		{
			int b,t;
			scanf("%d%d",&b,&t);
			add(S,b,1,t);
			add(i,b,inf,t);
		}
		if(i^1)
			add(i,1,inf,0);
	}
	n+=2;
	printf("%d\n",MCMF());
}
