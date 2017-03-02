#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=510;
const int maxm=250010;
char buf[33554500];
int n,m;
int Q[maxn];
int *tail;
int fa[maxn];
int pre[maxn];
int next[maxn];
int v[maxn];
int s[maxn];

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
inline void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}
int getfa(int x)
{
	if(fa[x]^x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
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
			s[*tail++=y]=0;
		if(fa[x]==x)
			fa[x]=lca;
		if(fa[y]==y)
			fa[y]=lca;
		x=pre[y];
	}
}
int match(int x)
{
	for(int i=0;i<=n;i++)
		fa[i]=i,s[i]=-1;
	tail=Q;
	s[*tail++=x]=0;
	int *begin=Q;
	while(begin!=tail)
	{
		int x=*begin++;
		for(edge *p=head[x];p;p=p->next)
		{
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
				s[*tail++=next[p->to]]=0;
			}
			else if(!s[p->to]&&getfa(p->to)^getfa(x))
			{
				int l=lca(p->to,x);
				blossom(x,p->to,l);
				blossom(p->to,x,l);
			}
		}
	}
	return 0;
}
inline void read(register int &x)
{
	static char *ch=buf;
	x=0;
	while(*ch<'0')
		++ch;
	while(*ch>='0')
		x=(x<<1)+(x<<3)+*ch++-'0';
}
inline void out(register int &x)
{
	static char s[10];
	static int id;
	id=0;
	while(x)
		s[++id]=x%10+'0',x/=10;
	while(id)
		putchar(s[id--]);	
	putchar(' ');
}
int main()
{
	fread(buf,1,33554500,stdin);
	read(n);
	read(m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		read(x);
		read(y);
		add(x,y);
	}
	int ans=0;
	for(int i=n;i;i--)
		if(!next[i])
			ans+=match(i);
	out(ans);
	putchar('\n');
	for(int i=1;i<=n;i++)
		if(next[i])
			out(next[i]);
		else
			putchar('0'),putchar(' ');
	putchar('\n');
}

