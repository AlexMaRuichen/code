#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=10010;
int n,k;

int to[maxn<<1];
int next[maxn<<1];
int len[maxn<<1];
bool ban[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y,int z)
{
	to[++tot]=x;
	next[tot]=head[y];
	ban[tot]=false;
	len[tot]=z;
	head[y]=tot;
	
	to[++tot]=y;
	next[tot]=head[x];
	ban[tot]=false;
	len[tot]=z;
	head[x]=tot;
}

int size[maxn];
int fa[maxn];
int dep[maxn];
int get(int x,int s)
{
	int ans=0;
	bool flag=true;
	size[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]!=fa[x])
		{
			fa[to[i]]=x;
			ans=max(get(to[i],s),ans);
			if(size[to[i]]>s>>1)
				flag=false;
			size[x]+=size[to[i]];
		}
	if(s-size[x]>s>>1)
		flag=false;
	return flag?x:ans;
}
void dfs(int x,int dis=0)
{
	dep[x]=dis;
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]^fa[x])
			fa[to[i]]=x,dfs(to[i],dis+len[i]);
}
int a[maxn];
void push(int x)
{
	a[++a[0]]=dep[x];
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]!=fa[x])
			push(to[i]);
}
int calc(int x)
{
	a[0]=0;
	push(x);
	sort(a+1,a+a[0]+1);
	int l=1,r=a[0],ans=0;
	while(l<=a[0])
	{
		while(r&&a[r]+a[l]>k)
			--r;
		ans+=r;
		++l;
	}
	return ans;
}
int partition(int x,int s)
{
	int ans=0;
	fa[x]=0;
	x=get(x,s);
	size[fa[x]]=s-size[x];
	fa[x]=0;
	dfs(x);
	ans+=calc(x);
	for(int i=head[x];i;i=next[i])
		if(!ban[i])
			ans-=calc(to[i]);
	for(int i=head[x];i;i=next[i])
		if(!ban[i])
			ban[i]=ban[i^1]=true,ans+=partition(to[i],size[to[i]]);
	return ans;
}
int main()
{
	while(scanf("%d%d",&n,&k)==2&&(n|k))
	{
		memset(head,0,sizeof(head));
		tot=1;
		for(int i=1;i<n;i++)
		{
			static int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
		}
		printf("%d\n",partition(1,n)-n>>1);
	}
}
