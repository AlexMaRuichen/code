#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#define assign(x) x=++cnt
using namespace std;
const int maxn=300;
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
int S,T;
edge *pre[maxn];
int cnt=0;
int sum;
bool spfa()
{
	static queue <int> q;
	static bool v[maxn];
	static int f[maxn];
	for(int i=1;i<=cnt;i++)
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
	int w=inf,ans=0;
	for(edge *p=pre[T];p;p=pre[p->from])
		w=min(p->len,w);
	for(edge *p=pre[T];p;p=pre[p->from])
		p->len-=w,p->rev->len+=w,ans+=p->cost*w;
	sum-=w;
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
	int t;
	scanf("%d",&t);
	int n,m,k,a[60],l[60],p[60],d[60],q[60],in[60],out[60],sch[60];
	for(int i=1;i<=50;i++)
		assign(in[i]),assign(out[i]),assign(sch[i]);
	assign(S);
	assign(T);
	for(int D=1;D<=t;D++)
	{
		sum=0;
		memset(head,0,sizeof(head));
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),sum+=a[i];
		for(int i=1;i<=m;i++)
			scanf("%d%d",&l[i],&p[i]);
		for(int i=1;i<=k;i++)
			scanf("%d%d",&d[i],&q[i]);
		for(int i=1;i<=n;i++)
			add(S,in[i],a[i],0),add(out[i],T,a[i],0);
		for(int i=1;i<n;i++)
			add(out[i],out[i+1],inf,0);
		for(int i=1;i<=m;i++)
		{
			add(S,sch[i],l[i],0);
			for(int j=1;j<=n;j++)
				add(sch[i],out[j],inf,p[i]);
		}	
		for(int i=1;i<=k;i++)
			for(int j=1;j<=n-d[i]-1;j++)
				add(in[j],out[j+d[i]+1],inf,q[i]);
		int ans=MCMF();
		if(sum)
			printf("Case %d: impossible\n",D);
		else
			printf("Case %d: %d\n",D,ans);
	}
}
