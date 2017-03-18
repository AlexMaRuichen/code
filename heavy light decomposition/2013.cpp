#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
struct segment_tree
{
	int l,r,M,sum;
}t[65536];
const int maxn=30000;
const int inf=0x7fffffff;
struct atable
{
	int to,next;
}e[10+(maxn<<1)];
int tot;
int head[maxn+10];
char query[20];
char change[]="CHANGE";
char qmax[]="QMAX";
char qsum[]="QSUM";
int a[maxn+10];
int n;
int p[maxn+10];
int depth[maxn+10];
int fa[maxn+10];
int size[maxn+10];
int son[maxn+10];
int Pos[maxn+10];
int cnt;
int top[maxn+10];
int q;
void dfs_son(int dep,int x,int F)
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
void dfs_top(int x,int T)
{
	top[x]=T;
	Pos[x]=++cnt;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs_top(e[i].to,e[i].to);
}
void add(int x,int y)
{
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
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
//	t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
//	t[x].M=max(t[x<<1].M,t[x<<1|1].M);
}
void modify(int x,int p,int v)
{
	int L=t[x].l;
	int R=t[x].r;
	if(L==R&&L==p)
	{
		t[x].sum=t[x].M=v;
		return;
	}
	int mid=(L+R)>>1;
	if(p<=mid)
		modify(x<<1,p,v);
	else
		modify(x<<1|1,p,v);
	t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
	t[x].M=max(t[x<<1].M,t[x<<1|1].M);
}
int query_max(int x,int l,int r)
{
//	if(l>r)
//		swap(l,r);
	int L=t[x].l;
	int R=t[x].r;
	if(L==l&&R==r)
		return t[x].M;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_max(x<<1,l,r);
	if(mid<l)
		return query_max(x<<1|1,l,r);
	return max(query_max(x<<1,l,mid),query_max(x<<1|1,mid+1,r));
}
int query_sum(int x,int l,int r)
{
//	if(l>r)
//		swap(l,r);
	int L=t[x].l;
	int R=t[x].r;
	if(L==l&&r==R)
		return t[x].sum;
	int mid=(L+R)>>1;
	if(mid>=r)
		return query_sum(x<<1,l,r);
	if(mid<l)
		return query_sum(x<<1|1,l,r);
	return query_sum(x<<1,l,mid)+query_sum(x<<1|1,mid+1,r);
}
int q_max(int x,int y)
{
	int ans=-inf;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans=max(ans,query_max(1,Pos[top[x]],Pos[x]));
		x=fa[top[x]];
	}
	if(Pos[x]>Pos[y])
		swap(x,y);
	ans=max(ans,query_max(1,Pos[x],Pos[y]));
	return ans;
}
int q_sum(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		ans+=query_sum(1,Pos[top[x]],Pos[x]);
		x=fa[top[x]];
	}
	if(Pos[x]>Pos[y])
		swap(x,y);
	ans+=query_sum(1,Pos[x],Pos[y]);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dfs_son(1,1,0);
	dfs_top(1,1);
	build(1,1,n);
	for(int i=1;i<=n;i++)
		modify(1,Pos[i],a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%s%d%d",query,&x,&y);
		if(!strcmp(query,change))
			modify(1,Pos[x],y);
		else if(!strcmp(query,qmax))
			printf("%d\n",q_max(x,y));
		else if(!strcmp(query,qsum))
			printf("%d\n",q_sum(x,y));
	}
}
//#include<cstdio>
//#include<cstring>
//#include<cstdlib>
//#include<iostream>
//#define inf 0x7fffffff
//#define N 30005 
//#define .M 60005
//using namespace std;
//int n,q,cnt,sz;
//int v[N],dep[N],size[N],head[N],fa[N];
//int pos[N],bl[N];
//struct data{int to,next;}e[.M];
//struct seg{int l,r,mx,sum;}t[100005];
//void insert(int u,int v)
//{
//    e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;
//    e[++cnt].to=u;e[cnt].next=head[v];head[v]=cnt;
//}
//void ini()
//{
//    scanf("%d",&n);
//    for(int i=1;i<n;i++)
//    {
//        int x,y;
//        scanf("%d%d",&x,&y);
//        insert(x,y);
//    }
//    for(int i=1;i<=n;i++)scanf("%d",&v[i]);
//}
//void dfs1(int x)
//{
//    size[x]=1;
//    for(int i=head[x];i;i=e[i].next)
//    {
//        if(e[i].to==fa[x])continue;
//        dep[e[i].to]=dep[x]+1;
//        fa[e[i].to]=x;
//        dfs1(e[i].to);
//        size[x]+=size[e[i].to];
//    }
//}
//void dfs2(int x,int chain)
//{
//    int k=0;sz++;
//    pos[x]=sz;//分配x结点在线段树中的编号
//    bl[x]=chain;
//    for(int i=head[x];i;i=e[i].next)
//        if(dep[e[i].to]>dep[x]&&size[e[i].to]>size[k])
//            k=e[i].to;//选择子树最大的儿子继承重链
//    if(k==0)return;
//    dfs2(k,chain);
//    for(int i=head[x];i;i=e[i].next)
//        if(dep[e[i].to]>dep[x]&&k!=e[i].to)
//            dfs2(e[i].to,e[i].to);//其余儿子新开重链
//}
//void build(int k,int l,int r)//建线段树
//{
//    t[k].l=l;t[k].r=r;
//    if(l==r)return;
//    int mid=(l+r)>>1;
//    build(k<<1,l,mid);
//    build(k<<1|1,mid+1,r);
//}
//void change(int k,int x,int y)//线段树单点修改
//{
//    int l=t[k].l,r=t[k].r,mid=(l+r)>>1;
//    if(l==r){t[k].sum=t[k].mx=y;return;}
//    if(x<=mid)change(k<<1,x,y);
//    else change(k<<1|1,x,y);
//    t[k].sum=t[k<<1].sum+t[k<<1|1].sum;
//    t[k].mx=max(t[k<<1].mx,t[k<<1|1].mx);
//}
//int querysum(int k,int x,int y)//线段树区间求和
//{
//    int l=t[k].l,r=t[k].r,mid=(l+r)>>1;
//    if(l==x&&y==r)return t[k].sum;
//    if(y<=mid)return querysum(k<<1,x,y);
//    else if(x>mid)return querysum(k<<1|1,x,y);
//    else {return querysum(k<<1,x,mid)+querysum(k<<1|1,mid+1,y);}
//}
//int querymx(int k,int x,int y)//线段树区间求最大值
//{
//     
//    int l=t[k].l,r=t[k].r,mid=(l+r)>>1;
//    if(l==x&&y==r)return t[k].mx;
//    if(y<=mid)return querymx(k<<1,x,y);
//    else if(x>mid)return querymx(k<<1|1,x,y);
//    else {return max(querymx(k<<1,x,mid),querymx(k<<1|1,mid+1,y));}
//}
//int solvesum(int x,int y)
//{
//    int sum=0;
//    while(bl[x]!=bl[y])
//    {
//        if(dep[bl[x]]<dep[bl[y]])swap(x,y);
//        sum+=querysum(1,pos[bl[x]],pos[x]);
//        x=fa[bl[x]];
//    }
//    if(pos[x]>pos[y])swap(x,y);
//    sum+=querysum(1,pos[x],pos[y]);
//    return sum;
//}
//int solvemx(int x,int y)
//{
//    int mx=-inf;
//    while(bl[x]!=bl[y])
//    {
//        if(dep[bl[x]]<dep[bl[y]])swap(x,y);
//        mx=max(mx,querymx(1,pos[bl[x]],pos[x]));
//        x=fa[bl[x]];
//    }
//    if(pos[x]>pos[y])swap(x,y);
//    mx=max(mx,querymx(1,pos[x],pos[y]));
//    return mx;
//}
//void solve()
//{
//    build(1,1,n);
//    for(int i=1;i<=n;i++)
//        change(1,pos[i],v[i]);
//    scanf("%d",&q);
//    char ch[10];
//    for(int i=1;i<=q;i++) 
//    {
//        int x,y;scanf("%s%d%d",ch,&x,&y);
//        if(ch[0]=='C'){v[x]=y;change(1,pos[x],y);}
//        else
//        {
//            if(ch[1]=='.M')
//               printf("%d\n",solvemx(x,y));
//            else
//                printf("%d\n",solvesum(x,y));
//        }
//    }
//}
//int main()
//{
//    ini();
//    dfs1(1);
//    dfs2(1,1);
//    solve();
//    return 0;
//}
