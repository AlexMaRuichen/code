#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=32000;
int bit[maxn+10];
int n;
int ans[15010];
map <pair<int,int>,int> m;
struct point
{
	int x,y;
}p[15010];
bool cmp(point x,point y)
{
	if(x.x!=y.x)
		return x.x<y.x;
	return x.y<y.y;
}
void modify(int x,int y)
{
	for(int i=x;i<=maxn;i+=lowbit(i))
		bit[i]+=y;
}
int query(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=bit[i];
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		ans[query(p[i].y)-m[make_pair(p[i].x,p[i].y)]]++;
		m[make_pair(p[i].x,p[i].y)]++;
		modify(p[i].y,1);
	}
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
}
