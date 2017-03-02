#include <stdio.h>
#include <algorithm>
using namespace std;
int s,c;
int main()
{
	int n;
	for(int i=1;i<=12;i++)
	{
		scanf("%d",&n);
		c+=300;
		c-=n;
		if((c)<0)
		{
			printf("-%d",i);
			return 0;
		}
		else 
		{
			int csave=c/100*100;
			s+=csave;
			c-=csave;
		}
	//	printf("%d %d\n",s,c);
	}
	printf("%.0lf",s*1.2+c);
}
