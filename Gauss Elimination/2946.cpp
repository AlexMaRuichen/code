#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=100010;
int n,a[maxn];
int gauss_elimination()
{
	int i,j,k,ans=0;
	for(i=30,k=0;~i;--i)
	{
		for(j=k+1;j<=n;j++)
			if(a[j]&(1<<i))
				break;
		if(j==n+1)
			continue;
		swap(a[j],a[++k]);
		for(j=1;j<=n;j++)
			if(j^k&&a[j]&(1<<i))
				a[j]^=a[k];
	}
	for(i=1;i<=k;i++)
		ans^=a[i];
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	printf("%d\n",gauss_elimination());
}
