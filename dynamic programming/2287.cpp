#include <stdio.h>
#include <algorithm>
using namespace std;
bool f[2][800][800];
int main()
{
	int a[30],n,ans=~0u>>1,sum;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	f[0][0][0]=true;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=700;j++)
			for(int k=0;k<=700;k++)
				if(f[(i&1)^1][j][k])
				{	
					f[i&1][j][k]=true;
					f[i&1][j+a[i]][k]=true;
					f[i&1][j][k+a[i]]=true;
				}
	for(int i=0;i<=700;i++)
		for(int j=0;j<=700;j++)
			if(f[n&1][i][j]&&i>0&&j>0&&sum-i-j>0)
				ans=min(ans,max(i,max(j,sum-i-j)));
	printf("%d\n",ans);
}
