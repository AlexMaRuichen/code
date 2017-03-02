#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=5010;
double f[2][maxn];
int r,b;

int main()
{
    scanf("%d%d",&r,&b);
    for(int i=1;i<=r;i++)
    {
        f[i&1][0]=i;
        for(int j=1;j<=b;j++)
            f[i&1][j]=max(0.0,i/double(i+j)*(f[(i^1)&1][j]+1)+j*1.0/double(i+j)*(f[i&1][j-1]-1));
    }
    printf("%.6lf\n",f[r&1][b]-5e-7>0?f[r&1][b]-5e-7:0);
}
