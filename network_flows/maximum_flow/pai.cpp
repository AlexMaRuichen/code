#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void gen()
{
	FILE *p=fopen("a.in","w");
	int n=rand()%30+1,m=rand()%30+1;
	fprintf(p,"%d %d\n",n,m);
	for(int i=1;i<=n;i++,fprintf(p,"\n"))
		for(int j=1;j<=m;j++)
			fprintf(p,"%d ",rand());
	fclose(p);
}
int main()
{
	srand(time(NULL));
	rand();
	system("g++ 2496.cpp -o 2496 -g -Wall");
	system("g++ hzwer.cpp -o hzwer -g -Wall");
	int cnt=0;
	while(true)
	{
		gen();
		system("./2496<a.in>a.out");
		system("./hzwer<a.in>b.out");
		if(system("diff a.out b.out -bw > /dev/null"))
			return puts("WA"),0;
		printf("%d AC\n",++cnt);
	}
}
