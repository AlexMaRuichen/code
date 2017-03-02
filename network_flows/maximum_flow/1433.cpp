#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=110;
const int maxm=maxn*maxn*5;
const int inf=1e9;
int cnt;
int n,m;

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *n):to(t),len(l),next(n){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm],*p=mempool;
void* edge:: operator new(size_t)
{
	return p++;
}
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

int S,T;
int dep[maxn];
queue <int> q;
bool bfs()
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

int per[maxn];
int bed[maxn];
bool at[maxn];
int sum;
void init()
{
	p=mempool;
	for(int i=1;i<=cnt;i++)
		head[i]=NULL,at[i]=false;
	cnt=0;
	sum=0;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		init();
		assign(S);
		assign(T);
		for(int i=1;i<=n;i++)
			assign(per[i]),assign(bed[i]);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&at[i]);
			if(at[i])
				add(bed[i],T,1);
			else
				add(S,per[i],1),++sum;
		}
		for(int i=1;i<=n;i++)
		{
			static int x;
			scanf("%d",&x);
			if(at[i]&&!x)
				add(S,per[i],1),++sum;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				static int x;
				scanf("%d",&x);
				if(i==j||x)
					add(per[i],bed[j],1);
			}
		if(dinic()==sum)
			puts("^_^");
		else
			puts("T_T");
	}
}
