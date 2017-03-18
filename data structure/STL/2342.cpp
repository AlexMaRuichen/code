#include <vector>
#include <algorithm>
#include <set>
#include <stdio.h>
using namespace std;
typedef pair<int,int> point;
point p[50010];
int main() 
{
	int n,k; 
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n; i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	set <point> s;
	vector <point> res;
	set <point>::iterator ita,itb;
	for(int i=1,j=1;i<=n&&res.size()<2;i++) 
	{
		for(;p[j].first+k<=p[i].first;j++) 
			s.erase(point(p[j].second,j));
		ita=itb=s.insert(point(p[i].second,i)).first;
		if(ita--!=s.begin()&&p[i].second<ita->first+k)
			res.push_back(point(i,ita->second));
		if(++itb!=s.end()&&itb->first<p[i].second+k)
			res.push_back(point(i,itb->second));
	}
	long long ans=0;
	if(res.size()>1) 
		ans=-1;
	else if(res.size()==1)
	{
		int dx=p[res[0].first].first-p[res[0].second].first;
		int dy=p[res[0].first].second-p[res[0].second].second;
		if(dx<0) 
			dx=-dx;
		if(dy<0)
			dy=-dy;
		ans=(long long)(k-dx)*(k-dy);
	}
	printf("%lld\n",ans);
}
