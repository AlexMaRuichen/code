#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=10010;
const int maxm=200010;
int n,m;
int S,T;

int tot;
int to[maxm];
int next[maxm];
int head[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}

int rtot;
int rto[maxm];
int rnext[maxm];
int rhead[maxn];
void radd(int x,int y)
{
	rto[++rtot]=x;
	rnext[rtot]=rhead[y];
	rhead[y]=rtot;
}

queue <int> q;
bool avl[maxn];
void reverse_bfs()
{
	q.push(T);
	avl[T]=true;
	while(!q.empty())
	{
		static int x;
		x=q.front();
		q.pop();
		for(int i=rhead[x];i;i=rnext[i])
			if(!avl[rto[i]])
				avl[rto[i]]=true,q.push(rto[i]);
	}
}

int f[maxn];
bool v[maxn];
void bfs()
{
	q.push(S);
	v[S]=true;
	for(int i=1;i<=n;i++)
		f[i]=~0u>>1;
	f[S]=0;
	while(!q.empty())
	{
		static int x;
		x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(!avl[to[i]])
				goto lableA;
		for(int i=head[x];i;i=next[i])
		{
			f[to[i]]=min(f[to[i]],f[x]+1);
			if(!v[to[i]])
				q.push(to[i]),v[to[i]]=true;
		}
		lableA:;
	}
	if(f[T]==~0u>>1)
		puts("-1");
	else
		printf("%d\n",f[T]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		radd(x,y);
	}
	scanf("%d%d",&S,&T);

	reverse_bfs();
	bfs();
}
