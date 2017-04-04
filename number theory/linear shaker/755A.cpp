#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=1e6+10;
const int maxn=N+10;
bool v[maxn];
int prime[maxn];
void linear_shaker()
{
	for(int i=2;i<=N;i++)
	{
		if(!v[i])
			prime[++prime[0]]=i;
		for(int j=1;j<=prime[0]&&i*prime[j]<=N;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
	linear_shaker();
	int n;
	scanf("%d",&n);
	for(int i=1;i<=1000;i++)
		if(v[i*n+1])
			return printf("%d\n",i),0;
}
