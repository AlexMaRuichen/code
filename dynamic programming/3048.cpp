#include <stdio.h>
#include <bitset>
#include <algorithm>
using namespace std;
const int maxn=110;
class MilkPails
{
	int x,y,K,m;
	bitset <maxn> f[maxn][maxn];
public:
	int solve()
	{
		int ans=~0u>>1;
		scanf("%d%d%d%d",&x,&y,&K,&m);
		f[1][x][0]=f[1][0][y]=f[1][0][0]=true;
		for(int i=1;i<=K;i++)
			for(int j=0;j<=x;j++)
				for(int k=0;k<=y;k++)
					if(f[i][j][k])
					{
						f[i+1][j][y]=true;
						f[i+1][x][k]=true;
						f[i+1][0][k]=true;
						f[i+1][j][0]=true;
						if(j+k>=y)
							f[i+1][j+k-y][y]=true;
						else
							f[i+1][0][j+k]=true;
						if(j+k>=x)
							f[i+1][x][j+k-x]=true;
						else
							f[i+1][j+k][0]=true;
					}
		for(int j=0;j<=x;j++)
			for(int k=0;k<=y;k++)
				if(f[K][j][k])
					ans=min(ans,abs(m-j-k));
		return ans;
	}
}cls;
int main()
{
	printf("%d\n",cls.solve());
}
