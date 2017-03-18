#include <stdio.h>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e6+10;
int n,m;
struct Adjacency_List
{
	int to[maxm];
	int next[maxm];
	int head[maxn];
	int tot;
	void add(int x,int y)
	{
		to[++tot]=y;
		next[tot]=head[x];
		head[x]=tot;
	}
}G,R;
queue <int> q;
int f[maxn];
int g[maxn];
int a[maxn];
bool v[maxn];
void spfa()
{
	memset(f,0x3f,sizeof(f));
	q.push(1);
	v[1]=true;
	f[1]=a[1];
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=G.head[x];i;i=G.next[i])
			if(f[G.to[i]]>f[x]||f[G.to[i]]>a[G.to[i]])
			{
				f[G.to[i]]=min(f[x],a[G.to[i]]);
				if(!v[G.to[i]])
					q.push(G.to[i]),v[G.to[i]]=true;
			}
		v[x]=false;
	}
	memset(v,0,sizeof(v));
	q.push(n);
	v[n]=true;
	g[n]=a[n];
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=R.head[x];i;i=R.next[i])
			if(g[R.to[i]]<g[x]||g[R.to[i]]<a[R.to[i]])
			{
				g[R.to[i]]=max(g[x],a[R.to[i]]);
				if(!v[R.to[i]])
					q.push(R.to[i]),v[R.to[i]]=true;
			}
		v[x]=false;
	}
}
int ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G.add(x,y);
		R.add(y,x);
		if(z==2)
			G.add(y,x),R.add(x,y);
	}
	spfa();		
	for(int i=1;i<=n;i++)
		ans=max(ans,g[i]-f[i]);
	printf("%d\n",ans);
}
