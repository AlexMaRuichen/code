#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#define assign(x) x=++cnt
using namespace std;
const int maxn=3010;
const int maxm=maxn*300;
const int inf=1e9;
int n,m;
int cnt;
struct size
{
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
int S,T;
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

int id[maxn];
int idCA[maxn];
int idCB[maxn];
int sum;
int main()
{
	scanf("%d",&n);
	assign(S);
	assign(T);
	for(int i=1;i<=n;i++)
		assign(id[i]);
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(S,id[i],x);
		sum+=x;
	}
	for(int i=1;i<=n;i++)
	{
		static int x;
		scanf("%d",&x);
		add(id[i],T,x);
		sum+=x;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		assign(idCA[i]);
		assign(idCB[i]);
		static int k,x,y;
		scanf("%d%d%d",&k,&x,&y);
		add(S,idCA[i],x);
		add(idCB[i],T,y);
		sum+=x+y;
		while(k--)
		{
			scanf("%d",&x);
			add(idCA[i],id[x],inf);
			add(id[x],idCB[i],inf);
		}
	}
	printf("%d\n",sum-dinic());
}
}obj;
int main()
{
	printf("%d\n",sizeof(obj));
}
