#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void gen()
{
	FILE *p=fopen("a.in","w");
	int n=20000;
	fprintf(p,"%d\n",n);
	for(int i=2;i<=n;i++)
		fprintf(p,"%d %d %d\n",i,rand()%(i-1)+1,rand()%3);
	fclose(p);
}
int main()
{
	srand(time(NULL));
	rand();
	system("g++ 2152.cpp -o 2152 -g -Wall");
	system("g++ 2152_pq.cpp -o 2152_pq -g -Wall");
	while(true)
	{
		gen();
		system("./2152<a.in>a.out");
		system("./2152_pq<a.in>b.out");
		if(system("diff a.out b.out -bw > /dev/null"))
			return puts("WA"),0;
		static int cnt;
		printf("%d AC\n",++cnt);
	}
}
