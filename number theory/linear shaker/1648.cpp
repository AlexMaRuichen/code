#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxprime=50010;
bool v[maxprime];
int prime[6000];
void sieve_of_Eratosthenes()
{
	for(int i=2;i<=50000;i++)
		if(!v[i])
		{
			prime[++prime[0]]=i;
			for(int j=2;j*i<=50000;j++)
				v[i*j]=true;
		}
}
int a0,a1,b0,b1;
int ans;
void calc(int p)
{
	static int cnt1,cnt2,cnt3,cnt4;
	cnt1=cnt2=cnt3=cnt4=0;
	while(a0%p==0)
		a0/=p,++cnt1;
	while(a1%p==0)
		a1/=p,++cnt2;
	while(b0%p==0)
		b0/=p,++cnt3;
	while(b1%p==0)
		b1/=p,++cnt4;
	if(cnt1==cnt2&&cnt3==cnt4)
    {
	    if(cnt2<=cnt4)
			ans*=cnt4-cnt2+1;
	    else
			ans=0;
    }
	else if(cnt1!=cnt2&&cnt3!=cnt4&&cnt2!=cnt4)
		ans=0;
}
int main()
{
	sieve_of_Eratosthenes();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ans=1;
		scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
		for(int i=1;i<=prime[0];i++)
			calc(prime[i]);
		if(b1!=1)
			calc(b1);
		printf("%d\n",ans);
	}
}
