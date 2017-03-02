#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;
int b;
string bin="0123456789ABCDEFGHIJ";
int f[21][21];
void check(int x);
int main()
{
	memset(f,0x3f,sizeof(f));
	cin>>b;
	f[b][0]=1;
	for(int i=1;f[b][i-1]<90000;i++)
		f[b][i]=f[b][i-1]*b;
	for(int i=1;i<=300;i++)
		check(i);
}
void check(int x)
{
	static string p,n;
	p.clear();
	n.clear();
	static int pow,s,e;
	pow=x*x;
	for(int i=20;i>=0;i--)
	{
		static int cnt;
		cnt=0;
		while(f[b][i]<=pow)
			pow-=f[b][i],cnt++;
		if(cnt)
			p+=bin[cnt];
		else if(p[0])
			p+='0';
	}
	s=0,e=p.length()-1;
	while(s<=e)
	{
		if(p[s]!=p[e])
			return;
		s++,e--;
	}
	for(int i=20;i>=0;i--)
	{
		static int cnt;
		cnt=0;
		while(f[b][i]<=x)
			x-=f[b][i],cnt++;
		if(cnt)
			n+=bin[cnt];
		else if(n[0])
			n+='0';
	}
	cout<<n<<" "<<p<<endl;
}
