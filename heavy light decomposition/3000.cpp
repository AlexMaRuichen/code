#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=300000;
struct atable
{
	int to,next,len;
}e[maxn*2+10];
struct point
{
	int x,y,len;
}p[maxn+10];
int head[maxn+10],tot;
int dif[maxn+10];
int son[maxn+10];
int pos[maxn+10];
int size[maxn+10];
int fa[maxn+10];
int top[maxn+10];
int depth[maxn+10];
int q[maxn+10];
int dis[maxn+10];
int P[maxn+10];	
int cost[maxn+10];
int cnt;
int ans;
void add(int x,int y,int z)
{
	e[++tot].to=y;
	e[tot].len=z;
	e[tot].next=head[x];
	head[x]=tot;
}
void dfs_son(int dep,int x,int F)
{
	depth[x]=dep;
	fa[x]=F;
	size[x]=1;
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=F)
		{
			cost[e[i].to]=e[i].len;
			dis[e[i].to]=dis[x]+e[i].len;
			dfs_son(dep+1,e[i].to,x);
			size[x]+=size[e[i].to];
			son[x]=(size[e[i].to]>size[son[x]]?e[i].to:son[x]);
		}
}
void dfs_top(int x,int T)
{
	top[x]=T;
	P[++cnt]=cost[x];
	pos[x]=cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs_top(e[i].to,e[i].to);
}
int n,m;
void process(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		dif[pos[top[x]]]++;
		dif[pos[x]+1]--;
		x=fa[top[x]];
	}
	if(x!=y)
	{
		if(depth[x]>depth[y])
			swap(x,y);
		dif[pos[x]+1]++;
		dif[pos[y]+1]--;
	}
}
int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	return depth[x]>depth[y]?y:x;
}
bool cmp(point x,point y)
{
	return x.len>y.len;
}
int check(int x)
{
	int t=0;
	while(p[t+1].len>x)
		t++;
	if(q[t]!=-1)
		return q[t];
	memset(dif,0,sizeof(dif));
	for(int i=1;i<=t;i++)
		process(p[i].x,p[i].y);
	int M=0,Tot=0;
    for (int i=1;i<=n;i++)
    {
    	Tot+=dif[i];
    	if(Tot==t)
    		M=max(M,P[i]);
    }
    q[t]=M;
    return M;
}
int main()
{
	memset(q,-1,sizeof(q));
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
	
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs_son(1,1,0);
	dfs_top(1,1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].len=dis[p[i].x]+dis[p[i].y]-2*dis[lca(p[i].x,p[i].y)];
	}
	sort(p+1,p+m+1,cmp);
	int l=0,r=p[1].len;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(p[1].len-check(mid)>mid)
			l=mid+1;
		else
		{
			ans=mid;
			r=mid-1;
		}
	}
	printf("%d\n",ans);
}
