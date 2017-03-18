#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;
typedef pair<int,int> point;
point p[50010];
int main() 
{
	freopen("squares.in","r",stdin);
	freopen("squares.out","w",stdout);
	int n,k; 
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n; i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	set<point> s;
	vector<point> res;
	set<point>::iterator ita,itb;
	for(int i=1,j=1;i<=n&&res.size()<2;i++) 
	{
		for(;s[j].first+k<=s[i].first;j++) 
			s.erase(point(s[j].second,j));
		ita=itb=s.insert(point(s[i].second,i)).first;
		if(ita--!=s.begin()&&s[i].second< ita->first+k)
			res.push_back(point(i,ita->second));
		if(++itb!=s.end()&&itb->first<s[i].second+k)
			res.push_back(point(i,itb->second));
	}

	long long ans = 0;
	if(res.size()>1) 
		ans=-1;
	else if(res.size()==1)
	{
		int dx=s[res[0].first].first-s[res[0].second].first;
		int dy=s[res[0].first].second-s[res[0].second].second;
		if(dx<0) 
			dx=-dx;
		if(dy<0)
			dy=-dy;
		ans = 1ll * (k - dx) * (k - dy);
	}
	printf("%d\n",ans);
}
