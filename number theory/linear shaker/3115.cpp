#include <stdio.h>
#include <bitset>
using namespace std;
const int maxn=1e6;
bitset <maxn+10> v;
int prime[80000];
int phi[maxn+10];
long long ans[maxn+10];
long long sum;
void liner_shaker()
{
	for(int i=2;i<=maxn;i++)
	{
		if(!v[i])
			prime[++prime[0]]=i,phi[i]=i-1;
		for(int j=1;j<=prime[0]&&i*prime[j]<=maxn;j++)
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
	for(int i=1;i<=maxn;i++)
		ans[i]=ans[i-1]+phi[i];
}
int main()
{
	liner_shaker();
	int x;
	while(scanf("%d",&x)&&x)
		printf("%lld\n",ans[x]);
}
