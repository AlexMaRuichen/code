#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int n;
bool flag;
int main()
{
	register int i,j;
	scanf("%d",&n);
	int ml=sqrt(2*n);
	for(i=ml;i>=2;i--)
	{
		int x=((2*n/i)+1-i)>>1;
		if(i*x+i*(i-1)/2==n)
		{
			for(j=x;j<x+i;j++)
				printf("%d ",j);
			puts("");
			flag=true;
		}
	}
	if(!flag)
		puts("NONE");
}
