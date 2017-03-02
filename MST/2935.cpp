#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2010;
struct edge
{
	int x,y,len;
}e[maxn*maxn/2];
long long ans;
bool cmp(edge x,edge y)
{
	return x.len>y.len;
}
int n;
int fa[maxn];
int size[maxn];
int a[maxn];
int tot;
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void init()
{
	for(int i=1;i<=n;i++)
		size[i]=1,fa[i]=i;
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
		ans+=e[i].len;
		if(size[x]>size[y])
			swap(x,y);
		fa[x]=y;
		size[y]+=size[x];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			e[++tot].x=i;
			e[tot].y=j;
			e[tot].len=(a[i]^a[j]);
		}
	sort(e+1,e+tot+1,cmp);
	kruskal();
	printf("%lld",ans);
}
