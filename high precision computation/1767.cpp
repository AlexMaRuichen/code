#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e5;
const int mod=1e4;
struct hpc
{
	int x[maxn];
	int len;
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
		x[1]=1;
	}
	void operator *= (const int &s) 
	{
		static long long num;
		num=0;
		for(int i=1;i<=len;i++)
		{
			num+=x[i]*s;
			x[i]=num%mod;
			num/=mod;
		}
		if(num)
			x[++len]=num;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
}A;
int main()
{	
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		A*=i;
	A.print();
}
