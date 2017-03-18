#include <stdio.h>
#include <algorithm>
#include <set>
#define lab(i,j) (((i)-1)*(n)+(j))
using namespace std;
const int maxn=510;
set <int> s;
struct edge
{
	int x,y,len;
}e[maxn*maxn*10];
int map[maxn][maxn];
int n;
int fa[maxn*maxn];
int size[maxn*maxn];
int cnt;
int maxsize;
bool cmp(edge a,edge b)
{
	return a.len<b.len;
}
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	x=getfa(x);
	y=getfa(y);
	if(x==y)
		return;
	if(size[x]>size[y])
		swap(x,y);
	fa[x]=y;
	size[y]+=size[x];
	maxsize=max(maxsize,size[y]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&map[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i>1)
			{
				e[++cnt].x=lab(i,j);
				e[cnt].y=lab(i-1,j);
				e[cnt].len=abs(map[i][j]-map[i-1][j]);
			}	
			if(i<n)
			{
				e[++cnt].x=lab(i,j);
				e[cnt].y=lab(i+1,j);
				e[cnt].len=abs(map[i][j]-map[i+1][j]);
			}
			if(j>1)
			{
				e[++cnt].x=lab(i,j);
				e[cnt].y=lab(i,j-1);
				e[cnt].len=abs(map[i][j]-map[i][j-1]);
			}
			if(j<n)
			{
				e[++cnt].x=lab(i,j);
				e[cnt].y=lab(i,j+1);
				e[cnt].len=abs(map[i][j]-map[i][j+1]);
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			fa[lab(i,j)]=lab(i,j),size[lab(i,j)]=1;
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int x=getfa(e[i].x);
		int y=getfa(e[i].y);
		if(x==y)
			continue;
		merge(x,y);
		if(maxsize*2>=n*n)
		{
			printf("%d\n",e[i].len);
			return 0;
		}
	}
}
