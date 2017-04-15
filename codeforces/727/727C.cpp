#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=5010;
int n;
int a[maxn];
int sum[4];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n/3;i++)
	{
		printf("? %d %d",3*(i-1)+1,3*(i-1)+2);
		puts("");
		fflush(stdout);
		scanf("%d",&sum[1]);
		printf("? %d %d",3*(i-1)+1,3*(i-1)+3);
		puts("");
		fflush(stdout);
		scanf("%d",&sum[2]);
		printf("? %d %d",3*(i-1)+2,3*(i-1)+3);
		puts("");
		fflush(stdout);
		scanf("%d",&sum[3]);
		int x=sum[1]+sum[2]+sum[3];
		x/=2;
		a[3*(i-1)+1]=x-sum[3];
		a[3*(i-1)+2]=x-sum[2];
		a[3*(i-1)+3]=x-sum[1];
	}
	if(n%3==0)
	{
		printf("!");
		for(int i=1;i<=n;i++)
			printf(" %d",a[i]);
		puts("");
		fflush(stdout);
	}
	else if(n%3==1)
	{
		printf("? 1 %d",n);
		puts("");
		fflush(stdout);
		scanf("%d",&sum[1]);
		a[n]=sum[1]-a[1];
		printf("!");
		for(int i=1;i<=n;i++)
			printf(" %d",a[i]);
		puts("");
		fflush(stdout);
	}
	else if(n%3==2)
	{
		printf("? 1 %d",n-1);
		puts("");
		fflush(stdout);
		scanf("%d",&sum[1]);
		a[n-1]=sum[1]-a[1];
		printf("? 1 %d",n);
		puts("");		
		fflush(stdout);
		scanf("%d",&sum[1]);
		a[n]=sum[1]-a[1];
		printf("!");
		for(int i=1;i<=n;i++)
			printf(" %d",a[i]);
		puts("");
		fflush(stdout);
	}
}
