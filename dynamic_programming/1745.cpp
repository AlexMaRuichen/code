#include <stdio.h>
const int maxn=60;
int n,k,p,color,value,m;
long long a[maxn],b[maxn],t[maxn],sum;
int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&color,&value);
		if(value<=p)
			m=i;
		if(m>=a[color])
			t[color]=b[color];
		a[color]=i;
		sum+=t[color];
		++b[color];
	}
	printf("%lld\n",sum);
}
