#include <stdio.h>
#include <algorithm>
using namespace std;
int n,k;
int ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int x;
		int cnt=0;
		while(scanf("%d",&x)==1&&x)
			cnt++;
		if(cnt>=k)
			ans++;
	}
	printf("%d",ans);
}
