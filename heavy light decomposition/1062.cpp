#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=10010;
const int maxm=100010;
int n,m,q;
struct atable
{
	int to,next,len;
}at[maxn<<1];
int head[maxn],tot;
void add(int x,int y,int z)
{
	at[++tot].to=y;
	at[tot].len=z;
	at[tot].next=head[x];
	head[x]=tot;
}
struct edge
{
	int x,y,len;
}e[maxm];
bool cmp(edge x,edge y)
{
	return x.len<y.len;
}
int f[maxn];
int s[maxn];
void init()
{
	for(int i=1;i<=n;i++)
		f[i]=i,s[i]=1;
}
int getfa(int x)
{
	if(f[x]!=x)
		f[x]=getfa(f[x]);
	return f[x];
}
void kruskal()
{
	init();
	for(int i=1;i<=m;i++)
	{
		int x=e[i].x;
		int y=e[i].y;
		x=getfa(x);
		y=getfa(y);
		if(x==y)
			continue;
		if(s[x]>s[y])
			swap(x,y);
		add(e[i].x,e[i].y,e[i].len);
		add(e[i].y,e[i].x,e[i].len);
		s[y]+=s[x];
		f[x]=y;
	}
}
struct segment_tree
{
	int l,r,m;
}t[32780];
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
	if(p<=mid)
		modify(x<<1,p,v);
	else
		modify(x<<1|1,p,v);
	t[x].m=max(t[x<<1].m,t[x<<1|1].m);
}
int query(int x,int l,int r)
{
	int L=t[x].l;
	int R=t[x].r;
	if(L==l&&R==r)
		return t[x].m;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query(x<<1,l,r);
	if(mid<l)
		return query(x<<1|1,l,r);
	return max(query(x<<1,l,mid),query(x<<1|1,mid+1,r));
}
int fa[maxn];
int size[maxn];
int pos[maxn];
int son[maxn];
int a[maxn];
int depth[maxn];
int top[maxn];
int cnt;
void dfs_son(int dep,int x,int F)
{
	size[x]=1;
	fa[x]=F;
	depth[x]=dep;
	for(int i=head[x];i;i=at[i].next)
		if(at[i].to!=F)
		{
			dfs_son(dep+1,at[i].to,x);
			size[x]+=size[at[i].to];
			a[at[i].to]=at[i].len;
			son[x]=(size[son[x]]>size[at[i].to]?son[x]:at[i].to);
		}
}
void dfs_top(int x,int T)
{
	top[x]=T;
	pos[x]=++cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=at[i].next)
		if(at[i].to!=fa[x]&&at[i].to!=son[x])
			dfs_top(at[i].to,at[i].to);
}
int process(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=max(ans,query(1,pos[top[x]],pos[x]));
		x=fa[top[x]];
	}
	if(x!=y)
	{
		if(depth[x]>depth[y])
			swap(x,y);
		ans=max(ans,query(1,pos[x]+1,pos[y]));
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
	sort(e+1,e+m+1,cmp);
	kruskal();
	build(1,1,n);
	dfs_son(1,1,0);
	dfs_top(1,1);
	for(int i=1;i<=n;i++)
		modify(1,pos[i],a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int s,t;
		scanf("%d%d",&s,&t);
		printf("%d\n",process(s,t));
	}
}
