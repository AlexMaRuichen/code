#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f[50][50];
int n,m,x,y;
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	f[x][y]=-1;
	if(x+2<=n&&y+1<=m)
		f[x+2][y+1]=-1;
	if(x+1<=n&&y+2<=m)
		f[x+1][y+2]=-1;
	if(x-2>=0&&y+1<=m)
		f[x-2][y+1]=-1;
	if(x-1>=0&&y+2<=m)
		f[x-1][y+2]=-1;
	if(x+2<=n&&y-1>=0)
		f[x+2][y-1]=-1;
	if(x+1<=n&&y-2>=0)
		f[x+1][y-2]=-1;
	if(x-2>=0&&y-1>=0)
		f[x-2][y-1]=-1;
	if(x-1>=0&&y-2>=0)
		f[x-1][y-2]=-1;
	f[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
		{
			if(i==0&&j==0)
				continue;
			if(f[i][j]==-1)
				continue;
			else 
			{
				if(i-1>=0&&f[i-1][j]!=-1)
					f[i][j]+=f[i-1][j];
				if(j-1>=0&&f[i][j-1]!=-1)
					f[i][j]+=f[i][j-1];
			}
		}
	printf("%lld\n",f[n][m]);
}
