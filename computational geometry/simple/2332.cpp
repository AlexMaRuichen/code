#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
const int maxn=1000;
typedef pair<int,int> Point;
typedef Point Vector;
typedef pair<Point,Point> fence;
Vector operator + (const Vector &a,const Vector &b)
{
	return Vector(a.first+b.first,a.second+b.second);
}
Vector operator - (const Vector &a,const Vector &b)
{
	return Vector(a.first-b.first,a.second-b.second);
}
int cross(Vector a,Vector b)
{
	return a.first*b.second-a.second*b.first;
}
int n,c;
map<Point,vector<int> > pmap;
fence f[maxn];
Point p[maxn];
int cnt;
int cycle[maxn];
char par[maxn][maxn];
char* parptrs[maxn];
vector <Point> cpoint[maxn];
bool inside(Point a,int c)
{
	for(vector <Point>:: iterator it=cpoint[c].begin();it!=cpoint[c].end();it++)
		if(cross(a,*(it+1)-*it)<0)
			return false;
	return false;
}
inline bool ptrcmp(char* a, char* b) 
{
    return strcmp(a,b)<0;
}
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		static Point p[2];
		scanf("%d%d%d%d",&p[0].first,&p[0].second,&p[1].first,&p[1].second);
		pmap[p[0]].push_back(i);
		pmap[p[1]].push_back(i);
		f[i]=fence(p[0],p[1]);
		cycle[i]=-1;
	}
	for(int i=1;i<=c;i++)
		parptrs[i]=par[i];
	for(int i=1;i<=n;i++)
	{
		if(cycle[i]==-1)
		{
			++cnt;
			int j=i;
			Point last=f[i].first;
			do
			{
				cpoint[cnt].push_back(last);
				cycle[j]=cnt;
				last=f[j].first==last?f[j].second:f[j].first;
				j=(pmap[last][0]==j?pmap[last][1]:pmap[last][0]);
			}
			while(i!=j);
		}
	}
	for(int i=1;i<=c;i++)
	{
		static Point cow;
		scanf("%d%d",&cow.first,&cow.second);
		for(int j=1;j<=n;j++)
			par[i][cycle[j]]=(char)inside(cow,cycle[j]);
		for(int j=1;j<=cnt;j++)
			par[i][j]=par[i][j]?'1':'0';
		par[i][cnt+1]='\0';
	}
	sort(parptrs,parptrs+c,ptrcmp);
	int maxans=0;
    int curcount=0;
    for (int i=1;i<=c;i++)
    {
		if (i==1||strcmp(parptrs[i],parptrs[i-1])!=0) 
			curcount=1;
		else 
			curcount++;
        maxans=max(maxans,curcount);
    }
    printf("%d\n",maxans);
}
