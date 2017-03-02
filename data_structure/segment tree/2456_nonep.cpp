#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cctype>
using namespace std;
const int maxn=100010;
int n,q;
int k;
int w[maxn],c[maxn];
char cc[]="CC";
char cw[]="CW";
char qs[]="QS";
char qm[]="QM";
char qu[10];
//数组
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct segment_tree
{
	int ls,rs,sum,m;
	segment_tree()
	{
		ls=rs=sum=m=0;
	}
}Tdata[20000000];
int root[100010];
inline void modify(int x,int p,int v,int l,int r)
{
	if(l==r)
	{
		Tdata[x].sum=Tdata[x].m=v;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=p)
	{
		Tdata[x].ls=Tdata[x].ls?Tdata[x].ls:++k;
		modify(Tdata[x].ls,p,v,l,mid);
	}
	else
	{
		Tdata[x].rs=Tdata[x].rs?Tdata[x].rs:++k;
		modify(Tdata[x].rs,p,v,mid+1,r);
	}
	Tdata[x].sum=Tdata[Tdata[x].ls].sum+Tdata[Tdata[x].rs].sum;
	Tdata[x].m=max(Tdata[Tdata[x].ls].m,Tdata[Tdata[x].rs].m);
}
inline int query_max(int x,int l,int r,int L,int R)
{
	if(!x)
		return 0;
	if(l==L&&R==r)
		return Tdata[x].m;
	int mid=(L+R)>>1;
	if(mid>=r)
		return Tdata[x].ls?query_max(Tdata[x].ls,l,r,L,mid):0;
	if(mid<l)
		return Tdata[x].rs?query_max(Tdata[x].rs,l,r,mid+1,r):0;
	return max(Tdata[x].ls?query_max(Tdata[x].ls,l,((l+r)>>1),L,mid):0,
			   Tdata[x].rs?query_max(Tdata[x].rs,((l+r)>>1)+1,r,mid+1,R):0);
}
inline int query_sum(int x,int l,int r,int L,int R)
{
	if(!x)
		return 0;
	if(l==L&&R==r)
		return Tdata[x].sum;
	int mid=(L+R)>>1;
	if(mid>=r)
		return Tdata[x].ls?query_sum(Tdata[x].ls,l,r,L,mid):0;
	if(mid<l)
		return Tdata[x].rs?query_sum(Tdata[x].rs,l,r,mid+1,r):0;
	return (Tdata[x].ls?query_sum(Tdata[x].ls,l,((l+r)>>1),L,mid):0)+
		   (Tdata[x].rs?query_max(Tdata[x].rs,((l+r)>>1)+1,r,mid+1,R):0);
}
struct edge
{
	int to,next;
}t[maxn*2];
int tot,head[maxn];
inline void add(int x,int y)
{
	t[++tot].to=y;
	t[tot].next=head[x];
	head[x]=tot;
}
int pos[maxn];
int fa[maxn];
int son[maxn];
int size[maxn];
int depth[maxn];
int top[maxn];
int cnt;
inline void dfs_son(int dep,int x,int F)
{
	depth[x]=dep;
	fa[x]=F;
	size[x]=1;
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=F)
		{
			dfs_son(dep+1,t[i].to,x);
			size[x]+=size[t[i].to];
			son[x]=(size[son[x]]>size[t[i].to]?son[x]:t[i].to);
		}
}
inline void dfs_top(int x,int T)
{
	top[x]=T;
	pos[x]=++cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=fa[x]&&t[i].to!=son[x])
			dfs_top(t[i].to,t[i].to);
}
inline int process_sum(int x,int y)
{
	int r=x;
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans+=query_sum(root[c[r]],pos[top[x]],pos[x],1,n);
		x=fa[top[x]];
	}
	ans+=query_sum(root[c[r]],min(pos[x],pos[y]),max(pos[x],pos[y]),1,n);
	return ans;
}
inline int process_max(int x,int y)
{
	int r=x;
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=max(ans,query_max(root[c[r]],pos[top[x]],pos[x],1,n));
		x=fa[top[x]];
	}
	ans=max(ans,query_max(root[c[r]],min(pos[x],pos[y]),max(pos[x],pos[y]),1,n));
	return ans;
}
int main()
{
	n=read();
	q=read();
	for(int i=1;i<=n;i++)
	{
		w[i]=read();
		c[i]=read();
		root[c[i]]=(root[c[i]]?root[c[i]]:++k);
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	dfs_son(1,1,0);
	dfs_top(1,1);
	for(int i=1;i<=n;i++)
		modify(root[c[i]],pos[i],w[i],1,n);
	while(q--)
	{
		int x,y;
		scanf("%s",qu);
		x=read();
		y=read();
		if(!strcmp(qu,cc))
		{
			if(c[x]!=y)
			{
				modify(root[c[x]],pos[x],0,1,n);
				modify(root[y],pos[x],w[x],1,n);
				c[x]=y;
			}
		}
		else if(!strcmp(qu,cw))
		{
			modify(root[c[x]],pos[x],y,1,n);
			w[x]=y;
		}
		else if(!strcmp(qu,qs))
			printf("%d\n",process_sum(x,y));
		else if(!strcmp(qu,qm))
			printf("%d\n",process_max(x,y));
	}
}
