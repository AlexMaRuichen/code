#include <stdio.h>
#include <string.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
int T,sg[1000001],n,tmp,m,M,x;
int main()
{
	register int i;
	for(i=1;i<=1e6;i++)
	{
		tmp=i;
		m=10,M=0;
		while(tmp)
		{
			x=tmp%10;
			if(x)
				m=min(m,x);
			M=max(M,x);
			tmp/=10;;
		}
		sg[i]=(sg[i-M]&sg[i-m])^1;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		sg[n]?puts("YES"):puts("NO");
	}
}
