#include <stdio.h>
#include <algorithm>
using namespace std;
int a[200010];
int main()
{
	 int n;
	 scanf("%d",&n);
	 for(int i=1;i<=n;i++)
	 	scanf("%d",&a[i]);
	 sort(a+1,a+n+1);
	 int tmp=0;
	 for(int i=1;i<=n+1;i++)
	 	if(a[i]!=a[i-1]&&i!=1)
	 	{
	 		printf("%d %d\n",a[i-1],tmp);
	 		tmp=1;
	 	}
	 	else tmp++;
}
