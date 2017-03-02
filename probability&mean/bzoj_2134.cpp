#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=10000010;
int n,A,B,C,d;
int a[maxn];
double ans;
int main()
{
	register int i;
	scanf("%d%d%d%d%d",&n,&A,&B,&C,a+1);
	for(i=2;i<=n;i++)
		a[i]=((long long)a[i-1]*A+B)%100000001;
	a[1]=a[1]%C+1;
	for(i=2;i<=n;i++)
	{
		a[i]=a[i]%C+1;
		ans+=1.0/double(max(a[i],a[i-1]));
	}
	ans+=1.0/double(max(a[n],a[1]));
	printf("%.3lf\n",ans);
}
