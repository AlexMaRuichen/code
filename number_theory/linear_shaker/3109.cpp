#include <stdio.h>
#include <algorithm>
using namespace std;
int pre[1000010];
int prime[80000];
int cnt;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		if(!pre[i])
		{
			prime[++cnt]=i;
			for(int j=2;i*j<=n;j++)
				pre[i*j]=true;
		}
	}
	for(int i=2;i<=n/2;i++)
		if(!pre[i]&&!pre[n-i])
		{
			printf("%d=%d+%d\n",n,i,n-i);
			return 0;
		}
	puts("NO WAY!");
}
