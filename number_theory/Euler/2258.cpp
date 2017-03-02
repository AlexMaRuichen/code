#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	while(scanf("%d",&n)==1)
	{
		if(n==0)
		{
			puts("0");
			continue;
		}
		if(n==1)
		{
			puts("2");
			continue;
		}
		int phi=n;
		for(int i=2;i*i<=n;i++)
			if(n%i==0)
			{
				phi/=i;
				phi*=i-1;
				while(n%i==0)
					n/=i;
			}
		if(n!=1)
			phi/=n,phi*=n-1;
		printf("%d\n",phi);
	}
}
