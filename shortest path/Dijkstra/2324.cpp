#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <string.h>
#include <queue>
#define lab(i,j) (((i)-1)*(n)+(j))
using namespace std;
typedef pair<int,int> point;
const int maxn=40;
point p[4*maxn*maxn*2];
int head[maxn*maxn];
int to[4*maxn*maxn*2];
int next[4*maxn*maxn*2];
int len[4*maxn*maxn*2];
int f[maxn*maxn];
int v[maxn*maxn];
int tot;
int ans;
int size;
void add(int x,int y,int z)
{
	to[++tot]=y;
	len[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	len[tot]=z;
	next[tot]=head[y];
	head[y]=tot;
}
string s,tmp;
int n,a,b;
void dijkstra(int S)
{
	memset(f,0x3f,sizeof(f));
	memset(v,0,sizeof(v));
	memset(p,0,sizeof(p));
	p[1]=point(0,S);
	size=1;
	f[S]=0;
	make_heap(p+1,p+size+1,greater<point>());
	while(size)
	{
		int x=p[1].second;
		int dis=p[1].first;
		pop_heap(p+1,p+size+1,greater<point>());
		--size;
		if(v[x])
			continue;
		v[x]=true;
		for(int i=head[x];i;i=next[i])
			if(f[to[i]]>dis+len[i])
			{
				f[to[i]]=dis+len[i];
				p[++size]=point(dis+len[i],to[i]);
				push_heap(p+1,p+size+1,greater<point>());
			}
		ans=max(ans,dis);
	}
}
int main()
{	
	scanf("%d%d%d",&n,&a,&b);
	s="0";
	for(int i=1;i<=n;i++)
	{
		cin>>tmp;
		s+=tmp;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i-1>0)
				add(lab(i,j),lab(i-1,j),s[lab(i,j)]==s[lab(i-1,j)]?a:b);
			if(i+1<=n)
				add(lab(i,j),lab(i+1,j),s[lab(i,j)]==s[lab(i+1,j)]?a:b);
			if(j-1>0)
				add(lab(i,j),lab(i,j-1),s[lab(i,j)]==s[lab(i,j-1)]?a:b);
			if(j+1<=n)
				add(lab(i,j),lab(i,j+1),s[lab(i,j)]==s[lab(i,j+1)]?a:b);
		}
	for(int i=1;i<=n*n;i++)
		dijkstra(i);
	printf("%d\n",ans);
}

