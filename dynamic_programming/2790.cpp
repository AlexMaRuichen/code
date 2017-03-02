#include <stdio.h>
#include <algorithm>
using namespace std;
int n,k;
int a[50];
long long f[50][10];
int main()
{
    scanf("%d%d",&n,&k);
    ++k;
    for(int i=1;i<=n;i++)
        scanf("%1d",&a[i]);
    f[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        f[i][0]=1;
        for(int j=min(k,i);j;j--)
        {
            long long v=a[i];
            int t=10;
            for(int k=i-1;k>=0;k--)
            {
                f[i][j]=max(f[i][j],f[k][j-1]*v);
                v+=a[k]*t;
                t*=10;
            }
        }
    }
    printf("%lld\n",f[n][k]);
}
