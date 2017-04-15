#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=30;
int a[maxn][maxn];
int n,m;
bool check()
{
	
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		for(int j=1;j<=m;j++)
			if(a[i][j]!=j)
			{
				++cnt;
			}
		if(cnt>2)
			return false;
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	if(check())
	{
		puts("YES");
		return 0;
	}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
		{
			for(int k=1;k<=n;k++)
				swap(a[k][i],a[k][j]);
			if(check())
			{
				puts("YES");
				return 0;
			}
			for(int k=1;k<=n;k++)
				swap(a[k][i],a[k][j]);
		}
	puts("NO");
}
