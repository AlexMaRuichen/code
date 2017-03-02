#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=110;
const int maxm=maxn<<1;
int n,m;

struct edge 
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm],*p=mempool;
void* edge :: operator new(size_t)
{
	return p++;
}
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}

int fa[maxn];
int s[maxn];
int v[maxn];
int pre[maxn];
int next[maxn];
queue <int> q;
int getfa(int x)
{
	if(fa[x]^x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
int lca(int x,int y)
{
	static int times;
	++times;
	x=getfa(x);
	y=getfa(y);
	for(;;swap(x,y))
		if(x)
		{
			if(v[x]==times)
				return x;
			v[x]=times;
			x=getfa(pre[next[x]]);
		}
}
void blossom(int x,int y,int lca)
{
	while(getfa(x)^lca)
	{
		pre[x]=y;
		y=next[x];
		if(s[y]==1)
			q.push(y),s[y]=0;
		if(fa[x]==x)
			fa[x]=lca;
		if(fa[y]==y)
			fa[y]=lca;
		x=pre[y];
	}
}
int match(int x)
{
	for(int i=1;i<=n;i++)
		s[i]=-1,fa[i]=i;
	while(!q.empty())
		q.pop();
	s[x]=0;
	q.push(x);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->next)
			if(s[p->to]==-1)
			{
				pre[p->to]=x;
				s[p->to]=1;
				if(!next[p->to])
				{
					for(int u=p->to,v=x,last;v;u=last,v=pre[u])
						last=next[v],next[u]=v,next[v]=u;
					return 1;
				}
				s[next[p->to]]=0;
				q.push(next[p->to]);
			}
			else if(!s[p->to]&&getfa(x)^getfa(p->to))
			{
				int l=lca(x,p->to);
				blossom(x,p->to,l);
				blossom(p->to,x,l);
			}
	}
	return 0;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(n&1)
		{
			for(int i=1;i<=m;i++)
				scanf("%*d%*d");
			puts("NO");
		}
		else 
		{
			int ans=0;
			p=mempool;
			memset(head,0,sizeof(head));
			memset(next,0,sizeof(next));
			for(int i=1;i<=m;i++)
			{
				static int x,y;
				scanf("%d%d",&x,&y);
				add(x,y);
			}
			for(int i=1;i<=n;i++)
				if(!next[i])
					ans+=match(i);
			if(ans==(n>>1))
				puts("YES");
			else
				puts("NO");
		}
	}
}
