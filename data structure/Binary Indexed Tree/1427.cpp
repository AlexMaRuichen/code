#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=500010;
int n,k;
int bit[maxn];
void modify(int x,int y)
{
	while(x<n)
	{
		bit[x]+=y;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int ans=0;
	while(x)
	{
		ans+=bit[x];
		x-=lowbit(x);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	while(k--)
	{
		static char opt[10];
		static int x,y;
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			scanf("%d",&x);
			printf("%d\n",query(x));
		}
		else if(opt[0]=='B')
		{
			scanf("%d%d",&x,&y);
			modify(x,y);
		}
		else if(opt[0]=='C')
		{
			scanf("%d%d",&x,&y);
			modify(x,-y);
		}
	}
}
