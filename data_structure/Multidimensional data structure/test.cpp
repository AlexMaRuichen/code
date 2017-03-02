#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=200;
const int maxm=1e4;
int n,m;
struct edge
{
	int to;
	edge *nxt;
	edge(){}
	edge(int to,edge *nxt):to(to),nxt(nxt){}
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
int pre[maxn];
int nxt[maxn];
int getfa(int x)
{
	if(fa[x]^x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
int v[maxn];
int lca(int x,int y)
{
	static int times=0;
	++times;
	x=getfa(x);
	y=getfa(y);
	for(;;swap(x,y))
		if(x)
		{
			if(v[x]==times)
				return x;
			v[x]=times;
			x=getfa(pre[nxt[x]]);
		}
}
int s[maxn];
queue <int> q;
void blossom(int x,int y,int lca)
{
	while(getfa(x)!=lca)
	{
		pre[x]=y;
		y=nxt[x];
		if(s[y]==1)
			q.push(y),s[y]=0;
		if(fa[x]==x)
			fa[x]=lca;
		if(fa[y]==y)
			fa[y]=lca;
		x=pre[y];
	}
}
void match(int x)
{
	for(int i=0;i<=n;++i)
		fa[i]=i,s[i]=-1;
	while(!q.empty())
		q.pop();
	s[x]=0;
	q.push(x);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(edge *p=head[x];p;p=p->nxt)
		{
			if(s[p->to]==-1)
			{
				pre[p->to]=x;
				s[p->to]=1;
				if(!nxt[p->to])
				{
					for(int u=p->to,v=x,last;v;u=last,v=pre[u])
						last=nxt[v],nxt[v]=u,nxt[u]=v;
					return;
				}
				q.push(nxt[p->to]);
				s[nxt[p->to]]=0;
			}
			else if(!s[p->to]&&getfa(p->to)^getfa(x))
			{
				int l=lca(p->to,x);
				blossom(x,p->to,l);
				blossom(p->to,x,l);
			}
		}
	}
	return;
}
int a[maxn],b[maxn];
int sta[maxn];
int cnt;
void clear()
{
	cnt=0;
	p=mempool;
	memset(head,0,sizeof(head));
	memset(nxt,0,sizeof(nxt));
}
int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		clear();
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d",&a[i],&b[i]);
			add(a[i],b[i]);
		}
		for(int i=1;i<=n;++i)
			if(!nxt[i])
				match(i);
		for(int i=1;i<=m;++i)
			if(nxt[a[i]]!=b[i])
				sta[++cnt]=i;
		printf("%d\n%d",cnt,sta[1]);
		for(int i=2;i<=cnt;++i)
			printf(" %d",sta[i]);
		printf("\n");
	}
}

