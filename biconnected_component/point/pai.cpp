#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int Rand(int l,int r)
{
	return rand()%(r-l+1)+l;
}
void gen()
{
	int T=1;
	FILE *p=fopen("a.in","w");
	while(T--)
	{
		int n=5;
		int m=10;
		int q=1;
		fprintf(p,"%d %d %d\n",n,m,q);
		for(int i=1;i<=m;i++)
			fprintf(p,"%d %d\n",Rand(1,n),Rand(1,n));
		for(int i=1;i<=q;i++)
			fprintf(p,"%d %d\n",Rand(1,n),Rand(1,n));
	}
	fprintf(p,"0 0 0\n");
	fclose(p);
}
int main()
{
	system("g++ 3749.cpp -o 3749 -g -Wall");
	system("g++ 3749_.cpp -o 3749_ -g -Wall");
	srand(time(NULL));
	rand();
	while(true)
	{
		static int cnt;
		printf("Case:%d\nGenerating ",++cnt);
		gen();
		printf("3749 ");
		system("./3749<a.in>a.out");
		printf("3749_ ");
		system("./3749_<a.in>b.out");
		printf("\nComparing result:");
		if(system("diff a.out b.out  > /dev/null"))
			return puts("WA"),0;
		puts("AC");
	}
}
