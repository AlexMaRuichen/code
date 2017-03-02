#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
double g[21][21];
double ans;
int c[21];
double f[(1<<20)+1];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%lf",&g[i][j]);
			g[i][j]/=100;
		}
	f[0]=100;
	for(int i=1;i<=(1<<n)-1;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
			if(i&(1<<(j-1)))
			{
				cnt++;
				c[cnt]=j;
			}
		for(int j=1;j<=cnt;j++)
			f[i]=max(f[i-(1<<(c[j]-1))]*g[c[j]][cnt],f[i]);
	}
	printf("%.6lf",f[(1<<n)-1]);
}
