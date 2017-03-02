#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=110;
const int mod=1e9+7;
int r,c,k;
int f[maxn][maxn];
int col[maxn][maxn];
int main()
{
	scanf("%d%d%d",&r,&c,&k);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			scanf("%d",&col[i][j]);
	f[1][1]=1;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			for(int a=1;a<i;a++)
				for(int b=1;b<j;b++)
					if(col[a][b]!=col[i][j])
						f[i][j]=(f[i][j]+f[a][b])%mod;
	printf("%d\n",f[r][c]);
}
