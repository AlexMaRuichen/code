#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=32000;
int bit[maxn+100];
int n;
int ans[15010];
struct point
{
	int x,y;
}p[15010];
void modify(int x,int y)
{
	for(int i=x;i<=maxn+1;i+=lowbit(i))
		bit[i]+=y;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].x++;
		ans[query(p[i].x)]++;
		modify(p[i].x,1);
	}
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
}
