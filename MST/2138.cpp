#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=20010;
int n;
long long ans;
struct edge
{
	int x,y;
	long long len;
}e[maxn];
bool cmp(edge x,edge y)
{
	return x.len<y.len;
}
int fa[maxn];
int size[maxn];
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
	for(int i=1;i<n;i++)
	{
		int x=e[i].x;
		int y=e[i].y;
		x=getfa(x);
		y=getfa(y);
		ans+=(size[x]*size[y]-1)*(e[i].len+1);
		if(size[x]>size[y])
			swap(x,y);
		fa[x]=y;
		size[y]+=size[x];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		scanf("%d%d%lld",&e[i].x,&e[i].y,&e[i].len);
	sort(e+1,e+n,cmp);
	kruskal();
	printf("%lld",ans);
}
