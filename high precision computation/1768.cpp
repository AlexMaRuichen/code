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
	bool flag;
	hpc()
	{
		len=1;
		flag=false;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		char ch=getchar();
		int l=0;
		while(ch<'0'||ch>'9')
		{
			if(ch=='-')
				flag=true;
			ch=getchar();
		}
		while(ch>='0'&&ch<='9')
			s[++l]=ch,ch=getchar();
		len=(l+3)/4;
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
	void operator -= (const hpc &s)
	{
		for(int i=1;i<=len;i++)
		{
			x[i]-=s.x[i];
			if(x[i]<0)
				--x[i+1],x[i]+=mod;
		}
		while(!x[len]&&len>1)
			--len;
	}
	int check(const hpc &s) const 
	{
		if(len<s.len)
			return -1;
		else if(len>s.len)
			return 1;
		else
			for(int i=len;i;i--)
				if(x[i]<s.x[i])
					return -1;
				else if(x[i]>s.x[i])
					return 1;
		return 0;
	}
}A,B;
int main()
{
	A.read();
	B.read();
	if(A.flag^B.flag)
	{
		int t=A.check(B);
		if(t==0)
			puts("0");
		else if(t>0)
		{
			A-=B;
			if(A.flag)
				putchar('-');
			A.print();
		}
		else if(t<0)
		{
			B-=A;
			if(B.flag)
				putchar('-');
			B.print();
		}
	}
	else
	{
		A+=B;
		if(A.flag)
			putchar('-');
		A.print();
	}
}
