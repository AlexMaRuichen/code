#include <stdio.h>
#include <algorithm>
#include <bitset>
using namespace std;
const int maxn=2e4+10;
bitset <maxn> v;
int n;
int prime[2300];
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
			prime[++prime[0]]=i;
		for(int j=1;j<=prime[0]&&prime[j]*i<=n;j++)
		{
			v[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	for(int i=1;i<=prime[0];i++)
		printf("%d\n",prime[i]);
}
