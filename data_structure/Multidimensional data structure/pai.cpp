#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
int a[100010];
void gen()
{
	FILE *p=fopen("a.in","w");
	int n=10000;
	int m=10000;
	fprintf(p,"%d %d\n",n,m);
	for(int i=1;i<=n;i++)	
		fprintf(p,"%d ",rand()%1000000+1);
	fprintf(p,"\n");
	for(int i=m;i;i--)
		if(rand()&1)
		{
			int l=rand()%n+1;
			int r=rand()%n+1;
			fprintf(p,"Q %d %d\n",l<r?l:r,l>r?l:r);
		}
		else
			fprintf(p,"R %d %d\n",rand()%n+1,rand()%1000000+1);
	fclose(p);
}
int main()
{
	srand(time(NULL));
	rand();
	system("g++ 3295.cpp -o 3295 -g -Wall");
//	system("g++ hzwer.cpp -o hzwer -g -Wall");
//	int cnt=0;
//	while(true)
//	{
		gen();
//		system("./3295<a.in>a.out");
//		system("./hzwer<a.in>b.out");
//		if(system("diff a.out b.out -bw > /dev/null"))
//			return puts("WA"),0;
//		printf("%d AC\n",++cnt);
//	}
}
