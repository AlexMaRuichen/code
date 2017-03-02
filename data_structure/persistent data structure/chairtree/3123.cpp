#include <stdio.h>
#include <algorithm>
#define check (x->ls->cnt+y->ls->cnt-lca->ls->cnt-fa->ls->cnt)
using namespace std;
const int maxn=8e4+10;
const int N=1e9;
const int log=17;
struct seg_tree
{
	seg_tree *ls,*rs;
	int cnt;
}*root[maxn],mempool[20002000];
inline seg_tree* new_node(seg_tree *x,seg_tree *y,int z)
{
	static seg_tree *p=mempool;
	p->ls=x;
	p->rs=y;
	p->cnt=z;
	return p++;
}
inline seg_tree* build(seg_tree *x,int y,int l,int r)
{
	if(l==r)
		return new_node(NULL,NULL,x->cnt+1);
	int mid=l+r>>1;
	if(mid>=y)
		return new_node(build(x->ls,y,l,mid),x->rs,x->cnt+1);
	else
		return new_node(x->ls,build(x->rs,y,mid+1,r),x->cnt+1);
}
inline int query(seg_tree *x,seg_tree *y,seg_tree *lca,seg_tree *fa,int k,int l,int r)
{
	if(l==r)
		return l;
	int mid=l+r>>1;
	if(check>=k)
		return query(x->ls,y->ls,lca->ls,fa->ls,k,l,mid);
	else
		return query(x->rs,y->rs,lca->rs,fa->rs,k-check,mid+1,r);
}

int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
inline void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}

int a[maxn];
int fa[log+1][maxn];
int dep[maxn];
inline void dfs(int x)
{
	dep[x]=dep[fa[0][x]]+1;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	root[x]=build(root[fa[0][x]],a[x],0,N);
	for(int i=head[x];i;i=next[i])
		if(to[i]!=fa[0][x])
		{
			fa[0][to[i]]=x;
			dfs(to[i]);
		}
}
inline int getfa(int x,int y)
{
	for(int i=0;i<=log;i++)
		if(y&(1<<i))
			x=fa[i][x];
	return x;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	x=getfa(x,dep[x]-dep[y]);
	if(x==y)
		return x;
	for(int i=log;i>=0;i--)
		if(fa[i][x]!=fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}

int n,m,t;
namespace dju
{
	int fa[maxn];
	int size[maxn];
	int fx,fy;
	inline void init()
	{
		for(int i=1;i<=n;i++)
			fa[i]=i,size[i]=1;
	}
	inline int getfa(int x)
	{
		if(fa[x]!=x)
			fa[x]=getfa(fa[x]);
		return fa[x];
	}
	inline void merge(int x,int y)
	{
		fx=getfa(x);
		fy=getfa(y);
		fa[fx]=fy;
		size[fy]+=size[fx];
	}
}
int main()
{
	scanf("%*d%d%d%d",&n,&m,&t);
	dju::init();
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		dju::merge(x,y);
	}
	root[0]=new_node(mempool,mempool,0);
	for(int i=1;i<=n;i++)
		if(!fa[0][i])
			dfs(i);
	while(t--)
	{
		static char s[10];
		static int x,y,k,lastans,lca;
		scanf("%s",s);
		if(s[0]=='Q')
		{
			scanf("%d%d%d",&x,&y,&k);
			x^=lastans;
			y^=lastans;
			k^=lastans;
			lca=LCA(x,y);
			printf("%d\n",lastans=query(root[x],root[y],root[lca],root[fa[0][lca]],k,0,N));
		}
		else if(s[0]=='L')
		{
			scanf("%d%d",&x,&y);
			x^=lastans;
			y^=lastans;
			if(dju::size[dju::getfa(x)]>dju::size[dju::getfa(y)])
				swap(x,y);
			dju::merge(x,y);
			fa[0][x]=y;
			dfs(x);
			add(x,y);
		}
	}
}
