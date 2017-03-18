#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=5010;
int f[11][maxn+1];
int leading_zeros=1;
int n,k;
void recursion(int n,int k,int m)
{
	if(k==0&&m==1)
		return;
	if(k==0||f[k][m-1]>=n) 
	{
		if(!leading_zeros) 
			printf("0");
		recursion(n,k,m-1);
	} 
	else 
	{
		leading_zeros = 0;
		printf ("1");
		recursion(n-f[k][m-1],k-1,m-1);
	}
}

int main()
{
	scanf("%d%d",&n,&k);
	if (k==1)
	{
		printf("1");
		for(int i=1;i<n;i++)
			printf("0");
		puts("");
		return 0;
	}
	f[0][1]=1;
	for(int j=1;j<=maxn;j++) 
	{
		for(int i=0;i<=10;i++) 
		{
			if(i==0) 
				f[i][j]=1;
			else 
				f[i][j]=f[i-1][j-1]+f[i][j-1];
			f[i][j]=min(f[i][j],10000000);
		}
	}
	recursion(n,k,maxn);
	puts("");
}
