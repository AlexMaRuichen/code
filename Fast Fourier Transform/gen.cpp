#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
void gen()
{
	FILE *p=fopen("a.in","w");
	int n=200000;
	int m=2000;
	int k=rand()%200+1;
	fprintf(p,"%d %d %d\n",n,m,k);
	for(int i=0;i<n;i++)
		fprintf(p,"%c",'0'+rand()%10);
	fprintf(p,"\n");
	for(int i=0;i<m;i++)
		fprintf(p,"%c",'0'+rand()%10);
	fprintf(p,"\n");
	fclose(p);
}
int main()
{
	srand(time(NULL));
	rand();
	gen();
/*	system("g++ 528D.cpp -o 528D -g -Wall");
	system("g++ BF.cpp -o BF -g -Wall");
	while(true)
	{
		gen();
		clock_t c=clock();
		system("./528D<a.in>a.out");
		printf("%lf\n",(clock()-c)*1.0/CLOCKS_PER_SEC);
		c=clock();
		system("./BF<a.in>b.out");
		printf("%lf\n",(clock()-c)*1.0/CLOCKS_PER_SEC);
		if(system("diff a.out b.out -bw > /dev/null"))
			return puts("WA"),0;
		static int cnt;
		printf("%d AC\n",++cnt);
	}*/
}
