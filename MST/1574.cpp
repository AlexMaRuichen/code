#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=20000;
typedef long long ll;
struct edge
{
	int x,y;
	ll len;
}e[maxn+10];
bool cmp(edge a,edge b)
{
	return a.len<b.len;
}
int n;
ll ans;
int fa[maxn+10];
int size[maxn+10];
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
void kruskal()
{
	init();
	sort(e+1,e+n,cmp);
	for(int i=1;i<n;i++)
	{
		int x=e[i].x;
		int y=e[i].y;
		x=getfa(x);
		y=getfa(y);
		if(size[x]<size[y])
			swap(x,y);
		ans+=(size[x]*size[y]-1)*(e[i].len+1);
		fa[y]=x;
		size[x]+=size[y];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%lld",&e[i].x,&e[i].y,&e[i].len);
		ans+=e[i].len;
	}
	kruskal();
	printf("%lld",ans);
}
