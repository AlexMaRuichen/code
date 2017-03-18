#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	FILE *p=fopen("a.in","w");
	int n=200000;
	srand(time(NULL));
	rand();
	fprintf(p,"%d\n",n);
	for(int i=1;i<=n;i++)
		fprintf(p,"%d\n",rand());
}
