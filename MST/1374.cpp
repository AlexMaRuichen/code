#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1010;
const int maxe=10010;
struct edge
{
	int x,y,len;
}e[maxe];
bool cmp(edge x,edge y)
{
	return x.len<y.len;
}
int n,m,k;
int ans;
int cnt;
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
	for(int i=1;i<=m;i++)
	{
		if(cnt==k)
			break;
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
		cnt--;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	cnt=n;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
	sort(e+1,e+m+1,cmp);
	kruskal();
	if(cnt==k)
		printf("%d",ans);
	else
		puts("No  Answer");
}
