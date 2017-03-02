#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxlen=1e5+10;
const int mod=1e4;
char s[maxlen];
struct hpc
{
	int x[maxlen];
	int len;
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		char ch=getchar();
		int l=0;
		while(ch<'0'||ch>'9')
			ch=getchar();
		while(ch>='0'&&ch<='9')
			s[++l]=ch,ch=getchar();
		len=(l+3)>>2;
		int rem=l%4,num=0,cnt=0;
		for(int i=1;i<=l;i++)
		{
			num=(num<<1)+(num<<3)+s[i]-'0';
			if((i-rem)%4==0)
				x[len-cnt++]=num,num=0;
		}
		if(num)
			x[len-cnt]=num;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
	void operator *= (const int &s) 
	{
		int num=0;
		for(int i=1;i<=len;i++)
		{
			num+=s*x[i];
			x[i]=num%mod;
			num/=mod;
		}
		if(num)
			x[++len]=num;
	}
}A;
int b;
int main()
{
	A.read();
	scanf("%d",&b);
	A*=b;
	A.print();
}
