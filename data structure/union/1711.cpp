#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2e4+10;
const int maxm=1e5+10;
int n,m;

int fa[maxn*2];
int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
void init()
{
	for(int i=1;i<=n<<1;i++)
		fa[i]=i;
}

struct edge
{
	int x,y,len;
	bool operator < (const edge s) const
	{
		return len>s.len;
	}
}e[maxm];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);

	sort(e+1,e+m+1);

	init();

	for(int i=1;i<=m;i++)
	{
		int x=getfa(e[i].x);
		int y=getfa(e[i].y);
		if(x==y)
		{
			printf("%d\n",e[i].len);
			return 0;
		}
		fa[y]=getfa(e[i].x+n);
		fa[x]=getfa(e[i].y+n);
	}
	puts("0");
}
