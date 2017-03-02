#include <stdio.h>
#include <set>
using namespace std;
typedef pair<int,int> point;
set <point> f1,g1;
set <point> :: reverse_iterator it;
int a[100010];
int n;
int f[100010];
int g[100010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f1.insert(point(1,a[1]));
	g1.insert(point(1,a[1]));
	for(int i=2;i<=n;i++)
	{
		for(it=g1.rbegin();it!=g1.rend();it++)
			if(a[i]>(*it).second)
			{
				f[i]=(*it).first+1;
				f1.insert(point(f[i],a[i]));
				break;
			}
		for(it=f1.rbegin();it!=f1.rend();it++)
			if(a[i]<(*it).second)
			{
				g[i]=(*it).first+1;
				g1.insert(point(g[i],a[i]));
				break;
			}
	}
	printf("%d\n",max((*f1.rbegin()).first,(*g1.rbegin()).first));
}
