#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
int n;
int bit[1100][1100];
void modify(int x,int y,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			bit[i][j]+=z;
}
int query(int x,int y)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			ans+=bit[i][j];
	return ans;
}
int main()
{
	scanf("%d",&n);
	int opt,a,b,c,d;
	while(scanf("%d",&opt)==1&&opt!=3)
	{
		if(opt==1)
		{
			scanf("%d%d%d",&a,&b,&c);
			modify(a+1,b+1,c);
		}
		else if(opt==2)
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%d\n",query(c+1,d+1)-query(a,d+1)-query(c+1,b)+query(a,b));
		}
	}
}
