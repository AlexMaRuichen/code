#include <stdio.h>
#include <algorithm>
using namespace std;
int C,G;
int f[21][15001];
int x[21];
int g[21];
const int s=7500;
int main()
{
	scanf("%d%d",&C,&G);
	for(int i=1;i<=C;i++)
		scanf("%d",&x[i]);
	for(int i=1;i<=G;i++)
		scanf("%d",&g[i]);
	for(int j=1;j<=C;j++)
		f[1][s+x[j]*g[1]]++;
	for(int i=2;i<=G;i++)
		for(int k=1;k<=C;k++)
			for(int j=0;j<=s*2+1;j++)
				if(j-g[i]*x[k]<0)
					continue;
				else
					f[i][j]+=f[i-1][j-g[i]*x[k]];
	printf("%d\n",f[G][s]);
}
