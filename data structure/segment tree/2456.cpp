#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
//指针	
const int maxn=100010;
int n,q;
int k;
struct segment_tree
{
	segment_tree *ls,*rs;
	int m,sum;
	segment_tree()
	{
		ls=rs=NULL;
		m=sum=0;
	}
}*root[maxn];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void modify(segment_tree* &x,int p,int v,int L,int R)
{
	if(L==p&&L==R)
	{
		x->m=x->sum=v;
		return;
	}
	int mid=(L+R)>>1;
	if(mid>=p)
	{
		if(!x->ls)
			x->ls=new segment_tree();
		modify(x->ls,p,v,L,mid);
	}
	else
	{
		if(!x->rs)
			x->rs=new segment_tree();
		modify(x->rs,p,v,mid+1,R);
	}
	static int lmax,rmax,lsum,rsum;
	lmax=x->ls?x->ls->m:0;
	rmax=x->rs?x->rs->m:0;
	lsum=x->ls?x->ls->sum:0;
	rsum=x->rs?x->rs->sum:0;
	x->m=max(lmax,rmax);
	x->sum=lsum+rsum;
}
inline int query_sum(segment_tree* &x,int l,int r,int L,int R)
{
	if(!x)
		return 0;
	if(l==L&&R==r)
		return x->sum;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_sum(x->ls,l,r,L,mid);
	if(mid<l)
		return query_sum(x->rs,l,r,mid+1,R);	
	return query_sum(x->ls,l,mid,L,mid)+query_sum(x->rs,mid+1,r,mid+1,R);
}
inline int query_max(segment_tree* &x,int l,int r,int L,int R)
{
	if(!x)
		return 0;
	if(l==L&&r==R)
		return x->m;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_max(x->ls,l,r,L,mid);
	if(mid<l)
		return query_max(x->rs,l,r,mid+1,R);
	return max(query_max(x->ls,l,mid,L,mid),query_max(x->rs,mid+1,r,mid+1,R));
}
struct edge
{
	int to,next;
}e[maxn*2];
int head[maxn],tot;
inline void add(int x,int y)
{
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
	e[++tot].to=x;
	e[tot].next=head[y];
	head[y]=tot;
}
int fa[maxn];
int son[maxn];
int size[maxn];
int depth[maxn];
int top[maxn];
int w[maxn];
int c[maxn];
int pos[maxn];
int cnt;
inline void dfs_son(int dep,int x,int F)
{
	fa[x]=F;
	size[x]=1;
	depth[x]=dep;
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=F)
		{
			dfs_son(dep+1,e[i].to,x);
			size[x]+=size[e[i].to];
			son[x]=(size[son[x]]>size[e[i].to]?son[x]:e[i].to);
		}
}
inline void dfs_top(int x,int T)
{
	top[x]=T;
	pos[x]=++cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs_top(e[i].to,e[i].to);
}
inline int process_sum(int x,int y)
{
	int r=c[x];
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans+=query_sum(root[r],pos[top[x]],pos[x],1,n);
		x=fa[top[x]];
	}
	ans+=query_sum(root[r],min(pos[x],pos[y]),max(pos[x],pos[y]),1,n);
	return ans;
}
inline int process_max(int x,int y)
{
	int r=c[x];
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=max(ans,query_max(root[r],pos[top[x]],pos[x],1,n));
		x=fa[top[x]];
	}
	ans=max(ans,query_max(root[r],min(pos[x],pos[y]),max(pos[x],pos[y]),1,n));
	return ans;
}
char qu[10];
char C[]="CC";
char W[]="CW";
char s[]="QS";
char m[]="QM";
int main()
{
	n=read();
	q=read();
	register int i;
	for(i=1;i<=n;i++)
	{
		w[i]=read();
		c[i]=read();
	}
	for(i=1;i<n;i++)
	{
		static int x,y;
		x=read();
		y=read();
		add(x,y);
	}
	dfs_son(1,1,0);
	dfs_top(1,1);
	for(i=1;i<=n;i++)
	{
		if(!root[c[i]])
			root[c[i]]=new segment_tree();
		modify(root[c[i]],pos[i],w[i],1,n);
	}
	while(q--)
	{
		static int x,y;
		scanf("%s",qu);
		x=read();
		y=read();
		if(!strcmp(qu,C))
		{
			modify(root[c[x]],pos[x],0,1,n);
			if(!root[y])
				root[y]=new segment_tree();
			modify(root[y],pos[x],w[x],1,n);
			c[x]=y;
		}
		if(!strcmp(qu,W))
		{
			modify(root[c[x	]],pos[x],y,1,n);
			w[x]=y;
		}
		if(!strcmp(qu,s))
			printf("%d\n",process_sum(x,y));
		if(!strcmp(qu,m))
			printf("%d\n",process_max(x,y));
	}
}
