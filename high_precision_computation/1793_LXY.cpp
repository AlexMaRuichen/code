#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn=1e5+9;
const int mod=1e4;
int ans;
int b;
char s[maxn];
struct hpc
{
	int len;
	int a[maxn];
	hpc()
	{
		len=0;
		memset(a,0,sizeof(a));
	}
	hpc& operator /= (const int &x)
	{
		int tmp=0;
		for(int i=len;i;i--)
		{
			a[i]+=(tmp*mod);
			tmp=a[i]%x;
			a[i]/=x;
		}
		ans=tmp;
		while(!a[len]&&len!=0)
			len--;
		return *this;
	}
}A;
void read()
{
	int l=strlen(s+1);
	int dig=1,cnt=0,num=0;
	for(int i=l;i;i--)
	{
		num+=dig*(s[i]-'0');
		cnt++,dig*=10;;	
		if(cnt==4)
		{
			A.a[++A.len]=num;
			num=0,cnt=0,dig=1;
		}
	}
	if(cnt)
		A.a[++A.len]=num;
}
void print()
{
	int l=A.len;
	printf("%d",A.a[l]);
	for(int i=l-1;i;i--)
		printf("%04d",A.a[i]);
}
int main()
{
	scanf("%s%d",s+1,&b);
	read();
	A/=b;
	print();
	printf("\n%d\n",ans);
}
