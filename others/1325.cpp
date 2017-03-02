#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=2050;
int n;
int sum[maxn];
int space[maxn][maxn];
int main()
{
	scanf("%d",&n);
	
	sum[1]=sum[2]=1;
	for(int i=1;i<=n;i++)
		for(int k=1;k<=(1<<i);k++)
			sum[k+(1<<i)]=sum[k]<<1;
	
	int mid=(sum[1<<n])>>1;
	
	for(int i=1;i<=n;i++)
		for(int k=1,cnt=1<<i;k<=(1<<i);k++,cnt-=2)
			space[k+(1<<(i-1))][mid]=max(cnt-2,0);
	
	for(int j=1;j<=n-2;j++)
		for(int k=1;k<=(1<<j);k++)
			for(int i=1;i<=sum[k];i++)
			{
				space[k+(1<<j)][mid-i]=space[k][mid+(sum[k]>>1)-i];
				space[k+(1<<j)][mid+i]=space[k][mid+(sum[k]>>1)-i];
			}
	
	for(int j=1;j<=n-2;j++)
		for(int k=1;k<=(1<<j);k++)
			for(int i=1;i<=sum[k+(1<<j)];i++)
			{
				space[k+(1<<j)+(1<<(n-1))][mid-i]=space[k+(1<<j)][mid+(sum[k+(1<<j)]>>1)-i];
				space[k+(1<<j)+(1<<(n-1))][mid+i]=space[k+(1<<j)][mid+(sum[k+(1<<j)]>>1)-i];
			}			
			
	for(int i=1;i<=(1<<n);i++)
	{
		for(int j=1;j<=(1<<n)-i;j++)
			putchar(' ');
		if(i&1)
			for(int j=1;j<=sum[i];j++)
			{
				putchar('/'),putchar('\\');
				for(int k=1;k<=space[i][mid-(sum[i]>>1)+j];k++)
					putchar(' ');
			}
		else
			for(int j=1;j<=sum[i];j++)
			{
				putchar('/'),putchar('_'),putchar('_'),putchar('\\');
				for(int k=1;k<=space[i][mid-(sum[i]>>1)+j];k++)
					putchar(' ');
			}
		puts("");
	}
}
