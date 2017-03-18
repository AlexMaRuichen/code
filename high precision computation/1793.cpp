#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;
const int maxn=1e5+10;
const int mod=1e4;
int r;
int s;
struct hpc
{
	int len;
	int x[maxn];
	hpc()
	{
		len=1;
		memset(x,0,sizeof(x));
	}
	void read()
	{
		string s;
		cin>>s;
		int l=s.length();
		int rem=l%4;
		len=l/4;
		if(rem)
			len++;
		int cnt=0;
		int num=0;
		for(int i=1;i<=l;i++)
		{
			num=(num<<1)+(num<<3);
			num+=s[i-1]-'0';
			if((i-rem)%4==0)
			{
				x[len-cnt]=num;
				cnt++;
				num=0;
			}
		}
	}
	void print()
	{
		printf("%d",x[len]);
		for(int i=len-1;i;i--)
			printf("%04d",x[i]);
		puts("");
	}
	void operator /= (const int &s)
	{
		for(int i=len;i;i--)
		{
			x[i]+=r*mod;
			r=x[i]%s;
			x[i]/=s;
		}
		while(x[len]==0&&len>1)
			len--;
	}
}A;
int main()
{
	A.read();
	scanf("%d",&s);
	A/=s;
	A.print();
	printf("%d\n",r);
}
