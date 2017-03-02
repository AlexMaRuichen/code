#include <stdio.h>
#include <algorithm>
#define dis(i,j) ((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))
using namespace std;
const int maxn=2010;
int n;
struct edge
{
	int x,y,len;
}e[maxn*maxn];
int cnt;
bool cmp(const edge &a,const edge &b)
{
	return a.len<b.len;
}
int x[maxn];
int y[maxn];
int fa[maxn];
int size[maxn];
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
int ans;
int c;
int main()
{
	scanf("%d%d",&n,&c);
	register int i,j;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		fa[i]=i;
		size[i]=1;
	}
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		{
			static int l;
			l=dis(i,j);
			if(l>=c)
				e[++cnt].x=i,e[cnt].y=j,e[cnt].len=l;
		}
	sort(e+1,e+cnt+1,cmp);
	for(i=1;i<=cnt;i++)
	{
		static int fx,fy;
		fx=getfa(e[i].x);
		fy=getfa(e[i].y);
		if(fx==fy)
			continue;
		if(size[fx]>size[fy])
			swap(fx,fy);
		fa[fx]=fy;
		size[fy]+=size[fx];
		ans+=e[i].len;
	}
	if(size[getfa(1)]!=n)
		puts("-1");
	else
		printf("%d\n",ans);
}
