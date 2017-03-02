#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define judge(a,b) (((a)>=1)&&((a)<=n)&&((b)>=1)&&((b)<=m))
#define lab(a,b) (((a)-1)*m+(b))
using namespace std;
const int maxn=910;
const int maxm=maxn*10;
const int inf=~0u>>1;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int to[maxm];
int next[maxm];
int len[maxm];
int head[maxn];
int tot=1;
void add(int x,int y,int z)
{
	to[++tot]=y;
	next[tot]=head[x];
	len[tot]=z;
	head[x]=tot;
	
	to[++tot]=x;
	next[tot]=head[y];
	len[tot]=0;
	head[y]=tot;
}

int S,T=905;
int dep[maxn];
queue <int> q;
bool bfs()
{
	q.push(S);
	memset(dep,-1,sizeof(dep));
	dep[S]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(len[i]&&dep[to[i]]==-1)
				dep[to[i]]=dep[x]+1,q.push(to[i]);
	}
	return dep[T]^-1;
}
int dfs(int x,int f)
{
	if(x==T)
		return f;
	int w,used=0;
	for(int i=head[x];i;i=next[i])
		if(len[i]&&dep[to[i]]==dep[x]+1)
		{
			w=dfs(to[i],min(len[i],f-used));
			len[i]-=w;
			len[i^1]+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(used^f)
		dep[x]=-1;
	return used;
}
int dinic()
{
	int ans=0;
	while(bfs())
		ans+=dfs(S,inf);
	return ans;
}
int n,m,sum;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			static int x;
			scanf("%d",&x);
			sum+=x;
			if((i+j)&1)
			{
				add(S,lab(i,j),x);
				for(int k=0;k<4;k++)
					if(judge(i+dx[k],j+dy[k]))
						add(lab(i,j),lab(i+dx[k],j+dy[k]),inf);
			}
			else
				add(lab(i,j),T,x);
		}
	printf("%d\n",sum-dinic());
}
