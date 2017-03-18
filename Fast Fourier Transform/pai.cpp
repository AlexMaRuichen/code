#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void gen()
{
	FILE *p=fopen("a.in","w");
	int len=100000;
	for(int i=1;i<=len;i++)
		fprintf(p,"%c",rand()&1?'a':'b');
	fprintf(p,"\n");
	fclose(p);
}
int main()
{
	srand(time(NULL));
	rand();
	system("g++ 3160.cpp -o 3160 -g -Wall");
	system("g++ 3160_pq.cpp -o 3160_pq -g -Wall");
	int cnt=0;
	while(true)
	{
		gen();
		system("./3160<a.in>a.out");
		system("./3160_pq<a.in>b.out");
		if(system("diff a.out b.out -bw > /dev/null"))
			return puts("WA"),0;
		printf("%d AC\n",++cnt);
	}
}
