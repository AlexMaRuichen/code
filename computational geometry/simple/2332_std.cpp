#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
const int maxn=1010;
typedef pair<long long,long long> point;
bool rayHits(point a,point b,point c) 
{
	if ((b.second>a.second)^(c.second>a.second)) 
		return (b.second-c.second<0)^(c.first*(b.second-a.second)+b.first*(a.second - c.second)>a.first* (b.second-c.second));
	else
		return false;
}

map<point,vector<int> > pmap;
pair<point,point > fences[maxn];
int cycle[maxn];
char par[maxn][maxn];
char* parptrs[maxn];
inline bool ptrcmp(char* a,char* b) 
{
	return strcmp(a,b)<0;
}

int main()
{
	int n,c;
	scanf("%d",&n);
	scanf("%d",&c);
	for (int i=0;i<n;i++)
	{
		point p1,p2;
		scanf("%lld%lld%lld%lld",&p1.first,&p1.second,&p2.first,&p2.second);
		pmap[p1].push_back(i);
		pmap[p2].push_back(i);
		fences[i]=pair<point,point >(p1,p2);
		cycle[i]=-1;
	}
	for (int i=0;i<c;i++)
		parptrs[i]=par[i];
	int ncycles=0;
	for (int i=0;i<n;i++) 
	{
		if (cycle[i]==-1) 
		{
			int j=i;
			point last=fences[i].first;
			do 
			{
				cycle[j]=ncycles;
				last=fences[j].first==last ? fences[j].second : fences[j].first;
				j=(pmap[last][0]==j ?pmap[last][1]:pmap[last][0]);
			}
			while(j!=i);
			ncycles++;
		}
	}
	for (int i=0;i<c;i++) 
	{
		point cow;
		scanf("%lld%lld",&cow.first,&cow.second);
		for (int j=0;j<n;j++)
			par[i][cycle[j]]^=(char)rayHits(cow,fences[j].first,fences[j].second);
		for (int j=0;j<ncycles;j++) 
			par[i][j]=par[i][j]?'1':'0';
		par[i][ncycles]='\0';
	}
	sort(parptrs,parptrs + c,ptrcmp);
	int maxans=0;
	int curcount=0;
	for (int i=0;i<c;i++) 
	{
		if (i==0||strcmp(parptrs[i],parptrs[i-1]) != 0) 
			curcount=1;
		else 
			curcount++;
		maxans=max(maxans,curcount);
	}
	printf("%d\n",maxans);
}

