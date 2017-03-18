#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
int h[110];
int sum;
int ans;
int f[2][2010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
		sum+=h[i];
	}
	memset(f,-1,sizeof(f));
	f[1][0]=0;
	int a;
	for(int i=1;i<=n;i++)
	{
		a=1-i%2;
		memset(f[a],-1,sizeof(f[a]));
		for(int j=0;j<=sum;j++)
		{
			if(f[a^1][j]>-1)
				f[a][j]=f[a^1][j];
			if(h[i]>j&&f[a^1][h[i]-j]>-1)
				f[a][j]=max(f[a][j],f[a^1][h[i]-j]+j);
			if(j+h[i]<=sum&&f[a^1][j+h[i]]>-1)
				f[a][j]=max(f[a][j],f[a^1][j+h[i]]);
 			if(j>=h[i]&&f[a^1][j-h[i]]>-1)
				f[a][j]=max(f[a][j],f[a^1][j-h[i]]+h[i]);	
		}
	}
	if(f[a][0]>0)
		printf("%d",f[a][0]);
	else
		puts("Impossible");
}
