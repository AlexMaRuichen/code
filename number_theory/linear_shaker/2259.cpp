#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
const int mx=1e6;
int prime[80000];
int phi[maxn];
bool v[maxn];
long long sum[maxn];
long long tot;
void linear_shaker()
{
	phi[1]=1;
	for(int i=2;i<=mx;i++)
	{
		if(!v[i])
			prime[++prime[0]]=i,phi[i]=i-1;
		for(int j=1;j<=prime[0]&&i*prime[j]<=mx;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(int i=1;i<=mx;i++)
		tot+=phi[i],sum[i]=1+(tot<<1);
}
int n;
int main()
{
	linear_shaker();
	while(~scanf("%d",&n))
		printf("%lld\n",sum[n]);
}
