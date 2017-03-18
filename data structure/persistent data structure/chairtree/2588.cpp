#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
const int log=17;
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
	seg_tree()
	{
		ls=rs=NULL;
		cnt=0;
	}
	void* operator new(size_t);
}*root[maxn],Tdata[maxn*20];
void* seg_tree :: operator new(size_t)
{
	static seg_tree *p=Tdata;
	return p++;
}
int n,m;
void build(seg_tree* &x,int l,int r)
{
	x=new seg_tree();
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(x->ls,l,mid);
	build(x->rs,mid+1,r);
}
int a[maxn];
int b[maxn];
void insert(seg_tree* &x,seg_tree *y,int v,int l,int r)
{
	x=new seg_tree();
	x->cnt=y->cnt+1;
	if(l==r)
		return;
	x->ls=y->ls;
	x->rs=y->rs;
	int mid=(l+r)>>1;
	if(mid>=v)
		insert(x->ls,y->ls,v,l,mid);
	else
		insert(x->rs,y->rs,v,mid+1,r);
}
int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}
int fa[log+1][maxn];
int depth[maxn];
void dfs(int x)
{
	insert(root[x],root[fa[0][x]],a[x],1,n);
	depth[x]=depth[fa[0][x]]+1;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa[0][x])
		{
			fa[0][to[i]]=x;
			dfs(to[i]);
		}
}
int getfa(int x,int y)
{
	for(int i=0;i<=log;i++)
		if((1<<i)&y)
			x=fa[i][x];
	return x;
}
int lca(int x,int y)
{
	if(depth[x]<depth[y])
		swap(x,y);
	x=getfa(x,depth[x]-depth[y]);
	if(x==y)
		return x;
	for(int i=log;i>=0;i--)
		if(fa[i][x]!=fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
int process(int x,int y,int k)
{
	int LCA=lca(x,y),FLCA=fa[0][LCA];
	int l=1,r=n;
	seg_tree *a=root[x],*b=root[y],*c=root[LCA],*d=root[FLCA];
	while(l<r)
	{
		int mid=(l+r)>>1;
		int sum=a->ls->cnt+b->ls->cnt-c->ls->cnt-d->ls->cnt;
		if(sum>=k)
			a=a->ls,b=b->ls,c=c->ls,d=d->ls,r=mid;
		else
			a=a->rs,b=b->rs,c=c->rs,d=d->rs,l=mid+1,k-=sum;
	}
	return l;
}
int main()
{
//	freopen("a.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	build(root[0],1,n);
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	int lastans=0;
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x^=lastans;
		printf("%d",lastans=b[process(x,y,z)]);
		if(i!=m)
			puts("");
	}
}
