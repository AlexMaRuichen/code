#include <stdio.h>
#include <algorithm>
using namespace std;
int pre[1500010];
int prime[80000];
int cnt;
int t;
int c;
int main()
{
	for(int i=2;i<=1000000;i++)
		if(!pre[i])
		{
			prime[++cnt]=i;
			for(int j=2;j*i<=1000000;j++)
				pre[i*j]=true;
		}
	scanf("%d",&t);
	while(t--)
	{
		c=0;
		static long long n;
		scanf("%lld",&n);
		for(int i=1;i<=cnt;i++)
		{
			while(n%prime[i]==0)
				n/=prime[i],c++;
			if(c>3)
			{
				puts("cow");
				goto lableA;
			}
		}
		if(n!=1)
			c++;
		if(c>3)
		{
			puts("cow");
			goto lableA;
		}
		puts("no");
		lableA:;
	}
}
