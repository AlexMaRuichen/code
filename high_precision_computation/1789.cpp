#include <stdio.h>
#include <string.h>
#include <algorithm>
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
		memset(x,0,sizeof(x));
		len=1;
	}
	void read()
	{
		char ch;
		int l=0;
		memset(s,0,sizeof(s));
		ch=getchar();
		while(ch<'0'||ch>'9')
			ch=getchar();
		while(ch>='0'&&ch<='9')
			s[++l]=ch,ch=getchar();
		len=(l+3)/4;
		int rem=l%4,cnt=0,num=0;
		for(int i=1;i<=l;i++)
		{
			num=(num<<1)+(num<<3)+s[i]-'0';
			if((i-rem)%4==0)
				x[len-cnt++]=num,num=0;
		}
		if(num)
			x[len-cnt]=num;
	}
	void operator += (const hpc &s) 
	{
		int l=max(len,s.len);
		for(int i=1;i<=l;i++)
		{
			x[i]+=s.x[i];
			x[i+1]+=x[i]/mod;
			x[i]%=mod;
		}
		while(x[l+1])
			++l;
		len=l;
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
}A,B;
int main()
{
	A.read();
	B.read();
	A+=B;
	A.print();
}
