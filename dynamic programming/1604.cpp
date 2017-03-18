#include <stdio.h>
#include <algorithm>
#define update(x,y) (x)=(x)>(y)?(x):(y)
using namespace std;
int n,m;
int s[360];
int f[45][45][45][45];
int a,b,c,d;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(int i=1;i<=m;i++)
	{
		static int x;
		scanf("%d",&x);
		x==1?++a:x==2?++b:x==3?++c:++d;
	}
	for(int i=0;i<=a;i++)
		for(int j=0;j<=b;j++)
			for(int k=0;k<=c;k++)
				for(int l=0;l<=d;l++)
				{
					if(i)
						update(f[i][j][k][l],f[i-1][j][k][l]);
					if(j)
						update(f[i][j][k][l],f[i][j-1][k][l]);
					if(k)
						update(f[i][j][k][l],f[i][j][k-1][l]);
					if(l)
						update(f[i][j][k][l],f[i][j][k][l-1]);
					f[i][j][k][l]+=s[i+j*2+k*3+l*4+1];
				}
	printf("%d\n",f[a][b][c][d]);
}
