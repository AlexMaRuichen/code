#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=110;
int n,t,tot;
struct edge
{
	int x,y,len;
}e[maxn*maxn];
bool cmp(edge x,edge y)
{
	return x.len<y.len;
}
int fa[maxn];
int size[maxn];
int ans;
void init()
{
	for(int i=1;i<=n;i++)
		fa[i]=i,size[i]=1;
}
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void kruskal()
{
	init();
	for(int i=1;i<=tot;i++)
	{
		int x=e[i].x;
		int y=e[i].y;
		x=getfa(x);
		y=getfa(y);
		if(x==y)
			continue;
		if(size[x]>size[y])
			swap(x,y);
		ans+=e[i].len;
		size[y]+=size[x];
		fa[x]=y;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&t);
			if(j<i)
			{
				e[++tot].x=i;
				e[tot].y=j;
				e[tot].len=t;
			}
		}
	sort(e+1,e+tot+1,cmp);
	kruskal();
	printf("%d",ans);
}
