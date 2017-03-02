#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
const int maxn=5e4+10;
int n;
typedef pair<int,pair<int,int> > seg;
typedef pair<int,int> point;
int rect[maxn][5];
seg edges[2*maxn];
multiset<point> s;
bool v[maxn];
int c;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<=4;j++) 
			scanf("%d",&rect[i][j]);
		edges[2*i-1]=seg(rect[i][1],point(i,1));
		edges[2*i]=seg(rect[i][3],point(i,0));
	}
	sort(edges+1,edges+2*n+1);
	s.insert(point(~0u>>1,1));
	for(int i=1;i<=2*n;i++) 
	{
		int idx=edges[i].second.first;
		int start=edges[i].second.second;
		pair<int,int> p=*(s.lower_bound(point(rect[idx][2],-1)));
		if(start) 
		{
			if(p.second==1) 
			{
				++c;
				v[idx]=1;
				s.insert(point(rect[idx][2], 1));
				s.insert(point(rect[idx][4], 0));
			}
		}
		else
		{
			if(v[idx]) 
			{
				s.erase(s.find(point(rect[idx][2], 1)));
				s.erase(s.find(point(rect[idx][4], 0)));
			}
		}
	}
	printf("%d\n",c);
}
