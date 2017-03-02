#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=1010;
const int maxm=210;
const int mod=1e9+7;
int n,m,K;
char a[maxn];
char b[maxm];
int f[2][maxn][maxm];
int s[2][maxn][maxm];
int ans;
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	scanf("%s",a+1);
	scanf("%s",b+1);
	f[0][0][0]=1;
	register int i,j,k;
	for(i=0;i<=n;i++)
		s[0][i][0]=1;
	for(k=1;k<=K;k++)
	{
		memset(s[k&1],0,sizeof(s[k&1]));
		memset(f[k&1],0,sizeof(f[k&1]));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{
				if(a[i]==b[j])
				{
					f[k&1][i][j]=s[k&1^1][i-1][j-1];
					if(a[i-1]==b[j-1])
						if((f[k&1][i][j]+=f[k&1][i-1][j-1])>=mod)
							f[k&1][i][j]-=mod;
				}
				if((s[k&1][i][j]=s[k&1][i-1][j]+f[k&1][i][j])>=mod)
					s[k&1][i][j]-=mod;
			}
	}
	for(i=1;i<=n;i++)
		if((ans+=f[K&1][i][m])>=mod)
			ans-=mod;
	printf("%d\n",ans);
}
