#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=44800;
const int N=44723;

int mu[maxn];
bool v[maxn];
int prime[maxn];
void linear_shaker()
{
	mu[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!v[i])
		{
			prime[++prime[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=prime[0]&&prime[j]*i<=N;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
}

int main()
{
	int T;
	linear_shaker();
	scanf("%d",&T);
	while(T--)
	{
		int k;
		scanf("%d",&k);
		int l=1,r=k<<1|1,mid;
		while(l<r)
		{
			mid=(l>>1)+(r>>1)+(l&r&1);
			int t=0;
			for(int i=1;i*i<=mid;i++)
				t+=mid/i/i*mu[i];
			if(t>=k)
				r=mid;
			else
				l=mid+1;
		}
		printf("%d\n",l);
	}
}
