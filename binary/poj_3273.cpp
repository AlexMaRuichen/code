#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
int a[100010];
int sum;
bool check(int x)
{
	int tmp=0;
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>x)
			return false;
		else if(a[i]+tmp<=x)
			tmp+=a[i];
		else
			tmp=a[i],ans++;
	}
	return ans<=m;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	int l=0,r=sum;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
}
