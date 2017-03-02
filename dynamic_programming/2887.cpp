#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e4+10;
const int maxm=1010;
const int inf=1061109567;
int n,m,k;
int f[maxn][maxm];
int l[maxn];
int r[maxn];
int u[maxn];
int d[maxn];
int idx=1;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	register int i,j;
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&u[i],&d[i]);
		l[i+1]=0;
		r[i+1]=m+1;
	}
	for(i=1;i<=k;i++)
	{
		static int x;
		scanf("%d",&x);
		scanf("%d%d",&l[x],&r[x]);
	}
	f[0][0]=inf;
	for(i=1;i<=n;i++)
	{
		memset(f[i],0x3f,sizeof(int)*(m+1));
		for(j=1;j<=m;j++)
		{
			if(j>=u[i-1])
				f[i][j]=min(f[i][j],min(f[i-1][j-u[i-1]]+1,f[i][j-u[i-1]]+1));
			if(j==m)
				for(int k=j-u[i-1];k<=m;k++)
					f[i][j]=min(f[i][j],min(f[i-1][k]+1,f[i][k]+1));
		}
		for(j=l[i]+1;j<=r[i]-1;j++)
			if(j+d[i-1]<=m)
				f[i][j]=min(f[i][j],f[i-1][j+d[i-1]]);
		for(j=1;j<=l[i];j++)
			f[i][j]=inf;
		for(j=r[i];j<=m;j++)
			f[i][j]=inf;
	}
	int ans=inf,cnt=k;
	for(i=n;i;i--)
	{
        for(j=l[i]+1;j<=r[i]-1;j++)
            if(f[i][j]<inf)
            	ans=min(ans,f[i][j]);
        if(ans!=inf)
			break;
        if(r[i]<=m)
			cnt--;
    }
	if(cnt==k)
		printf("1\n%d\n",ans);
 	else
		printf("0\n%d\n",cnt);
}
