#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int n,s;
string bin="0123456789";
int f[11][21];
void check(int x);
int main()
{
	cin>>n>>s;
	memset(f,0x3f,sizeof(f));
	for(int i=2;i<=10;i++)
	{
		f[i][0]=1;
		for(int j=1;f[i][j-1]<50000;j++)
			f[i][j]=f[i][j-1]*i;
	}
	++s;
	while(n)
		check(s++);
}
void check(int x)
{
	static int c,l,r,tmp,cnt;
	static string d;
	c=0;	
	for(int j=10;j>=2;j--)
	{
		tmp=x;
		d.clear();
		for(int i=20;i>=0;i--)
		{	
			cnt=0;
			while(f[j][i]<=tmp)
				tmp-=f[j][i],cnt++;
			if(cnt)
				d+=bin[cnt];
			else if(d[0])
				d+='0';
		}
		l=0,r=d.length()-1;
		while(l<=r)
		{
			if(d[l]!=d[r])
				goto lableA;
			l++,r--;
		}
		c++;
		if(c==2)
		{
			cout<<x<<endl;
			n--;
			return;
		}
		lableA:;
	}
}
