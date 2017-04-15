#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
#define lab(i,j) ((i-1)*n+j)
#define judge(x,y) ((x)>=1&&(x)<=n&&(y)>=1&&(y)<=n&&!map[x][y])
using namespace std;
const int maxn=200*200+10;
const int maxm=maxn*10;
const int inf=1e9;

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

int S=40005,T=40006;
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

int n,m;
int dx[]={-2,-1, 1, 2, 2, 1,-1,-2};
int dy[]={ 1, 2, 2, 1,-1,-2,-2,-1};
bool map[210][210];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if((i+j)&1)
				add(S,lab(i,j),1);
			else
				add(lab(i,j),T,1);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=true;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(((i+j)&1)&&!map[i][j])
				for(int k=0;k<8;k++)
					if(judge(i+dx[k],j+dy[k]))
						add(lab(i,j),lab(i+dx[k],j+dy[k]),inf);
	printf("%d\n",n*n-m-dinic());
}
