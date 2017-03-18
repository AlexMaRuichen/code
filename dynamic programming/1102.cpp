#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int k[21][21];
int f[21];
int b[21];
int n,m,t;
int ans;
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	while(t--)
	{
		ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%1d",&k[i][j]);
		for(int j=1;j<=m;j++)
			for(int i=1;i<=n;i++)
				if(k[i][j])
					f[j]|=1<<(i-1);
		for(int i=0;i<=(1<<n)-1;i++)
		{
			memcpy(b,f,sizeof(f));
			for(int j=1;j<=m;j++)
				printf("%d\n",b[j]);
			for(int j=1;j<=m;j++)
			{
				b[i]=b[i]^(b[i-1]<<1)^(b[i-1]<<2)^(b[i-1]>>1)^(b[i-1]>>2)^b[i-1];
				b[i+1]=(b[i+1]^b[i-1])&((1<<n)-1);
			}
			if(!(b[m]&((1<<n)-1)))
				ans++;
		}
		printf("%d\n",ans);
	}
}
