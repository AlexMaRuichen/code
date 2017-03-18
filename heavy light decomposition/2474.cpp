#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int a[300010];
int size[300010];
struct edge
{
	int to,next;
}t[600010];
int depth[300010];
int head[300010],tot;
void dfs_son(int dep,int x,int F);
void dfs_top(int x,int T);
void process(int x,int y);
int fa[300010];
int top[300010];
void add(int x,int y);
int son[300010];
int dif[300010];
void solve(int x);
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs_son(1,a[1],0);
	dfs_top(a[1],a[1]);
	for(int i=1;i<n;i++)
	{
		int x=a[i];
		int y=a[i+1];
		process(x,y);
	}
	solve(a[1]);
	dif[a[1]]++;
	for(int i=1;i<=n;i++)
		dif[a[i]]--;
	for(int i=1;i<=n;i++)
		printf("%d\n",dif[i]);
}
void solve(int x)
{
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=fa[x])
		{
			solve(t[i].to);
			dif[x]+=dif[t[i].to];
		}
}
void process(int x,int y)
{
	dif[x]++;
	dif[y]++;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	int lca=(depth[x]<depth[y]?x:y);
	dif[lca]--;
	dif[fa[lca]]--;
}
void add(int x,int y)
{
	t[++tot].to=y;
	t[tot].next=head[x];
	head[x]=tot;
}
void dfs_top(int x,int T)
{	
	top[x]=T;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=fa[x]&&t[i].to!=son[x])
			dfs_top(t[i].to,t[i].to);
}
void dfs_son(int dep,int x,int F)
{
	depth[x]=dep;
	size[x]=1;
	fa[x]=F;
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=F)
		{
			dfs_son(dep+1,t[i].to,x);
			size[x]+=size[t[i].to];
			son[x]=(size[t[i].to]>size[son[x]]?t[i].to:son[x]);
		}
}
//#include<iostream>
//#include<cstdio>
//#include<cstring>
//#include<cstdlib>
//#include<algorithm>
//#include<cmath>
//#include<set>
//#define inf 1000000000
//#define ll long long
//using namespace std;
//inline int read()
//{
//	int x=0,f=1;char ch=getchar();
//	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//	return x*f;
//}
//int bin[20];
//int n,cnt;
//int fa[300005][20];
//int a[300005],f[300005],last[300005],deep[300005];
//struct edge{int to,next;}e[600005];
//void insert(int u,int v)
//{
//	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
//	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;
//}
//void dfs(int x)
//{
//	for(int i=1;i<=18;i++)
//		if(deep[x]>=bin[i])
//			fa[x][i]=fa[fa[x][i-1]][i-1];
//		else break;
//	for(int i=last[x];i;i=e[i].next)
//		if(e[i].to!=fa[x][0])
//		{
//			deep[e[i].to]=deep[x]+1;
//			fa[e[i].to][0]=x;
//			dfs(e[i].to);
//		}
//}
//int lca(int x,int y)
//{
//	if(deep[x]<deep[y])swap(x,y);
//	int t=deep[x]-deep[y];
//	for(int i=0;i<=18;i++)
//		if(bin[i]&t)x=fa[x][i];
//	for(int i=18;i>=0;i--)
//		if(fa[x][i]!=fa[y][i])
//			x=fa[x][i],y=fa[y][i];
//	if(x==y)return x;
//	return fa[x][0];
//}
//void dp(int x)
//{
//	for(int i=last[x];i;i=e[i].next)
//		if(e[i].to!=fa[x][0])
//		{
//			dp(e[i].to);
//			f[x]+=f[e[i].to];
//		}
//}
//void solve()
//{
//	dfs(a[1]);
//    for(int i=1;i<n;i++)
//	{
//		int t=lca(a[i],a[i+1]);
//		f[a[i]]++;f[a[i+1]]++;
//		f[t]--;f[fa[t][0]]--;
//	}
//    dp(a[1]);
//	for(int i=2;i<=n;i++)f[a[i]]--;
//	for(int i=1;i<=n;i++)printf("%d\n",f[i]);
//}
//int main()
//{
//	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
//	n=read();
//	for(int i=1;i<=n;i++)a[i]=read();
//	for(int i=1;i<n;i++)
//	{
//		int u=read(),v=read();
//		insert(u,v);
//	}
//	solve();
//	return 0;
//}
