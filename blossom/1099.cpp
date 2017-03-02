#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=230;
const int maxm=maxn*maxn;
int n;

struct edge 
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm];
void* edge :: operator new(size_t)
{
	static edge *p=mempool;
	return p++;
}
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}

int fa[maxn];
int pre[maxn];
int next[maxn];
int s[maxn];
int v[maxn];
int getfa(int x)
{
	if(fa[x]!=x)
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
queue <int> q;
void blossom(int x,int y,int lca)
{
	while(getfa(x)^lca)
	{
		pre[x]=y;
		y=next[x];
		if(s[y]==1)
			s[y]=0,q.push(y);
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
		fa[i]=i,s[i]=-1;
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
						last=next[v],next[v]=u,next[u]=v;
					return 1;
				}
				q.push(next[p->to]);
				s[next[p->to]]=0;
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
	scanf("%d",&n);
	int x,y,ans=0;
	while(scanf("%d%d",&x,&y)==2)
		add(x,y);
	for(int i=n;i;i--)
		if(!next[i])
			ans+=match(i);
	printf("%d\n",ans<<1);
	for(int i=1;i<=n;i++)
		if(next[i]>i)
			printf("%d %d\n",i,next[i]);
}
