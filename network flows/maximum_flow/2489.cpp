#include <stdio.h>
#include <algorithm>
#include <queue>
#include <set>
#include <string.h>
using namespace std;
const int maxn=120;
int m,n;
int to[maxn*maxn];
int next[maxn*maxn];
int len[maxn*maxn];
char s[5000];
int head[maxn];
int tot=1;
queue <int> q;
set <int> s1,s2;
void add(int x,int y,int z)
{
	to[++tot]=y;
	len[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	len[tot]=0;
	next[tot]=head[y];
	head[y]=tot;
}
int depth[maxn];
int S,T;
bool bfs()
{
	memset(depth,-1,sizeof(depth));
	q.push(S);
	depth[S]=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&depth[to[i]]<0)
				depth[to[i]]=depth[x]+1,q.push(to[i]);
	}
	return depth[T]!=-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(int i=head[x];i;i=next[i])
		if(len[i]&&depth[to[i]]==depth[x]+1)
		{
			w=dfs(to[i],min(len[i],f-used));
			len[i]-=w;
			len[i^1]+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used!=f)
		depth[x]=-1;
	return used;
}
int ans;
void dinic()
{
	while(bfs())
		ans-=dfs(S,~0u>>1);
}
int main()
{
	scanf("%d%d",&m,&n);
	S=0,T=n+m+1;
	int x;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);  
		add(S,i,x);  
		ans+=x; 
		char c;
		for (;;)
		{  
			while((c=getchar())==' ');
				ungetc(c,stdin);  
			if(c==10||c==13)
				break;  
			scanf("%d",&x);  
			add(i,x+m,~0u>>1);  
        }  
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		add(i+m,T,x);
	}
	dinic();
	for(int i=1;i<=m;i++)
		if(depth[i]!=-1)
		{
			if(i==1)
				printf("%d",i);
			else
				printf(" %d",i);
		}
	puts("");
	for(int i=m+1;i<=n+m;i++)
		if(depth[i]!=-1)
		{
			if(i==m+1)
				printf("%d",i-m);
			else
				printf(" %d",i-m);
		}
	printf("\n%d\n",ans);
}
