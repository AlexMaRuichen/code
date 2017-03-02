#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=810;
int n,k;
int map[maxn][maxn];
int sum[maxn][maxn];
int ans;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&map[i+j-1][n-i+j]);
    n=(n<<1)-1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
    k=(k<<1)+1;
	if(k>=n)
		printf("%d\n",sum[n][n]);
	else
	{
		for(int i=1;i<=n-k+1;i++)
			for(int j=1;j<=n-k+1;j++)
				ans=max(ans,sum[i+k-1][j+k-1]-sum[i-1][j+k-1]-sum[i+k-1][j-1]+sum[i-1][j-1]);
		printf("%d\n",ans);
	}
}
