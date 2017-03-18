#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e3+10;
int n;
int a[maxn];
int f[2][maxn][2];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[++n]=0;
	sort(a+1,a+n+1);
	memset(f[0],0x3f,sizeof(f[0]));
	for(int i=1;i<=n;i++)
		if(a[i]==0)
		{
			f[0][i][0]=0;
			break;
		}
	int c;
	for(int len=1;len<n;len++)
	{
		c=n-len;
		for(int i=1;i+len<=n+1;i++)
		{
			f[len&1][i-1][0]=min(f[(len^1)&1][i][0]+c*(a[i]-a[i-1]),f[(len^1)&1][i][1]+c*(a[i+len-1]-a[i-1]));
			f[len&1][i][1]=min(f[(len^1)&1][i][0]+c*(a[i+len]-a[i]),f[(len^1)&1][i][1]+c*(a[i+len]-a[i+len-1]));
		}	
	}
	printf("%d\n",min(f[(n^1)&1][1][0],f[(n^1)&1][1][1]));
}


