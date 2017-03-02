#include <stdio.h>
#include <algorithm>
#include <queue>
#define assign(x) x=++cnt
using namespace std;
const int maxn=20010;
const int inf=1e9;
int cnt;
struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}
int dep[maxn];
int S,T;
bool bfs()
{
	static queue <int> q;
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
int main()
{
	int n,m,k,sum=0;
	scanf("%d%d%d",&n,&m,&k);
	cnt=n;
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(S,i,x);
		sum+=x;
	}
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		sum+=x;
		add(i,T,x);
	}
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=k;i++)
	{
		static int s,a,b,x;
		scanf("%d",&s);
		if(!s)
			continue;
		scanf("%d%d",&a,&b);
		sum+=b;
		if(a)
			add(++cnt,T,b);
		else
			add(S,++cnt,b);
		while(s--)
		{
			scanf("%d",&x);
			if(a)
				add(x,cnt,inf);
			else
				add(cnt,x,inf);
		}
	}
	printf("%d\n",sum-dinic());
}
