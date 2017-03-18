#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
int a[250000+10];
int main()
{
	srand(time(NULL));
	rand();
	int n=250000;
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %d %d\n",i,rand()%(i-1)+1,rand()%100000+1);
	int m=rand()%500+1;
	printf("%d\n",m);
	for(int i=2;i<=n;i++)
		a[i]=i;
	for(int i=1;i<=m;i++)
	{
		int k=rand()%(n-1)+1;
		printf("%d ",k);
		random_shuffle(a+1,a+n);
		for(int i=1;i<=k;i++)
			printf("%d ",a[i]);
		puts("");
	}
}
