#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=20010;

int to[maxn<<1];
int next[maxn<<1];
int len[maxn<<1];
int head[maxn];
bool ban[maxn];
int tot=1;
inline void add(int x,int y,int z)
{
	to[++tot]=y;
	len[tot]=z;
	next[tot]=head[x];
	ban[tot]=false;
	head[x]=tot;
	
	to[++tot]=x;
	len[tot]=z;
	next[tot]=head[y];
	ban[tot]=false;
	head[y]=tot;
}

int dep[maxn];
int fa[maxn];
int size[maxn];
int f[3][maxn];
inline int get(int x,int s)
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
inline void dfs(int root,int x,int dis)
{
	size[x]=1;
	++f[dis][root];
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]!=fa[x])
		{
			fa[to[i]]=x;
			dfs(root,to[i],(dis+len[i])%3);
			size[x]+=size[to[i]];
		}
}
inline int calc(int x)
{
	int ans=0;
	f[0][x]=1;
	f[1][x]=0;
	f[2][x]=0;
	size[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]!=fa[x])
		{
			fa[to[i]]=x;
			f[0][to[i]]=f[1][to[i]]=f[2][to[i]]=0;
			dfs(to[i],to[i],len[i]);
			ans+=f[0][x]*f[0][to[i]];
			ans+=f[1][x]*f[2][to[i]];
			ans+=f[2][x]*f[1][to[i]];
			f[0][x]+=f[0][to[i]];
			f[1][x]+=f[1][to[i]];
			f[2][x]+=f[2][to[i]];
		}
	return ans;
}
inline int partition(int x,int s)
{
	x=get(x,s);
	fa[x]=0;
	int ans=calc(x);
	for(int i=head[x];i;i=next[i])
		if(!ban[i]&&to[i]!=fa[x])
		{
			ban[i]=ban[i^1]=true;
			ans+=partition(to[i],size[to[i]]);
		}
	return ans;
}
inline int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z%3);
	}
	int up=partition(20150227%n+1,n)*2+n,down=n*n,GCD=gcd(up,down);
	printf("%d/%d\n",up/GCD,down/GCD);
}
