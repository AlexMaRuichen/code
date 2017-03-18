#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> point;
const int maxn=10010;
const int maxm=50010;
int to[maxm*2];
int next[maxm*2];
int len[maxm*2];
int head[maxn];
int f[6][maxn];
int n,m,k;
int market[10];
bool ismarket[maxn];
int ans=~0u>>1,tmp;
priority_queue <point,vector <point>,greater <point> > pq;
void add(int x,int y,int z)
{
	to[++tmp]=y;
	len[tmp]=z;
	next[tmp]=head[x];
	head[x]=tmp;
	to[++tmp]=x;
	len[tmp]=z;
	next[tmp]=head[y];
	head[y]=tmp;
}
void dijkstra(int S)
{
	f[S][market[S]]=0;
	pq.push(make_pair(0,market[S]));
	while(!pq.empty())
	{
		int x=pq.top().second;
		int dis=pq.top().first;
		pq.pop();
		if(f[S][x]<dis)	
			continue;
		f[S][x]=dis;
		for(int i=head[x];i;i=next[i])
			if(f[S][to[i]]>f[S][x]+len[i])
				pq.push(point(f[S][x]+len[i],to[i]));
	}
}
int x[10];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&market[i]);
		ismarket[market[i]]=true;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	for(int i=1;i<=k;i++)
	{
		memset(f[i],0x3f,sizeof(f[i]));
		dijkstra(i);
	}
	for(int i=1;i<=k;i++)
		x[i]=i;
	do
	{
		tmp=~0u>>1;
		for(int i=1;i<=n;i++) 
			if(!ismarket[i])
				tmp=min(tmp,f[x[1]][i]+f[x[k]][i]);
		for(int i=2;i<=k;i++)
			tmp+=f[x[i-1]][market[x[i]]];
		ans=min(ans,tmp);
	}
	while(next_permutation(x+1,x+k+1));
	printf("%d\n",ans);
}
