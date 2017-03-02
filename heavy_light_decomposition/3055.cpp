#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,k;
struct atable
{
	int to,next;
}t[maxn*2];
int head[maxn],tot;
void add(int x,int y)
{
	t[++tot].to=y;
	t[tot].next=head[x];
	head[x]=tot;
}
int top[maxn];
int son[maxn];
int size[maxn];
int fa[maxn];
int depth[maxn];
bool cnt[maxn];
void dfs_son(int dep,int x,int F)
{
	size[x]=1;
	fa[x]=F;
	depth[x]=dep;
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=F)
		{
			dfs_son(dep+1,t[i].to,x);
			size[x]+=size[t[i].to];
			son[x]=(size[son[x]]>size[t[i].to]?son[x]:t[i].to);
		}
}
void dfs_top(int x,int T)
{
	top[x]=T;
	if(son[x])
		dfs_top(son[x],T);
	for(int i=head[x];i;i=t[i].next)
		if(t[i].to!=son[x]&&t[i].to!=fa[x])
			dfs_top(t[i].to,t[i].to);
}
int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	return depth[x]<depth[y]?x:y;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		cnt[y]=true;
	}
	for(int i=1;i<=n;i++)
		if(!cnt[i])
		{
			dfs_son(1,i,0);
			dfs_top(i,i);
			break;
		}
	while(k--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
}
