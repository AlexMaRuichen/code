#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	FILE *p=fopen("a.in","w");
	int n=16,m=300;
	fprintf(p,"%d %d\n",n,m);
	srand(time(NULL));
	rand();
	for(int i=1;i<=n;i++,fprintf(p,"\n"))
		for(int j=1;j<=m;j++)
			fprintf(p,"%d ",rand()&1);
	fclose(p);
}
