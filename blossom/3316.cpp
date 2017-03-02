#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#define dis(i,j) (abs(p[i].first-p[j].first)+abs(p[i].second-p[j].second))
using namespace std;
const int maxn=370;
const int maxm=maxn*maxn<<1;
int n,l;
int map[20][20];

struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm],*P=mempool;
void* edge :: operator new(size_t)
{
	return P++;
}
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}

int fa[maxn];
int s[maxn];
int pre[maxn];
int next[maxn];
int v[maxn];
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
	for(int i=1;i<=361;i++)
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
				s[p->to]=1;
				pre[p->to]=x;
				if(!next[p->to])
				{
					for(int u=p->to,v=x,last;v;u=last,v=pre[u])
						last=next[v],next[v]=u,next[u]=v;
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
void init()
{
	memset(head,0,sizeof(head));
	memset(next,0,sizeof(next));
	P=mempool;
}
pair <int,int> p[maxn];
int cnt;
int main()
{
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			map[i][j]=++cnt;
	while(scanf("%d",&n)==1)
	{
		init();
		for(int i=1;i<=n;i++)
			scanf("%d%d",&p[i].first,&p[i].second),++p[i].first,++p[i].second;
		scanf("%d",&l);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(dis(i,j)<=l)
					add(map[p[i].first][p[i].second],map[p[j].first][p[j].second]);
		int ans=0;
		for(int i=1;i<=369;i++)
			if(!next[i])
				ans+=match(i);
		if((ans<<1)==n)
			puts("YES");
		else
			puts("NO");
	}

}
