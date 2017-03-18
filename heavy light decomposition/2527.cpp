#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=40000;
struct segment_tree
{
	int l,r,m;
}t[131100];
struct atable
{
	int next,to,len;
}e[maxn*2+10];
int a[maxn+10];
int head[maxn+10];
int tot;
int son[maxn+10];
int fa[maxn+10];
int size[maxn+10];
int top[maxn+10];
int depth[maxn+10];
int pos[maxn+10];
int cnt;
int query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	if(l==L&&R==r)
		return t[x].m;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x<<1,l,r);
	if(mid<l)
		return query(x<<1|1,l,r);
	return max(query(x<<1,l,mid),query(x<<1|1,mid+1,r));
}
int solve(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=max(ans,query(1,pos[top[x]],pos[x]));
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])
		swap(x,y);
	if(x!=y)
		ans=max(ans,query(1,pos[x]+1,pos[y]));
	return ans;
}
void modify(int x,int p,int v)
{
	int L=t[x].l;
	int R=t[x].r;
	if(L==R&&L==p)
	{
		t[x].m=v;
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=p)
		modify(x<<1,p,v);
	if(mid<p)
		modify(x<<1|1,p,v);
	t[x].m=max(t[x<<1].m,t[x<<1|1].m);
}
void build(int x,int l,int r)
{
	t[x].l=l;
	t[x].r=r;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void dfs_son(int dep,int x,int F)
{
	size[x]=1;
	fa[x]=F;
	depth[x]=dep;
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=F)
		{
			dfs_son(dep+1,e[i].to,x);
			size[x]+=size[e[i].to];
			a[e[i].to]=e[i].len;
			son[x]=(size[e[i].to]>size[son[x]]?e[i].to:son[x]);
		}
}
void dfs_top(int x,int T)
{
	top[x]=T;
	pos[x]=++cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs_top(e[i].to,e[i].to);
}
void add(int x,int y,int z)
{
	e[++tot].to=y;
	e[tot].len=z;
	e[tot].next=head[x];
	head[x]=tot;
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	build(1,1,n);
	dfs_son(1,1,0);
	dfs_top(1,1);
	for(int i=1;i<=n;i++)
		modify(1,pos[i],a[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",solve(x,y));
	}
}
