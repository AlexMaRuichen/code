#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
double f[1010],h[1010];
const double inf=1e100;
int lis[1010],lds[1010];
int t;
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lf",&h[i]);
	for(int i=1;i<=n;i++)
		f[i]=inf;
	for(int i=0;i<n;i++)
	{
		int k=lower_bound(f+1,f+n+1,h[i])-f;
		f[k]=h[i];
		lis[i]=k;
	}
	for(int i=1;i<=n;i++)
		f[i]=inf;
	for(int i=n-1;i>=0;i--)
	{
		int k=lower_bound(f+1,f+n+1,h[i])-f;
		f[k]=h[i];
		lds[i]=k;
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			ans=max(ans,lis[i]+lds[j]);
	printf("%d\n",n-ans);
}

