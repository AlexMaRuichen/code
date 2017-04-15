#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=3010;
const int maxm=3010*1010;
const int inf=1e9;
int n;

struct edge
{
	int to,len;
	edge *next,*rev;
	edge(){}
	edge(int t,int l,edge *n):to(t),len(l),next(n){}
	inline void* operator new(size_t);
}*head[maxn],mempool[maxm];
inline void* edge :: operator new(size_t)
{
	static edge *p=mempool;
	return p++;
}
inline void add(int x,int y,int z)
{
	head[x]=new edge(y,z,head[x]);
	head[y]=new edge(x,0,head[y]);
	head[x]->rev=head[y];
	head[y]->rev=head[x];
}

queue <int> q;
int dep[maxn];
int S,T;
inline bool bfs()
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
inline int dfs(int x,int f)
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
inline int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
int a[maxn];
int sum;
inline int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int pow[46350];
int main()
{
	scanf("%d",&n);
	T=n+1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),sum+=a[i];
	for(int i=1;i*1ll*i<=~0u>>1;i++)
		pow[++pow[0]]=i*1ll*i;
	for(int i=1;i<=n;i++)
		if(a[i]&1)
		{
			add(S,i,a[i]);
			for(int j=1;j<=n;j++)
				if(a[j]&1^1&&gcd(a[i],a[j])==1&&*(lower_bound(pow+1,pow+pow[0]+1,a[i]*a[i]+a[j]*a[j]))==a[i]*a[i]+a[j]*a[j])
						add(i,j,inf);
		}
		else
			add(i,T,a[i]);
	printf("%d\n",sum-dinic());
}
