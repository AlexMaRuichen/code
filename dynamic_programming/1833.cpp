#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int main()
{
	static ll f[14],ans[10],pow,a,b,cur;
	scanf("%lld%lld",&a,&b);
	int i;
	++b;
	for(i=1,pow=1;i<=13;i++,pow*=10)
		f[i]=f[i-1]*10+pow;	
	for(i=1,pow=10;pow<b;i++,pow*=10)
	{
		for(int j=0;j<10;j++)
			ans[j]+=f[i-1]*9;
		for(int j=1;j<10;j++)
			ans[j]+=pow/10;
	}
	cur=pow/=10;
	--i;
	while(cur<b)
	{
		while(cur+pow<=b)
		{
			ll t=cur/pow;
			while(t)
				ans[t%10]+=pow,t/=10;
			for(int j=0;j<10;j++)
				ans[j]+=f[i];
			cur+=pow;
		}
		pow/=10,--i;
	}
	for(i=1,pow=10;pow<a;i++,pow*=10)
	{
		for(int j=0;j<10;j++)
			ans[j]-=f[i-1]*9;
		for(int j=1;j<10;j++)
			ans[j]-=pow/10;
	}
	cur=pow/=10;
	--i;
	while(cur<a)
	{
		while(cur+pow<=a)
		{
			ll t=cur/pow;
			while(t)
				ans[t%10]-=pow,t/=10;
			for(int j=0;j<10;j++)
				ans[j]-=f[i];
			cur+=pow;
		}
		pow/=10,--i;
	}
	for(int i=0;i<10;i++)
		printf("%lld%c",ans[i],i^9?' ':'\n');
}
