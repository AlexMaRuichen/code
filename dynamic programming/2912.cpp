#include <stdio.h>
#include <string.h>
#include <algorithm>
#define dis(a,b) (abs(p[(a)].first-p[(b)].first)+abs(p[(a)].second-p[(b)].second))
using namespace std;
const int maxn=510;
int n,k;
typedef pair<int,int> point;
point p[maxn];
int e=505;
int ans;
int f[maxn][maxn];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	memset(f,0x3f,sizeof(f));
	f[1][0]=0;
	for(int i=2;i<=n;i++)
        for(int j=0;j<=i-2&&j<=::k;j++)
            for(int k=0;k<=j;k++)
                f[i][j]=min(f[i][j],f[i-k-1][j-k]+dis(i-k-1,i));
    printf("%d\n",f[n][min(n-2,k)]);
}
