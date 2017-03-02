#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int tot;
const int maxn=110;
struct edge
{
	int x,y,len;
}e[maxn*(maxn-1)/2];
bool cmp(edge a,edge b)
{
	return a.len<b.len;
}
int fa[maxn];
int size[maxn];
int n,m;
int ans=~0u>>1;
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void init()
{
	for(int i=1;i<=n;i++)
		fa[i]=i,size[i]=1;
}
void kruskal(int x)
{
	init();
	int maxlen;
	for(int i=x;i<=m;i++)
	{
		int a=e[i].x;
		int b=e[i].y;
		a=getfa(a);
		b=getfa(b);
		if(a==b)
			continue;
		if(size[a]>size[b])
			swap(a,b);
		fa[a]=b;
		size[b]+=size[a];
		maxlen=e[i].len;
	}
	int s=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==i)
			s++;
	if(s==1)
		ans=min(ans,maxlen-e[x].len);
	return;
}
int main()
{
//	scanf("%d",&tot);
//	while(tot--)
//	{
		ans=~0u>>1;
		memset(e,0,sizeof(e));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
		sort(e+1,e+m+1,cmp);
		for(int i=1;i<=m;i++)
			kruskal(i);
		if(ans!=~0u>>1)
			printf("%d\n",ans);		
		else
			puts("-1");
//	}
}
