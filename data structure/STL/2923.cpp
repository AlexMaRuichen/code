#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
const int maxn=5e4+10;
int n;
typedef pair<int,int> seg;
typedef pair<int,seg> cow;
set <int> s;
set <int> ::iterator lb,ub;
cow bak[maxn];
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x*=-z;
		bak[i].first=y;
		bak[i].second.first=x-z;
		bak[i].second.second=x;
		s.insert(x-z-1);
		s.insert(x-z);
		s.insert(x-z+1);
		s.insert(x-1);
		s.insert(x);
		s.insert(x+1);
	}
	sort(bak+1,bak+n+1);
	for(int i=1;i<=n;i++)
	{
		lb=s.lower_bound(bak[i].second.first);
		ub=s.lower_bound(bak[i].second.second);
		if(lb!=ub)
			++ans,s.erase(lb,ub);
	}
	printf("%d\n",ans);
}
