#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	int t;
	long long ans;
	long long pon[25]={1};
	int x[25];
	for(int i=1;i<=20;i++)
		pon[i]=pon[i-1]*i;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	for(int i=1;i<=n;i++)
	{
		static int cnt;
		cnt=0;
		for(int j=i+1;j<=n;j++)
			if(x[i]>x[j])
				cnt++;
		ans+=cnt*pon[n-i];
	}
	ans++;
	printf("%lld\n",ans);
}	
