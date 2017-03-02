#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int,int> point;
const int maxn=10010;
int n;
point p[maxn];
int ans;
bool v[maxn];
set <int> pos;
set <int> :: iterator it;
int mx;
bool cmp(point x,point y)
{
	if(x.first==y.first)
		return x.second<y.second;
	return x.first>y.first;
}
int main()
{
//	freopen("2387.in","r",stdin);
//	freopen("2387.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i].first,&p[i].second);
		mx=max(mx,p[i].second);
	}
	for(int i=1;i<=mx;i++)
		pos.insert(i);
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n&&(!pos.empty());i++)
		if(*pos.begin()<=p[i].second)
		{
			pos.erase(--pos.upper_bound(p[i].second));
			ans+=p[i].first;
		}
	printf("%d\n",ans);
}
