#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e5+10;
const int mod=1e8;
struct hpc
{
	long long x[maxn];
	int len;
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		scanf("%lld",&x[1]);
	}
	void print()
	{
		printf("%lld",x[len]);
		for(int i=len-1;i;i--)
			printf("%08lld",x[i]);
		puts("");
	}
	void operator *= (const hpc &s) 
	{
		hpc res;
		res.len=s.len+len;
		for(int i=1;i<=len;i++)
		{
			long long num=0,t;
			for(int j=1;j<=s.len;j++)
			{
				t=x[i]*s.x[j]+res.x[i+j-1]+num;
				res.x[i+j-1]=t%mod;
				num=t/mod;
			}
			if(num)
				res.x[i+s.len]=num;
		}
		*this=res;
		while(!x[len]&&len>1)
			--len;
	}
	void operator ^= (int y) 
	{
		hpc ans;
		ans.x[1]=1;
		while(y)
		{
			if(y&1)
				ans*=*this;
			*this*=*this;
			y>>=1;
		}
		*this=ans;
	}
}A;
int main()
{
	A.read();
	int y;
	scanf("%d",&y);
	A^=y;
	A.print();
}
