#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=100010;
int to[2*maxn];
int next[2*maxn];
int head[maxn];
int tot;
char opt[10];	
bool x[maxn];
int a;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}
int b[maxn];
int e[maxn];
int bit[2*maxn];
int n,m;
int cnt;
void modify(int x,int y)
{
	for(int i=x;i<=cnt;i+=lowbit(i))
		bit[i]+=y;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
void dfs(int x,int f)
{
	b[x]=++cnt;
	for(int i=head[x];i;i=next[i])
		if(to[i]!=f)
			dfs(to[i],x);
	e[x]=++cnt;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		modify(e[i],1),x[i]=true;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s%d",opt,&a);
		if(opt[0]=='Q')
			printf("%d\n",query(e[a])-query(b[a]));
		else if(opt[0]=='C')
		{
			if(x[a])
			{
				modify(e[a],-1);
				x[a]=false;
			}
			else
			{
				modify(e[a],1);
				x[a]=true;
			}
		}
	}
}
