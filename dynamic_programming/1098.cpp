#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n,m,K;
int t[15];
int d[15];
int e[21];
int k[21];
int ans;
void dfs(int dep,int c,int s);
int bin(int x);
void process()
{
	while(scanf("%d",&n)==1&&n)
	{
		memset(t,0,sizeof(t));
		memset(d,0,sizeof(d));
		memset(e,0,sizeof(e));
		memset(k,0,sizeof(k));
		ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d%d",&t[i],&d[i]);
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&K,&e[i]);
			for(int j=1;j<=K;j++)
			{
				int tmp;
				scanf("%d",&tmp);
				k[i]|=1<<(tmp-1);
			}
		}
		dfs(0,(1<<n)-1,0);
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("1098.in","r",stdin);
//	freopen("1098.out","w",stdout);
	process();
}
void dfs(int dep,int c,int s)
{
	ans=max(ans,s);
	if(!c)
		return;
	for(int i=1;i<=m;i++)
	{
		if((k[i]&c)==k[i])
		{
			int tmps=s+e[i];
			int tmp=k[i];
			while(tmp)
			{
				int x=bin(tmp&-tmp);
				if(t[x]-d[x]*dep<0)
					goto lableA;
				tmp-=(tmp&-tmp);
				tmps+=t[x]-d[x]*dep;
			}
			dfs(dep+1,c^k[i],tmps);
		}
		lableA:;
	}
}
int bin(int x)
{
	int tmp=0;
	while(x)
	{
		tmp++;
		x>>=1;
	}
	return tmp;
}
