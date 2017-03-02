#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn=110;
int k,n;
double f[maxn][10];
double ans;
int main()
{
    while(scanf("%d%d",&k,&n)==2)
    {
        ans=0;
        for(int i=0;i<=k;i++)
            f[1][i]=100.0/(k+1);
        for(int i=2;i<=n;i++)
        {
            f[i][0]=(f[i-1][0]+f[i-1][1])/(k+1);
            for(int j=1;j<k;j++)
                f[i][j]=(f[i-1][j-1]+f[i-1][j]+f[i-1][j+1])/(k+1);
            f[i][k]=(f[i-1][k-1]+f[i-1][k])/(k+1);
        }
        for(int i=0;i<=k;i++)
            ans+=f[n][i];
        printf("%.5f\n",ans);
    }
}
