#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
struct cow
{
	int u,d;
}c[25010];
int end1[25010];
int end2[25010];
int n;
bool cmp(cow a,cow b)
{
	if(a.u<a.d&&b.u<b.d)
		return a.u<b.u;
	else if(a.u<a.d&&b.u>b.d)
		return true;
	else if(a.u>a.d&&b.u<b.d)
		return false;
	else
		return a.d>b.d;	
}
int ans;
int main()
{
//	freopen("2288.in","r",stdin);
//	freopen("2288.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&c[i].u,&c[i].d);
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++)
        end1[i]=end1[i-1]+c[i].u;
    for(int i=1;i<=n;i++)
        end2[i]=max(end2[i-1],end1[i])+c[i].d;
	printf("%d\n",end2[n]);
}
