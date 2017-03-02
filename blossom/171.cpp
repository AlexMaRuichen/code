#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#include <map>
#define assign(x) x=++cnt
using namespace std;
const int maxn=610;
const int maxm=maxn*maxn+310*6;
queue <int> q;
int n,m,e;
int cnt;

struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge* next):to(to),next(next){}
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
	for(int i=1;i<=cnt;i++)
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
int ball[310];
int buc[110][3];
map<int,int> maps;
void init()
{
	memset(head,0,sizeof(head));
	memset(next,0,sizeof(next));
	p=mempool;
	cnt=0;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		init();
		scanf("%d%d%d",&n,&m,&e);
		for(int i=1;i<=n;i++)
			assign(ball[i]);
		for(int i=1;i<=m;i++)
			assign(buc[i][0]),maps[buc[i][0]]=i,
			assign(buc[i][1]),maps[buc[i][1]]=i,
			assign(buc[i][2]),maps[buc[i][2]]=i,
			add(buc[i][0],buc[i][1]),
			add(buc[i][1],buc[i][2]),
			add(buc[i][2],buc[i][0]);
		for(int i=1;i<=e;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			add(ball[x],buc[y][0]);
			add(ball[x],buc[y][1]);
			add(ball[x],buc[y][2]);
		}
		int ans=0;
		for(int i=1;i<=cnt;i++)
			if(!next[i])
				ans+=match(i);
		printf("%d\n",ans-n);
	}
}
