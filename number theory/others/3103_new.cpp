#include <stdio.h>
#include <math.h>
int main()
{
	int n;
	int i,j,k,s;
	printf("输入一个数：");
	scanf("%d",&n);
	s=0;
	k=1;
	for(i=1;i<=n/2+1;i++)
	{
		s=s+i;
		if(s==n)
		{
			s=0;
			for(;s<n;i--)
			{
				s=s+i;
			}
			s=0;
			for(i=i+1;s<n;i++)
			{
				s=s+i;
				printf("%d+",i);				
			}	
			printf("\b=%d\n",n);
			k=k+1;
			i=k;
			s=0;
		}
		else
		{
			if(s>n)
			{
				k=k+1;
				i=k;
				s=0;
			}
		}
	}

}
