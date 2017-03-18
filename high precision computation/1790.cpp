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
	bool operator < (const hpc &s) const
	{
		if(s.len!=len)
			return len<s.len;
		for(int i=len;i;i--)
			if(s.x[i]!=x[i])
				return x[i]<s.x[i];
	}
	bool operator == (const hpc &s) const
	{
		if(s.len!=len)
			return false;
		for(int i=len;i;i--)
			if(s.x[i]!=x[i])
				return false;
		return true;
	}
	void operator -= (const hpc &s)
	{
		int l=max(len,s.len);
		for(int i=1;i<=l;i++)
		{
			x[i]-=s.x[i];
			if(x[i]<0)
			{
				x[i]+=mod;
				--x[i+1];
			}
		}
		while(!x[l]&&l>1)
			--l;
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
	if(A==B)
		return puts("0"),0;
	if(A<B)
	{
		putchar('-');
		B-=A;
		B.print();
	}	
	else
	{
		A-=B;
		A.print();
	}
}
