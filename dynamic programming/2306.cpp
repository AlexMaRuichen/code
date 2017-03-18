#include <stdio.h>
#include <algorithm>
using namespace std;
int a[1001];
int b[1001];
int na,nb;
int f[1001][1001];
int n,x,y,z;
int main()
{
	register int i,j,k;
	scanf("%d%d%d%d",&n,&x,&y,&z);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&j);
		for(k=1;k<=j;k++)
			a[++na]=i;
		scanf("%d",&j);
		for(k=1;k<=j;k++)
			b[++nb]=i;
	}
	for(j=0;j<=nb;j++) 
		f[0][j]=j*x;
	for(i=0;i<=na;i++) 
		f[i][0]=i*y;
	for(i=1;i<=na;i++)
		for(j=1;j<=nb;j++)
		{
			f[i][j]=~0u>>1;
			f[i][j]=min(f[i][j],f[i][j-1]+x);
			f[i][j]=min(f[i][j],f[i-1][j]+y);
			f[i][j]=min(f[i][j],f[i-1][j-1]+z*abs(a[i]-b[j]));
		}
	printf("%d\n",f[na][nb]);
}
