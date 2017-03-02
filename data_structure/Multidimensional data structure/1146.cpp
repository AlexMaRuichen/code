#include <stdio.h>
#include <algorithm>
#define lowbit(x) (x)&(-x)
using namespace std;
const int maxn=80010;
struct seg
{
	seg *ls,*rs;
	int val;
	void* operator new(size_t)
	{
		static seg *l,*r;
		if(l==r)
			r=(l=new seg[1<<15])+(1<<15);
		return l++;
	}
}*root[maxn<<1];
int query(seg *x,int p,int l,int r)
{
	if(!x)
		return 0;
	if(!x->val)
		return 0;
	if(l==r)
		return x->val;
	int mid=l+r>>1;
	if(mid>=p)
		return query(x->ls,p,l,mid);
	else
		return (x->ls?x->ls->val:0)+query(x->rs,p,mid+1,r);
}
void insert(seg *&x,int p,int v,int l,int r)
{
	if(!x)
		x=new seg();
	x->val+=v;
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(mid>=p)
		insert(x->ls,p,v,l,mid);
	else
		insert(x->rs,p,v,mid+1,r);
}
struct edge
{
	int to;
	edge *next;
	edge(){}
	edge(int to,edge *next):to(to),next(next){}
	void* operator new(size_t)
	{
		static edge *l,*r;
		if(l==r)
			r=(l=new edge[1<<15])+(1<<15);
		return l++;
	}
}*head[maxn];
void add(int x,int y)
{
	head[x]=new edge(y,head[x]);
	head[y]=new edge(x,head[y]);
}
const int log=17;
int fa[log+1][maxn];
int dep[maxn];
int b[maxn];
int e[maxn];
int cnt;
void dfs(int x)
{
	b[x]=++cnt;
	dep[x]=dep[fa[0][x]]+1;
	for(int i=1;i<=log;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	for(edge *p=head[x];p;p=p->next)
		if(p->to^fa[0][x])
			fa[0][p->to]=x,
			dfs(p->to);
	e[x]=++cnt;
}
int get(int x,int y)
{
	for(int i=0;i<=log;i++)
		if(y&(1<<i))
			x=fa[i][x];
	return x;
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	x=get(x,dep[x]-dep[y]);
	if(x==y)
		return x;
	for(int i=log;~i;i--)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],
			y=fa[i][y];
	return fa[0][x];
}
int n,q;
int calc(int x,int y)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=query(root[i],y,0,n);
	return ans;
}
int query(int x,int y,int k)
{
	int l=0,r=n+10,mid;
	int lca=LCA(x,y),f=fa[0][lca];
	while(l<r)
	{
		mid=l+r>>1;
		if(calc(b[x],mid)+calc(b[y],mid)-calc(b[lca],mid)-calc(b[f],mid)>=k)
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
void insert(int x,int y)
{
	for(int i=x;i<=cnt;i+=lowbit(i))
		insert(root[i],y,1,1,n);
}
void del(int x,int y)
{
	for(int i=x;i<=cnt;i+=lowbit(i))
		insert(root[i],y,-1,1,n);
}
int a[maxn];
int opt[maxn];
int x[maxn];
int y[maxn];
int main()
{

	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		insert(b[i],a[i]);
		del(e[i],a[i]);
	}
	for(int i=1;i<=q;i++)
	{
		int opt,x,y,t;
		scanf("%d%d%d",&opt,&x,&y);
		if(!opt)
		{
			del(b[x],a[x]);
			insert(e[x],a[x]);
			insert(b[x],y);
			del(e[x],y);
			a[x]=y;
		}
		else
			(t=query(x,y,opt))>n?puts("invalid request!"):printf("%d\n",t);
	}
}
