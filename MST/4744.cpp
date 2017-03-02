#include <stdio.h>
#include <algorithm>
using namespace std;
struct edge
{
	int x,y,len;
}e[1000010];
bool cmp(const edge &a,const edge &b)
{
	return a.len<b.len;
}
int n;
int fa[1010];
int rank[1010];
int getfa(int x)
{
	if(fa[x]^x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	if(rank[x]>rank[y])
		swap(x,y);
	else if(rank[x]==rank[y])
		++rank[y];
	fa[x]=y;
}
typedef pair<int,int> point;
point p[1010];
int ans;
int main()
{
	int tot=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		scanf("%d%d",&p[i].first,&p[i].second);
		for(int j=1;j<i;j++)
		{
			e[++tot].x=i;
			e[tot].y=j;
			e[tot].len=(p[i].first-p[j].first)*(p[i].first-p[j].first)+(p[i].second-p[j].second)*(p[i].second-p[j].second);
		}
	}
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	{
		int x=getfa(e[i].x);
		int y=getfa(e[i].y);
		if(x==y)
			continue;
		merge(x,y);
		ans=e[i].len;
	}
	printf("%d\n",ans);
}
