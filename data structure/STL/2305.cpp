#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
multiset <int> ms;
typedef pair<int,int> point;
point p[100010];
bool cmp(point a,point b)
{
	if(a.first!=b.first)
		return a.first<b.first;
	return a.second<b.second;
}
int n,d;
int ans=~0u>>1;
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1,cmp);
	int l=1,r=1;
	while(r<=n)
	{
		ms.insert(p[r].second);
		if(*ms.rbegin()-*ms.begin()>=d)
		{
			while(*ms.rbegin()-*ms.begin()>=d)
				ms.erase(ms.find(p[l++].second));
			ans=min(ans,p[r].first-p[l-1].first);
		}
		++r;
	}
	printf("%d\n",ans==~0u>>1?-1:ans);
}
