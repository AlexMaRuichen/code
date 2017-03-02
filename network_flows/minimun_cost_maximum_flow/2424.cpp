#include <stdio.h>
#include <algorithm>
#include <queue>
const int maxn=60;
const int inf=1e9;
using namespace std;
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
int S,T;
edge *pre[maxn];
bool spfa()
{
	static queue <int> q;
	static int f[maxn];
	static bool v[maxn];
	for(int i=1;i<=T;i++)
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
	int n,m,s;
	scanf("%d%d%d",&n,&m,&s);
	S=n+1,T=n+2;
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(i,T,x,0);
	}
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(S,i,inf,x);
	}
	for(int i=1;i<n;i++)
		add(i,i+1,s,m);
	printf("%d\n",MCMF());
}
