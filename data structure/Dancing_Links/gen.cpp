#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
void gen()
{
	FILE *p=fopen("a.in","w");
	int n=16,m=300;
	int T=500;
	while(T--)
	{
		fprintf(p,"%d %d\n",n,m);
		for(int i=1;i<=n;i++,fprintf(p,"\n"))
			for(int j=1;j<=m;j++)
				fprintf(p,"%d ",rand()&1);
	}
	fclose(p);

}
int main()
{
	srand(time(NULL));
	rand();
	system("g++ 3740.cpp -o 3740 -g -Wall");
	system("g++ 3740_.cpp -o 3740_ -g -Wall");
	while(true)
	{
		gen();
		system("./3740<a.in>a.out");
		system("./3740_<a.in>b.out");
		if(system("diff a.out b.out -bw > /dev/null"))
			return puts("WA"),0;
		static int cnt;
		printf("%d AC\n",++cnt);
	}
}

