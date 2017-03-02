#include <stdio.h>
#include <bitset>
#include <algorithm>
using namespace std;
const int maxn=5e7+10;
int n;
int prime[3001140];
bool v[maxn];
void linear_shaker()
{
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
			prime[++prime[0]]=i;
		for(int j=1;j<=prime[0]&&i*prime[j]<=n;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	printf("%d\n",prime[0]);
}
int main()
{
	scanf("%d",&n);
	linear_shaker();	
}
