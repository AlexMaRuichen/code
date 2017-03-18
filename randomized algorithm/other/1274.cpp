#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=310;
const int mt=150000;
int to[maxn*2];
int next[maxn*2];
int f[maxn*2];
int head[maxn];
int depth[maxn][maxn];
int tot;
int t;
int ans=~0u>>1;
int tmp;
int n,p;
int maxdep;
int cnt[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}
void dfs(int dep,int x,int F)
{
	maxdep=max(dep,maxdep);
	for(int i=head[x];i;i=next[i])
		if(to[i]!=F)
		{
			cnt[dep]++;
			depth[dep][cnt[dep]]=i;
			dfs(dep+1,to[i],x);	
		}
}
void randomized(int dep)
{
	if(dep==maxdep)
		return;
	int t=rand()%cnt[dep]+1;
	f[depth[dep][t]]=1;
	randomized(dep+1);
}
void check(int x,int F)
{
	tmp++;
	for(int i=head[x];i;i=next[i])
		if(to[i]!=F&&!f[i])
			check(to[i],x);
}
int main()
{
	srand(20150227);
	rand();
	scanf("%d%d",&n,&p);
	for(int i=1;i<=p;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,1,0);
	while(t<mt)
	{
		tmp=0;
		memset(f,0,sizeof(f));
		randomized(1);
		check(1,0);
		ans=min(tmp,ans);
		t++;
	}
	printf("%d\n",ans);
}
