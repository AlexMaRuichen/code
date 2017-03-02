#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
using namespace std;
int n,m,q;
int bit[101][301][301];
int map[301][301];
void modify(int x,int y,int c,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			bit[c][i][j]+=z;
}
int query(int x,int y,int c)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		for(int j=y;j>=1;j-=lowbit(j))
			ans+=bit[c][i][j];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&map[i][j]);
			modify(i,j,map[i][j],1);
		}
	scanf("%d",&q);
	while(q--)
	{
		static int opt,x1,y1,x2,y2,c;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&x1,&y1,&c);
			modify(x1,y1,map[x1][y1],-1);
			modify(x1,y1,c,1);
			map[x1][y1]=c;
		}
		else if(opt==2)
		{
			scanf("%d%d%d%d%d",&x1,&x2,&y1,&y2,&c);
			printf("%d\n",query(x2,y2,c)-query(x1-1,y2,c)-query(x2,y1-1,c)+query(x1-1,y1-1,c));
		}
	}
}
