#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int maxn=2000;
const int inf=1e9;
struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int to,int len,edge *next):to(to),len(len),next(next){}
	void* operator new(size_t)
	{
		static edge mem[1001001],*p=mem;
		return p++;
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
int cnt;
queue <int> q;
bool bfs()
{
	for(int i=1;i<=T;i++)
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
vector <int> ans[maxn];
bool v[maxn];
int a[maxn];
void dye(int x,int pos) 
{
    ans[pos].push_back(x);
    v[x]=true;
	for(edge *p=head[x];p;p=p->next) 
		if(!v[p->to]&&p->to^S&&p->to^T)	
		{
			if(a[x]&1&&!p->len) 
				dye(p->to,pos);
			else if(!(a[x]&1)&&!p->rev->len)
				dye(p->to,pos);
		}
}
const int N=1e7;
int prime[100000];
bool is[N];
void linear_shaker()
{
	for(int i=2;i<N;i++)
	{
		if(!is[i])
			prime[++prime[0]]=i;
		for(int j=1;j<=prime[0]&&i*prime[j]<N;j++)
		{
			is[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	printf("%d\n",prime[0]);
}
int main()
{
	linear_shaker();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%d", &a[i]);
	if(n&1) 
	{
		puts("Impossible");
		return 0;
	}
	S=n+1,T=n+2;
	for(int i=1;i<=n; i++) 
	{
		if(a[i]&1) 
			add(S,i,2);
		else 
			add(i,T,2);
	}
	for(int i=1;i<=n;i++)
		if(a[i]&1)
			for(int j=1;j<=n;j++)
				if(!(a[j]&1)&&!is[a[i]+a[j]])
					add(i,j,1);
	if(dinic()!=n) 
	{
		puts("Impossible");
		return 0;
	}
	int cnt=0;
	for(int i=1;i<=n;i++) 
		if(!v[i]) 
			dye(i,++cnt);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) 
	{
		printf("%lu ",ans[i].size());
		for(int j=ans[i].size()-1;~j;j--) 
			printf("%d ",ans[i][j]);
		puts("");
	}
}
