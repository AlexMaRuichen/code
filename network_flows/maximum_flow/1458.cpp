#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int maxn=210;
const int maxm=100010;
const int inf=1e9;

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *p):to(t),len(l),next(p){}
	void* operator new(size_t);
}*head[maxn],mempool[maxm];
void* edge :: operator new(size_t)
{
	static edge *p=mempool;
	return p++;
}
void add(int x,int y,int len)
{
	head[x]=new edge(y,len,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

queue <int> q;
int dep[maxn];
int S=maxn-1,T=maxn-2;
bool bfs()
{
	memset(dep,-1,sizeof(dep));
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
int n,m,k;
int l[maxn];
int c[maxn];
int a[maxn];
int b[maxn];
bool map[maxn][maxn];
int main()
{
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=m;i++)
		scanf("%d",&l[i]),l[i]=n-l[i];
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]),c[i]=m-c[i];
	for(int i=1;i<=k;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=true;
		++a[x];
		++b[y];
		if(a[x]>l[x]||b[y]>c[y])
			return puts("JIONG!"),0;
	}
	for(int i=1;i<=m;i++)
		add(S,i,l[i]-a[i]);
	for(int i=1;i<=n;i++)
		add(i+m,T,c[i]-b[i]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(!map[i][j])
				add(i,j+m,1);
	printf("%d\n",n*m-k-dinic());
}
