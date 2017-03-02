#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
struct vertex
{
	ll x,y;
}v[1000010];
int n;
bool cmp(vertex a,vertex b)
{
	if(a.x==b.x)
		return a.y<b.y;
	else
		return a.x<b.x;
}
double ans=~0u>>1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&v[i].x,&v[i].y);
	sort(v+1,v+n+1,cmp);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(v[j].x-v[i].x>=ans)
				break;
			double dis=sqrt(pow(v[i].x-v[j].x,2)+pow(v[i].y-v[j].y,2));
			ans=min(ans,dis);
		}
	printf("%.3lf",ans);
}
