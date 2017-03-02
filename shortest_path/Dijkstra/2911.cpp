#include <stdio.h>
#include <functional>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=40010;
typedef pair<int,int> point;
point heap[maxn<<1];
int b,e,p,n,m;

int to[maxn<<1];
int next[maxn<<1];
int head[maxn];
int tot;
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	next[tot]=head[y];
	head[y]=tot;
}

int f[4][maxn];
int size;
bool v[maxn];
void dijkstra()
{
	memset(f,0x3f,sizeof(f));
	memset(v,0,sizeof(v));
	heap[++size]=point(0,1);
	f[1][1]=0;
	while(size)
	{
		int x=heap[1].second;
		pop_heap(heap+1,heap+size--+1,greater<point>());
		if(v[x])
			continue;
		v[x]=true;
		for(int i=head[x];i;i=next[i])
			if(f[1][to[i]]>f[1][x]+1)
			{
				f[1][to[i]]=f[1][x]+1;
				heap[++size]=point(f[1][to[i]],to[i]);
				push_heap(heap+1,heap+size+1,greater<point>());
			}
	}

	memset(v,0,sizeof(v));
	heap[++size]=point(0,2);
	f[2][2]=0;
	while(size)
	{
		int x=heap[1].second;
		pop_heap(heap+1,heap+size--+1,greater<point>());
		if(v[x])
			continue;
		v[x]=true;
		for(int i=head[x];i;i=next[i])
			if(f[2][to[i]]>f[2][x]+1)
			{
				f[2][to[i]]=f[2][x]+1;
				heap[++size]=point(f[2][to[i]],to[i]);
				push_heap(heap+1,heap+size+1,greater<point>());
			}
	}

	memset(v,0,sizeof(v));
	heap[++size]=point(0,n);
	f[3][n]=0;
	while(size)
	{
		int x=heap[1].second;
		pop_heap(heap+1,heap+size--+1,greater<point>());
		if(v[x])
			continue;
		v[x]=true;
		for(int i=head[x];i;i=next[i])
			if(f[3][to[i]]>f[3][x]+1)
			{
				f[3][to[i]]=f[3][x]+1;
				heap[++size]=point(f[3][to[i]],to[i]);
				push_heap(heap+1,heap+size+1,greater<point>());
			}
	}
}
int ans=~0u>>1;
int main()
{
	scanf("%d%d%d%d%d",&b,&e,&p,&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dijkstra();
	for(int i=1;i<=n;i++)
		ans=min(ans,b*f[1][i]+e*f[2][i]+p*f[3][i]);
	printf("%d\n",ans);
}
