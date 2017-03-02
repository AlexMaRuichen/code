#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=10000;
const int maxe=50000;
int n,m;
int q;
struct edge
{
	int x,y,len;
}e[maxe+10];
struct atable
{
	int to,next,len;
}at[maxe*2+10];
struct segment_tree
{
	int l,r,m;
}t[32800];
int head[maxn+10],tot;
bool v[maxn+10];
void add(int x,int y,int z)
{
	at[++tot].to=y;
	at[tot].len=z;
	at[tot].next=head[x];
	head[x]=tot;
}
bool cmp(edge x,edge y)
{
	return x.len>y.len;
}
void build(int x,int l,int r)
{
	t[x].l=l;
	t[x].r=r;
	if(l==r)
	{
		t[x].m=~0u>>1;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x].m=min(t[x<<1].m,t[x<<1|1].m);
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
	t[x].m=min(t[x<<1].m,t[x<<1|1].m);
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
	return min(query(x<<1,l,mid),query(x<<1|1,mid+1,r));
}
int f[maxn+10];
int s[maxn+10];
int getfa(int x)
{
	if(x!=f[x])
		f[x]=getfa(f[x]);
	return f[x];
}
void init()
{
	for(int i=1;i<=n;i++)
		s[i]=1,f[i]=i;
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
		add(e[i].x,e[i].y,e[i].len);
		add(e[i].y,e[i].x,e[i].len);
		if(s[x]>s[y])
			swap(x,y);
		f[x]=y;
		s[y]+=s[x];
	}
	for(int i=1;i<=n;i++)
		f[i]=getfa(f[i]);
}
int fa[maxn+10];
int size[maxn+10];
int depth[maxn+10];
int top[maxn+10];
int son[maxn+10];
int a[maxn+10];
int pos[maxn+10];
int cnt;
void dfs_son(int dep,int x,int F)
{
	fa[x]=F;
	size[x]=1;
	depth[x]=dep;
	for(int i=head[x];i;i=at[i].next)
		if(at[i].to!=F)
		{	
			dfs_son(dep+1,at[i].to,x);
			size[x]+=size[at[i].to];
			a[at[i].to]=at[i].len;
			son[x]=(size[at[i].to]>size[son[x]]?at[i].to:son[x]);
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
	int ans=~0u>>1;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=min(ans,query(1,pos[top[x]],pos[x]));
		x=fa[top[x]];
	}
	if(pos[x]>pos[y])
		swap(x,y);
	if(x!=y)
		ans=min(ans,query(1,pos[x]+1,pos[y]));
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
	sort(e+1,e+m+1,cmp);
	kruskal();
	for(int i=1;i<=n;i++)
		if(!v[f[i]])
		{
			dfs_son(1,f[i],0);
			dfs_top(f[i],f[i]);
			v[f[i]]=true;			
		}
	build(1,1,n);
	for(int i=1;i<=n;i++)
		if(a[i])
			modify(1,pos[i],a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(f[x]!=f[y])
		{
			puts("-1");
			continue;
		}
		if(pos[x]>pos[y])
			swap(x,y);
		printf("%d\n",process(x,y));
	}
}
