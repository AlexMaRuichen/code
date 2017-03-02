#include <stdio.h>
#include <string.h>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;
const int maxn=1e4+10;
const int maxm=5e4+10;
typedef pair<int,int> point;
int n,m;
point heap[maxm];
int size;

int to[maxm];
int rto[maxm];
int next[maxm];
int rnext[maxm];
int len1[maxm];
int len2[maxm];
int head[maxn];
int rhead[maxn];
int tot;
void add(int x,int y,int a,int b)
{
	to[++tot]=y;
	len1[tot]=a;
	len2[tot]=b;
	next[tot]=head[x];
	head[x]=tot;
	rto[tot]=x;
	rnext[tot]=rhead[y];
	rhead[y]=tot;
}

int f1[maxn];
int f2[maxn];
bool v[maxn];
void dijkstra()
{
	size=0;
	memset(f1,0x3f,sizeof(f1));
	heap[++size]=point(0,n);
	f1[n]=0;
	while(size)
	{
		int x=heap[1].second;
		pop_heap(heap+1,heap+size--+1,greater<point>());
		if(v[x])
			continue;
		v[x]=true;
		for(int i=rhead[x];i;i=rnext[i])
			if(f1[rto[i]]>f1[x]+len1[i])
			{
				f1[rto[i]]=f1[x]+len1[i];
				heap[++size]=point(f1[rto[i]],rto[i]);
				push_heap(heap+1,heap+size+1,greater<point>());
			}
	}
	memset(v,0,sizeof(v));
	memset(f2,0x3f,sizeof(f2));
	heap[++size]=point(0,n);
	f2[n]=0;
	while(size)
	{
		int x=heap[1].second;
		pop_heap(heap+1,heap+size--+1,greater<point>());
		if(v[x])
			continue;
		v[x]=true;
		for(int i=rhead[x];i;i=rnext[i])
			if(f2[rto[i]]>f2[x]+len2[i])
			{
				f2[rto[i]]=f2[x]+len2[i];
				heap[++size]=point(f2[rto[i]],rto[i]);
				push_heap(heap+1,heap+size+1,greater<point>());
			}
	}
}
int f[maxn];
queue <int> q;
void spfa()
{
	memset(f,0x3f,sizeof(f));
	memset(v,0,sizeof(v));
	f[1]=0;
	v[1]=true;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(f[to[i]]>(f[x]+(len1[i]+f1[to[i]]!=f1[x]?1:0)+(len2[i]+f2[to[i]]!=f2[x]?1:0)))
			{
				f[to[i]]=(f[x]+(len1[i]+f1[to[i]]!=f1[x]?1:0)+(len2[i]+f2[to[i]]!=f2[x]?1:0));
				if(!v[to[i]])
					v[to[i]]=true,q.push(to[i]);
			}
		v[x]=false;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y,a,b;
		scanf("%d%d%d%d",&x,&y,&a,&b);
		add(x,y,a,b);
	}
	dijkstra();
	spfa();
	printf("%d\n",f[n]);
}
